#include <pch.hpp>
#include "TestSystem.hpp"

#include "CustomComponent.hpp"

void TestSystem::OnUpdate(Timestep ts, entt::registry& registry)
{
    const auto view = registry.view<TransformComponent, TestComponent>();
    auto windowWidth = Application::Get().GetWindow().GetWidth();
    auto windowHeight = Application::Get().GetWindow().GetHeight();

    for(auto &&[entity, transform, test] : view.each())
    {
        auto pos = Input::GetMousePosition();
        
        // TODO: Mouse chasing is delayed..;;
        transform.Translation = {pos.x - windowWidth / 2, windowHeight - pos.y - windowHeight / 2, 0.0f};

    }
}