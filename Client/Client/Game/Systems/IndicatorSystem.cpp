#include <pch.hpp>
#include "IndicatorSystem.hpp"

#include "../../Utils/Utils.hpp"
#include "CustomComponent.hpp"

#include <DawnBoard/Chess/ChessAction.hpp>

IndicatorSystem::IndicatorSystem(Ref<Scene>& scene, Ref<ChessBoard>& chessBoard)
    : SystemBase(scene), _chessBoard(chessBoard), _currentPlayer(PieceColor::WHITE)
{
}

void IndicatorSystem::OnUpdate(Timestep ts, entt::registry &registry)
{
    const auto view = registry.view<TransformComponent, SpriteRendererComponent, IndicatorComponent>();
    const auto& state = _chessBoard->GetState<ChessBoardState>();

    for(auto &&[entity, transform, sprite, indicator] : view.each())
    {
        auto state = _chessBoard->GetState<ChessBoardState>();
        if(indicator.testIdx >= 3)
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
            auto pos = ToScreenCoord(Input::GetMousePosition());

            pos = ScreenToWorldCoord(pos, _scene->GetPrimaryCameraEntity());

            pos.x = static_cast<int>(pos.x + 0.5f);
            pos.y = static_cast<int>(pos.y + 0.5f);

            if(pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7)
                continue;
            
            if(Input::IsMouseButtonDown(Mouse::ButtonLeft))
            {
                transform.Translation.x = pos.x;
                transform.Translation.y = pos.y;

                auto act = SelectAction({pos.x, pos.y}, _currentPlayer);
                _chessBoard->ApplyAction(act);
            }
            else if(Input::IsMouseButtonDown(Mouse::ButtonRight))
            {
                if(state->selectedObj != nullptr)
                {
                    auto act = MoveAction({pos.x, pos.y}, _currentPlayer);
                    // TODO: maybe delete, current just for single
                    if(_chessBoard->ApplyAction(act))
                    {
                        int color = (PieceColorToInt(_currentPlayer) + 1) % 2;
                        _currentPlayer = IntToPieceColor(color);
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