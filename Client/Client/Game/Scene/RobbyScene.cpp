#include <DawnStar/dspch.hpp>
#include "RobbyScene.hpp"
#include "../GameLayer.hpp"

#include "../Network/NetworkManager.hpp"

#include <DawnStar/Game/UI/UISystem.hpp>

RobbyScene::RobbyScene(GameLayer* layer) : SceneWrapper(), _layer(layer)
{

}

void RobbyScene::OnAttach()
{
    _scene->OnViewportResize(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
    _scene->AddSystem(CreateRef<UI::UISystem>(_scene));

    // Network connect button
    {
        Entity simpleSprite = _scene->CreateEntity("Sprite");
        auto& layout = simpleSprite.AddComponent<UI::LayoutComponent>();
        layout.AnchorMax = layout.AnchorMin = {0.5, 0.5};
        layout.Pivot = {0.5, 0.5};
        layout.Box = {400, 500, 50, 50};
        
		auto& transform = simpleSprite.GetTransform();
		transform.Scale = glm::vec3(20);
        
		auto& sprite = simpleSprite.AddComponent<UI::SpriteRendererComponent>();
		sprite.SortingOrder = 10;

        auto& button = simpleSprite.AddComponent<UI::ButtonComponent>();
        button.normalColor = {0.3f, 0.8f, 0.3f, 0.5f};
        button.onClick = [this]() {
            Ne
        };
    }
    {
        Entity simpleSprite = _scene->CreateEntity("Sprite");
        auto& layout = simpleSprite.AddComponent<UI::LayoutComponent>();
        layout.AnchorMax = layout.AnchorMin = {0.5, 0.5};
        layout.Pivot = {0.5, 0.5};
        layout.Box = {400, 500, 50, 50};
        
		auto& transform = simpleSprite.GetTransform();
		transform.Scale = glm::vec3(20);
        
		auto& sprite = simpleSprite.AddComponent<UI::SpriteRendererComponent>();
		sprite.SortingOrder = 10;

        auto& button = simpleSprite.AddComponent<UI::ButtonComponent>();
        button.normalColor = {0.3f, 0.8f, 0.3f, 0.5f};
        button.onClick = [this]() {
            _layer->ChangeScene("Game");
        };
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