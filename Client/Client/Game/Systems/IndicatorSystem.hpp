#pragma once

#include <DawnStar/DawnStar.hpp>

#include <DawnBoard/Chess/ChessBoard.hpp>

#include <Game/Scene/GameScene.hpp>

using namespace DawnStar;
using namespace DawnBoard::Chess;

class IndicatorSystem : public SystemBase
{
public:
    IndicatorSystem(Ref<Scene>& scene, Ref<SceneWrapper> sceneWrapper, Ref<ChessBoard>& chessBoard);

protected:
    virtual void OnUpdate(Timestep ts, entt::registry& registry) override;

    Ref<GameScene> GetGameScene() { return static_pointer_cast<GameScene>(_sceneWrapper); }
private:
    Ref<ChessBoard> _chessBoard;
    Ref<SceneWrapper> _sceneWrapper;
};