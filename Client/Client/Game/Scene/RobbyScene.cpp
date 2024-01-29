#include <pch.hpp>
#include "RobbyScene.hpp"
#include "../GameLayer.hpp"

#include "../../Network/NetworkManager.hpp"

#include <DawnStar/Game/UI/UISystem.hpp>

RobbyScene::RobbyScene(GameLayer* layer) : SceneWrapper("Robby"), _layer(layer)
{

}

void RobbyScene::OnAttach()
{
    _scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
    _scene->AddSystem(CreateRef<UI::UISystem>(_scene));

    // Network connect button
    {
        Entity entity = _scene->CreateEntity("Connect Button");
        auto& layout = entity.AddComponent<UI::LayoutComponent>();
        layout.AnchorMax = layout.AnchorMin = {0.5, 0.5};
        layout.Pivot = {0.5, 0.5};
        layout.Box = {400, 340, 80, 40};
        
		auto& transform = entity.GetTransform();
		transform.Scale = glm::vec3(20);
        
		auto& sprite = entity.AddComponent<UI::SpriteRendererComponent>();
		sprite.SortingOrder = 10;

        auto& button = entity.AddComponent<UI::ButtonComponent>();
        button.normalColor  = {0.3f, 0.8f, 0.3f, 0.5f};
        button.overColor    = {0.3f, 0.8f, 0.3f, 0.7f};
        button.pressColor   = {0.3f, 0.8f, 0.3f, 0.3f};
        button.onClick = []() {
            NetworkManager::Instance().Connect("127.0.0.1", "8888");
        };
    }
    {
        Entity entity = _scene->CreateEntity("Try to join Button");
        auto& layout = entity.AddComponent<UI::LayoutComponent>();
        layout.AnchorMax = layout.AnchorMin = {0.5, 0.5};
        layout.Pivot = {0.5, 0.5};
        layout.Box = {400, 290, 70, 40};
        
		auto& transform = entity.GetTransform();
		transform.Scale = glm::vec3(20);
        
		auto& sprite = entity.AddComponent<UI::SpriteRendererComponent>();
		sprite.SortingOrder = 10;

        auto& button = entity.AddComponent<UI::ButtonComponent>();
        button.normalColor  = {0.8f, 0.8f, 0.3f, 0.5f};
        button.overColor    = {0.8f, 0.8f, 0.3f, 0.7f};
        button.pressColor   = {0.8f, 0.8f, 0.3f, 0.3f};
        button.onClick = [this]() {
            
            Protocol::C_JOIN pkt;
            NetworkManager::Instance().Send(pkt);

            ControlLoadingScreen(true);
        };
    }
    {

    }

}

void RobbyScene::OnDetach()
{
}

void RobbyScene::OnUpdate(Timestep ts)
{
    _scene->OnUpdate(ts);
}

void RobbyScene::OnImGuiRender()
{
    
}

void RobbyScene::ControlLoadingScreen(bool run)
{
}
