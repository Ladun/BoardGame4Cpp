#include <DawnStar/dspch.hpp>
#include "IndicatorSystem.hpp"

#include "../../Utils/Utils.hpp"
#include "CustomComponent.hpp"

#include <DawnBoard/Chess/ChessAction.hpp>

IndicatorSystem::IndicatorSystem(Ref<ChessBoard> &chessBoard, Ref<Scene> scene)
    : m_ChessBoard(chessBoard), m_Scene(scene), m_CurrentPlayer(PieceColor::WHITE)
{
}

void IndicatorSystem::OnUpdate(Timestep ts, entt::registry &registry)
{
    const auto view = registry.view<TransformComponent, SpriteRendererComponent, IndicatorComponent>();
    const auto& state = m_ChessBoard->GetState<ChessBoardState>();

    for(auto &&[entity, transform, sprite, indicator] : view.each())
    {
        auto state = m_ChessBoard->GetState<ChessBoardState>();
        if(indicator.testIdx >= 2)
        {

            continue;

        }
        else if(indicator.testIdx > 0)
        {
            sprite.Color.a = static_cast<float>(state->isCheck[indicator.testIdx - 1]);
            continue;
        }

        sprite.Color.a = state->selectedObj == nullptr? 0: 0.5f;
        
        if(Input::IsMouseButtonDown(Mouse::Any))
        {
            auto pos = Utils::ToScreenCoord(Input::GetMousePosition());

            pos = Utils::ToScreenToWorldCoord(pos, m_Scene->GetPrimaryCameraEntity());

            pos.x = static_cast<int>(pos.x + 0.5f);
            pos.y = static_cast<int>(pos.y + 0.5f);
            
            if(Input::IsMouseButtonDown(Mouse::ButtonLeft))
            {
                transform.Translation.x = pos.x;
                transform.Translation.y = pos.y;

                auto act = SelectAction({pos.x, pos.y}, m_CurrentPlayer);
                m_ChessBoard->ApplyAction(act);
            }
            else if(Input::IsMouseButtonDown(Mouse::ButtonRight))
            {
                if(state->selectedObj != nullptr)
                {
                    auto act = MoveAction({pos.x, pos.y}, m_CurrentPlayer);
                    // TODO: maybe delete, current just for single
                    if(m_ChessBoard->ApplyAction(act))
                    {
                        int color = (PieceColorToInt(m_CurrentPlayer) + 1) % 2;
                        m_CurrentPlayer = IntToPieceColor(color);
                    }
                }
            }
        }
        else
        {
        
            int axisX = -static_cast<int>(Input::IsKeyDown(Key::A)) + static_cast<int>(Input::IsKeyDown(Key::D));
            int axisY = -static_cast<int>(Input::IsKeyDown(Key::S)) + static_cast<int>(Input::IsKeyDown(Key::W));

            transform.Translation.x += axisX;
            transform.Translation.y += axisY;

            
            if(Input::IsKeyDown(Key::Space))
            {

            }
        }

    }
}