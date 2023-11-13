#pragma once

#include <DawnStar/DawnStar.hpp>

#include <DawnBoard/Chess/ChessBoard.hpp>

using namespace DawnStar;
using namespace DawnBoard::Chess;

const glm::vec4 BOARD_BRIGHT_COLOR = glm::vec4(.98f, .83f, .64f, 1.0f);
const glm::vec4 BOARD_DARK_COLOR = glm::vec4(.82f, .66f, .43f, 1.f);
const glm::vec4 BOARD_BRIGHT_SELECTED_COLOR = glm::vec4(.91f, .91f, .41f, 1.f);
const glm::vec4 BOARD_DARK_SELECTED_COLOR = glm::vec4(.83f, .83f, .35f, 1.f);

class ChessGraphicSystem : public SystemBase
{
public:
    ChessGraphicSystem(Ref<ChessBoard>& chessBoard, Ref<Scene> scene);

protected:
    virtual void OnUpdate(Timestep ts, entt::registry& registry) override;

private:
    Ref<ChessBoard> m_ChessBoard;
    Ref<Scene> m_Scene;

};