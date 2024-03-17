#include <pch.hpp>
#include "RobbyScene.hpp"
#include "../GameLayer.hpp"

#include <Network/NetworkManager.hpp>

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
        layout.Box = {0, 20, 170, 30};

        auto& text = entity.AddComponent<TextComponent>();
        text.TextString = "Connect to Server";
        text.FontSize = 25;
        text.SetHorizontalCenter();
        text.SetVerticalCenter();

        auto& button = entity.AddComponent<UI::ButtonComponent>();
        button.normalColor  = {0.3f, 0.8f, 0.3f, 0.5f};
        button.overColor    = {0.3f, 0.8f, 0.3f, 0.7f};
        button.pressColor   = {0.3f, 0.8f, 0.3f, 0.3f};
        button.onClick = [this]() {
            ControlLoadingScreen(true);
            NetworkManager::Instance().Connect("127.0.0.1", "8888");
        };
        
		auto& sprite = entity.AddComponent<UI::SpriteRendererComponent>();
		sprite.SortingOrder = 8;
        sprite.Color = button.normalColor;
    }
    {
        Entity entity = _scene->CreateEntity("Try to join Button");
        auto& layout = entity.AddComponent<UI::LayoutComponent>();
        layout.AnchorMax = layout.AnchorMin = {0.5, 0.5};
        layout.Pivot = {0.5, 0.5};
        layout.Box = {0, -20, 110, 30};

        auto& text = entity.AddComponent<TextComponent>();
        text.TextString = "Join game";
        text.FontSize = 25;
        text.SetHorizontalCenter();
        text.SetVerticalCenter();

        auto& button = entity.AddComponent<UI::ButtonComponent>();
        button.normalColor  = {0.8f, 0.8f, 0.3f, 0.5f};
        button.overColor    = {0.8f, 0.8f, 0.3f, 0.7f};
        button.pressColor   = {0.8f, 0.8f, 0.3f, 0.3f};
        button.onClick = [this]() {
            ControlLoadingScreen(true);
            
            Protocol::C_JOIN pkt;
            NetworkManager::Instance().Send(pkt);
        };
        
		auto& sprite = entity.AddComponent<UI::SpriteRendererComponent>();
		sprite.SortingOrder = 9;
        sprite.Color = button.normalColor;
    }
    { // Create Loading Screen

        Entity entity = _scene->CreateEntity("Loading screen");
        auto& layout = entity.AddComponent<UI::LayoutComponent>();
        layout.AnchorMax = {1.0f, 1.0f};
        layout.AnchorMin = {0.0f, 0.0f};
        layout.Pivot = {0.5, 0.5};
        layout.Box = {0, 0, 0, 0};
        layout.Interactable = false;

        auto& transform = entity.GetTransform();
        transform.Translation.z = .02f;
        
		auto& sprite = entity.AddComponent<UI::SpriteRendererComponent>();
        sprite.Color = {0.0f, 0.0f, 0.0f, 0.8f};
		sprite.SortingOrder = 11;
        sprite.Enable = false;

        _loadingScreen = entity;
    }

    // Descending order
	_scene->SortComponents<UI::SpriteRendererComponent>(
		[](const auto& lhs, const auto& rhs)
		{
            // This means that if next value is greater than current value, dp swapping.
			return lhs.SortingOrder < rhs.SortingOrder;
		});
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
    auto& sprite = _loadingScreen.GetComponent<UI::SpriteRendererComponent>();
    auto& layout = _loadingScreen.GetComponent<UI::LayoutComponent>();
    layout.Interactable = run;
    sprite.Enable = run;
}
