#include <DawnStar/dspch.hpp>
#include "GameScene.hpp"

#include "../../Utils/ResourceManager.hpp"
#include "../../Utils/Utils.hpp"
#include "../Systems/CustomComponent.hpp"
#include "../Systems/IndicatorSystem.hpp"
#include "../Systems/ChessGraphicSystem.hpp"

#include <DawnBoard/Chess/ChessBoardState.hpp>

#include <imgui.h>

GameScene::GameScene()
{
	_chessBoard = CreateRef<ChessBoard>();
    _scene = CreateRef<Scene>();
}

void GameScene::OnAttach()
{
    _scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
	_scene->AddSystem(CreateRef<IndicatorSystem>(_chessBoard, _scene));
	_scene->AddSystem(CreateRef<ChessGraphicSystem>(_chessBoard, _scene));

#if DS_DEBUG
    _objListPanel.SetContext(_scene);
#endif

	// Load resource
	ResourceManager::instance().LoadTexturesFromAssets();

	// Init chess board
	_chessBoard->Init();

    { // Indicator
		Entity indicator = _scene->CreateEntity("indicator");
		indicator.AddComponent<IndicatorComponent>();

		auto& transform = indicator.GetTransform();
		transform.Scale = glm::vec3(0.6f);
		transform.Translation.z = 2.0f;

		auto& sprite = indicator.AddComponent<SpriteRendererComponent>();
		sprite.Color = {0.3f, 0.8f, 0.3f, 0.5f};
		sprite.SortingOrder = 10;

	}

	{ // Draw simple map
		Entity parent = _scene->CreateEntity("board_parent");
		
		{
			Entity obj = _scene->CreateEntity("board-back");
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
				Entity obj = _scene->CreateEntity(Utils::string_format("board-%d-%d", i, j));
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
		Entity parent = _scene->CreateEntity("piece_parent");
		auto& transform = parent.GetTransform();
		transform.Translation = {0.0f, 0.0f, 1.0f};

		auto& pieces = _chessBoard->GetState<ChessBoardState>()->pieces;
		for(auto& piece : pieces)
		{
			Entity obj = _scene->CreateEntity(GetTextureNameByPieceType(piece->m_PieceType, piece->m_Color));
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

			auto& cg 		= obj.AddComponent<ChessPieceComponent>();
			cg.piece 		= piece;
			cg.currentPos 	= piece->m_Pos;

		} 
	}

	{ // Camera
		Entity cameraObj = _scene->CreateEntity("Camera");
		auto& transform = cameraObj.GetComponent<TransformComponent>();
		transform.Translation = {4.0f, 4.0f, 12.0f};
		auto& cam = cameraObj.AddComponent<CameraComponent>();
		cam.Cam.SetOrthographic(40, -100.0f, 100.0f);
	}

	_scene->SortForSprites();
}

void GameScene::OnDetach()
{
}

void GameScene::OnUpdate(Timestep ts)
{
    _scene->OnUpdate(ts);
}

void GameScene::OnImGuiRender()
{
	_statPanel.OnImGuiRender();
	_objListPanel.OnImGuiRender();
}

std::string GameScene::GetTextureNameByPieceType(PieceType type, PieceColor color)
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