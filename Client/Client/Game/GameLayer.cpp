#include <DawnStar/dspch.hpp>
#include "GameLayer.hpp"
#include "../Utils/ResourceManager.hpp"
#include "CustomComponent.hpp"

#include <DawnBoard/Chess/Logic/ChessBoardState.hpp>

#include <imgui.h>

#define BIND_EVENT_FN(x) std::bind(&GameLayer::x, this, std::placeholders::_1)

GameLayer::GameLayer()
    : m_StatPanel()
{
	m_ChessBoard = CreateRef<ChessBoard>();
}

void GameLayer::OnAttach()
{
	m_Scene = CreateRef<Scene>();

	m_Scene->OnViewportResize(Application::Get().GetWindow().GetWidth(),
							  Application::Get().GetWindow().GetHeight());

	{ 
		// Load resource
		ResourceManager::instance().LoadTexturesFromAssets();

		// Init chess board
		m_ChessBoard->Init();
	}

	{ // Draw simple map
		for(int i = 0; i < 8; ++i)
		{
			for(int j = 0; j < 8; ++j)
			{
				Entity obj = m_Scene->CreateEntity("board");
				auto& transform = obj.GetComponent<TransformComponent>();
				transform.Translation = {j, i, 0};
				auto& sprite = obj.AddComponent<SpriteRendererComponent>();
				sprite.Color = ((i + j) % 2 == 0)? glm::vec4(.15f, .15f, .15f, 1.0f): glm::vec4(.85f, .85f, .85f, 1.f);
			}
		}
	}
	{
		// Draw Chess 
		auto pieces = m_ChessBoard->GetState<ChessBoardState>()->pieces;
		for(auto piece : pieces)
		{
			Entity obj = m_Scene->CreateEntity();
			auto& transform = obj.GetComponent<TransformComponent>();
			transform.Translation = {piece->m_Pos.x, piece->m_Pos.y, 0};
			auto& sprite = obj.AddComponent<SpriteRendererComponent>();
			sprite.Texture = ResourceManager::instance().GetTexture(
				"pieces/" + GetTextureNameByPieceType(piece->m_PieceType,
													  piece->m_Color)
			);
			obj.AddComponent<ChessComponent>();

			DS_APP_INFO("Create {0} on ({1}, {2})", 
						GetTextureNameByPieceType(piece->m_PieceType, piece->m_Color),
						piece->m_Pos.x, piece->m_Pos.y);

		} 
	}

	{
		Entity cameraObj = m_Scene->CreateEntity("Camera");
		auto& transform = cameraObj.GetComponent<TransformComponent>();
		transform.Translation = {4.0f, 4.0f, 12.0f};
		auto cam = cameraObj.AddComponent<CameraComponent>();
	}

}

void GameLayer::OnDetach()
{
    
}

void GameLayer::OnUpdate(Timestep ts)
{
	Renderer2D::ResetStats();
	RenderCommand::SetClearColor({0.3f, 0.2f, 0.1f, 1.0f});
	RenderCommand::Clear();
	m_Scene->OnUpdate(ts);
}

void GameLayer::OnImGuiRender()
{
	m_StatPanel.OnImGuiRender();

	
	ImGui::Begin("Camera Setting");
	{
		auto camEntity = m_Scene->GetPrimaryCameraEntity();
		if(camEntity)
		{
			auto& transform = camEntity.GetTransform();
			ImGuiUI::DrawVec3Control("Translation", transform.Translation);
			ImGuiUI::DrawVec3Control("Rotation", transform.Rotation);
			ImGuiUI::DrawVec3Control("Scale", transform.Scale);
		}
	}
	ImGui::End();
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
		typeStr = "Pawn"; break;
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
