#include <DawnStar/dspch.hpp>
#include "IndicatorSystem.hpp"

#include "../../Utils/Utils.hpp"
#include "CustomComponent.hpp"

IndicatorSystem::IndicatorSystem(Ref<ChessBoard> &chessBoard, Ref<Scene> scene)
    : m_ChessBoard(chessBoard), m_Scene(scene)
{
}

void IndicatorSystem::OnUpdate(Timestep ts, entt::registry &registry)
{
    const auto view = registry.view<TransformComponent, IndicatorComponent>();

    for(auto &&[entity, transform, indicator] : view.each())
    {
        
        if(Input::IsMouseButtonDown(Mouse::Button0))
        {
            auto pos = Utils::ToScreenCoord(Input::GetMousePosition());

            pos = Utils::ToScreenToWorldCoord(pos, m_Scene->GetPrimaryCameraEntity());
            
            transform.Translation.x = pos.x;
            transform.Translation.y = pos.y;

            continue;
        }
        
        int axisX = -static_cast<int>(Input::IsKeyDown(Key::A)) + static_cast<int>(Input::IsKeyDown(Key::D));
        int axisY = -static_cast<int>(Input::IsKeyDown(Key::S)) + static_cast<int>(Input::IsKeyDown(Key::W));

        // TODO: KeyDown, KeyUp, Key implementation

        transform.Translation.x += axisX;
        transform.Translation.y += axisY;

        
        if(Input::IsKeyDown(Key::Space))
        {

        }

    }
}