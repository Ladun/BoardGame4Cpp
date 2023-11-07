#pragma once

#include <DawnStar/DawnStar.hpp>

#include <DawnBoard/Chess/Logic/ChessBoard.hpp>

using namespace DawnStar;
using namespace DawnBoard::Chess;

class IndicatorSystem : public SystemBase
{
public:
    IndicatorSystem(Ref<ChessBoard>& chessBoard, Ref<Scene> scene);

protected:
    virtual void OnUpdate(Timestep ts, entt::registry& registry) override;

private:
    Ref<ChessBoard> m_ChessBoard;
    Ref<Scene> m_Scene;

};