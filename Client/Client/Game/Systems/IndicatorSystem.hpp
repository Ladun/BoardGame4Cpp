#pragma once

#include <DawnStar/DawnStar.hpp>

#include <DawnBoard/Chess/ChessBoard.hpp>

using namespace DawnStar;
using namespace DawnBoard::Chess;

class IndicatorSystem : public SystemBase
{
public:
    IndicatorSystem(Ref<Scene>& scene, Ref<ChessBoard>& chessBoard);

protected:
    virtual void OnUpdate(Timestep ts, entt::registry& registry) override;

private:
    Ref<ChessBoard> _chessBoard;

    // TODO: test code, for single
    PieceColor _currentPlayer;

};