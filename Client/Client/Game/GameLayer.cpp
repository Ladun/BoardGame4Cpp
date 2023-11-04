#include <DawnStar/dspch.hpp>
#include "GameLayer.hpp"

#include "../Utils/ResourceManager.hpp"
#include "../Utils/Utils.hpp"
#include "CustomComponent.hpp"

#include <DawnBoard/Chess/Logic/ChessBoardState.hpp>

#include <imgui.h>

#define BIND_EVENT_FN(x) std::bind(&GameLayer::x, this, std::placeholders::_1)

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
							  
	m_ObjListPanel.SetContext(m_Scene);

	// Load resource
	ResourceManager::instance().LoadTexturesFromAssets();

	// Init chess board
	m_ChessBoard->Init();


	{ // Draw simple map
		Entity parent = m_Scene->CreateEntity("board_parent");

		for(int i = 0; i < 8; ++i)
		{
			for(int j = 0; j < 8; ++j)
			{
				Entity obj = m_Scene->CreateEntity(Utils::string_format("board-%d-%d", i, j));
				obj.SetParent(parent);
				
				auto& transform = obj.GetTransform();
				transform.Translation = {j, i, 0};

				auto& sprite = obj.AddComponent<SpriteRendererComponent>();
				sprite.Color = ((i + j) % 2 == 0)? glm::vec4(.98f, .83f, .64f, 1.0f): glm::vec4(.82f, .66f, .43f, 1.f);
				sprite.SortingOrder = 1;
			}
		}
	}
	{
		// Draw Chess 
		Entity parent = m_Scene->CreateEntity("piece_parent");
		auto& transform = parent.GetTransform();
		transform.Translation = {0.0f, 0.0f, 1.0f};

		auto pieces = m_ChessBoard->GetState<ChessBoardState>()->pieces;
		for(auto piece : pieces)
		{
			Entity obj = m_Scene->CreateEntity(GetTextureNameByPieceType(piece->m_PieceType, piece->m_Color));
			obj.SetParent(parent);

			auto& transform = obj.GetComponent<TransformComponent>();
			transform.Translation = {piece->m_Pos.y, piece->m_Pos.x, 0};
			// transform.Scale = {0.8f, 0.8f, 0.8f};

			auto& sprite = obj.AddComponent<SpriteRendererComponent>();
			sprite.Texture = ResourceManager::instance().GetTexture(
				"pieces/" + GetTextureNameByPieceType(piece->m_PieceType,
													  piece->m_Color)
			);
			sprite.SortingOrder = 2;
			obj.AddComponent<ChessComponent>();

			DS_APP_INFO("Create {0} on ({1}, {2})", 
						GetTextureNameByPieceType(piece->m_PieceType, piece->m_Color),
						piece->m_Pos.x, piece->m_Pos.y);

		} 
	}

	{ // Camera
		Entity cameraObj = m_Scene->CreateEntity("Camera");
		auto& transform = cameraObj.GetComponent<TransformComponent>();
		transform.Translation = {4.0f, 4.0f, 12.0f};
		auto& cam = cameraObj.AddComponent<CameraComponent>();
		cam.Cam.SetOrthographic(10, -0.0f, 100.0f);
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
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
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
