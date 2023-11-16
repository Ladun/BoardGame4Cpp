#include <DawnStar/dspch.hpp>
#include "GameLayer.hpp"

#include "../Utils/ResourceManager.hpp"
#include "../Utils/Utils.hpp"
#include "Systems/CustomComponent.hpp"
#include "Systems/IndicatorSystem.hpp"
#include "Systems/ChessGraphicSystem.hpp"

#include <DawnBoard/Chess/ChessBoardState.hpp>

#include <imgui.h>

GameLayer::GameLayer()
    : m_StatPanel(), m_ObjListPanel()
{
	m_ChessBoard = CreateRef<ChessBoard>();
}
void GameLayer::OnAttach()
{
	m_Scene = CreateRef<Scene>();

	m_Scene->OnViewportResize(Application::Get().GetWindow().GetWidth(),
							  Application::Get().GetWindow().GetHeight());
	m_Scene->AddSystem(CreateRef<IndicatorSystem>(m_ChessBoard, m_Scene));
	m_Scene->AddSystem(CreateRef<ChessGraphicSystem>(m_ChessBoard, m_Scene));

	m_ObjListPanel.SetContext(m_Scene);

	// Load resource
	ResourceManager::instance().LoadTexturesFromAssets();

	// Init chess board
	m_ChessBoard->Init();

	{ // Indicator
		Entity indicator = m_Scene->CreateEntity("indicator");
		indicator.AddComponent<IndicatorComponent>();

		auto& transform = indicator.GetTransform();
		transform.Scale = glm::vec3(0.6f);
		transform.Translation.z = 2.0f;

		auto& sprite = indicator.AddComponent<SpriteRendererComponent>();
		sprite.Color = {0.3f, 0.8f, 0.3f, 0.5f};
		sprite.SortingOrder = 1;

	}

	{ // Test Indicator
		for(int i = 0; i< 2; ++i)
		{
			Entity indicator = m_Scene->CreateEntity("indicator2");
			auto& ic = indicator.AddComponent<IndicatorComponent>();
			ic.testIdx = i + 1;

			auto& transform = indicator.GetTransform();
			transform.Scale = glm::vec3(0.4f);
			transform.Translation = {10, 10 + i , 2.0f};

			auto& sprite = indicator.AddComponent<SpriteRendererComponent>();
			sprite.Color = {glm::vec3(i), 0.0f};
			sprite.SortingOrder = 1;
		}
		Entity indicator = m_Scene->CreateEntity("indicator3");
		auto& ic = indicator.AddComponent<IndicatorComponent>();
		ic.testIdx = 2;

		auto& transform = indicator.GetTransform();
		transform.Scale = glm::vec3(0.4f);
		transform.Translation = {10, 10 + 2 , 2.0f};

		auto& sprite = indicator.AddComponent<SpriteRendererComponent>();
		sprite.Color = {1.0f, 0.7f, 0.3f, 0.0f};
		sprite.SortingOrder = 1;

	}


	{ // Draw simple map
		Entity parent = m_Scene->CreateEntity("board_parent");
		
		{
			Entity obj = m_Scene->CreateEntity("board-back");
			obj.SetParent(parent);

			auto& transform = obj.GetTransform();
			transform.Translation = {3.5f, 3.5f, -0.1};
			transform.Scale = {8.5, 8.5, 1};

			auto& sprite = obj.AddComponent<SpriteRendererComponent>();
			sprite.Color = {glm::vec3(0.2f), 1.f};
			sprite.SortingOrder = -1;

			auto& cg = obj.AddComponent<ChessBoardComponent>();
			cg.back = true;
		}

		for(int i = 0; i < 8; ++i)
		{
			for(int j = 0; j < 8; ++j)
			{
				Entity obj = m_Scene->CreateEntity(Utils::string_format("board-%d-%d", i, j));
				obj.SetParent(parent);
				
				auto& transform = obj.GetTransform();
				transform.Translation = {j, i, 0};

				auto& sprite = obj.AddComponent<SpriteRendererComponent>();
				sprite.Color = ((i + j) % 2 == 1)? BOARD_BRIGHT_COLOR: BOARD_DARK_COLOR;
				sprite.SortingOrder = -1;

				auto& cg = obj.AddComponent<ChessBoardComponent>();
				cg.x	 = j;
				cg.y 	 = i;
				
			}
		}
	}
	{
		// Draw Chess 
		Entity parent = m_Scene->CreateEntity("piece_parent");
		auto& transform = parent.GetTransform();
		transform.Translation = {0.0f, 0.0f, 1.0f};

		auto& pieces = m_ChessBoard->GetState<ChessBoardState>()->pieces;
		for(auto& piece : pieces)
		{
			Entity obj = m_Scene->CreateEntity(GetTextureNameByPieceType(piece->m_PieceType, piece->m_Color));
			obj.SetParent(parent);

			auto& transform 		= obj.GetComponent<TransformComponent>();
			transform.Translation 	= {piece->m_Pos.x, piece->m_Pos.y, 0};
			// transform.Scale = {0.8f, 0.8f, 0.8f};

			auto& sprite 	= obj.AddComponent<SpriteRendererComponent>();
			sprite.Texture 	= ResourceManager::instance().GetTexture(
				"pieces/" + GetTextureNameByPieceType(piece->m_PieceType,
													  piece->m_Color)
			);
			sprite.SortingOrder = 0;

			auto& cg 	= obj.AddComponent<ChessPieceComponent>();
			cg.piece 	= piece;

		} 
	}

	{ // Camera
		Entity cameraObj = m_Scene->CreateEntity("Camera");
		auto& transform = cameraObj.GetComponent<TransformComponent>();
		transform.Translation = {4.0f, 4.0f, 12.0f};
		auto& cam = cameraObj.AddComponent<CameraComponent>();
		cam.Cam.SetOrthographic(20, -100.0f, 100.0f);
	}

	m_Scene->SortForSprites();	
}

void GameLayer::OnDetach()
{
    
}

void GameLayer::OnUpdate(Timestep ts)
{
	Renderer2D::ResetStats();
	RenderCommand::SetClearColor({0.4f, 0.4f, 0.4f, 1.0f});
	RenderCommand::Clear();

	m_Scene->OnUpdate(ts);
}

void GameLayer::OnImGuiRender()
{
	m_StatPanel.OnImGuiRender();
	m_ObjListPanel.OnImGuiRender();
}

void GameLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(DS_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<MouseMovedEvent>(DS_BIND_EVENT_FN(GameLayer::OnMouseMoved));
}

std::string GameLayer::GetTextureNameByPieceType(PieceType type, PieceColor color)
{
	// TODO: string concatenation optimization	
	std::string colorStr = color == PieceColor::BLACK? "Black": "White";
	std::string typeStr;
	switch(type)
	{
	case PieceType::BISHOP:
		typeStr = "Bishop"; break;
	case PieceType::KNIGHT:
		typeStr = "Knight"; break;
	case PieceType::QUEEN:
		typeStr = "Queen"; break;
	case PieceType::KING:
		typeStr = "King"; break;
	case PieceType::PAWN:
		typeStr = "Pawn"; break;
	case PieceType::ROOK:
		typeStr = "Rook"; break;
	}

	return colorStr + typeStr + ".png";
}

bool GameLayer::OnWindowResize(WindowResizeEvent &e)
{

	m_Scene->OnViewportResize(e.GetWidth(), e.GetHeight());
    return false;
}

bool GameLayer::OnMouseMoved(MouseMovedEvent &e)
{
	
	// auto pos = Input::GetMousePosition();
	// DS_APP_INFO("From event: ({0}, {1}), From system?: ({2}, {3}) {4}", 
	// 			e.GetX(), e.GetY(), pos.x, pos.y, (e.GetX() == pos.x && e.GetY() == pos.y));
    return false;
}
