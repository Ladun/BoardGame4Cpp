#include <DawnStar/dspch.hpp>
#include "GameLayer.hpp"

#include <imgui.h>

GameLayer::GameLayer()
    : m_StatPanel()
{

}

void GameLayer::OnAttach()
{
	m_MainScene = DawnStar::CreateRef<DawnStar::Scene>();

	m_MainScene->OnViewportResize(DawnStar::Application::Get().GetWindow().GetWidth(),
								  DawnStar::Application::Get().GetWindow().GetHeight());

	{
		DawnStar::Entity testObj = m_MainScene->CreateEntity("Test object");
		auto transform = testObj.GetComponent<DawnStar::TransformComponent>();
		auto sprite = testObj.AddComponent<DawnStar::SpriteRendererComponent>();
		// sprite.Texture
	}

	{
		DawnStar::Entity cameraObj = m_MainScene->CreateEntity("Camera");
		auto transform = cameraObj.GetComponent<DawnStar::TransformComponent>();
		transform.Translation = {0.0f, 0.0f, -5.0f};
		auto cam = cameraObj.AddComponent<DawnStar::CameraComponent>();
	}

}

void GameLayer::OnDetach()
{
    
}

void GameLayer::OnUpdate(DawnStar::Timestep ts)
{
	DawnStar::Renderer2D::ResetStats();
	DawnStar::RenderCommand::SetClearColor({0.3f, 0.2f, 0.1f, 1.0f});
	DawnStar::RenderCommand::Clear();
	m_MainScene->OnUpdate(ts);
}

void GameLayer::OnImGuiRender()
{
	m_StatPanel.OnImGuiRender();
}

void GameLayer::OnEvent(DawnStar::Event& e)
{
}