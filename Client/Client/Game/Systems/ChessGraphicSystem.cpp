#include <DawnStar/dspch.hpp>
#include "ChessGraphicSystem.hpp"

#include "../../Utils/Utils.hpp"
#include "CustomComponent.hpp"

#include <DawnBoard/Chess/ChessBoardState.hpp>

ChessGraphicSystem::ChessGraphicSystem(Ref<ChessBoard> &chessBoard, Ref<Scene> scene)
    : m_ChessBoard(chessBoard), m_Scene(scene)
{
}

void ChessGraphicSystem::OnUpdate(Timestep ts, entt::registry &registry)
{
    // TODO: Add "Update your graphics components only when your chessboard is updated";

    // Piece update
    const auto view1 = registry.view<TransformComponent, ChessPieceComponent>();
    for(auto &&[entity, transform, pieceInfo] : view1.each())
    {
        transform.Translation = {pieceInfo.piece->m_Pos.x, 
                                 pieceInfo.piece->m_Pos.y, 
                                 transform.Translation.z};

    }
    
    // Board update
    const auto view2 = registry.view<SpriteRendererComponent, ChessBoardComponent>();
    for(auto &&[entity, sprite, boardInfo] : view2.each())
    {
        ChessBoardState* state = m_ChessBoard->GetState<ChessBoardState>();
        BoardInfo info = state->square[boardInfo.y][boardInfo.x];

        if(info.boardSelected)
        {
            sprite.Color = (boardInfo.x + boardInfo.y) % 2 == 1? 
                            BOARD_BRIGHT_SELECTED_COLOR :
                            BOARD_DARK_SELECTED_COLOR;
        }
        else
        {
            sprite.Color = (boardInfo.x + boardInfo.y) % 2 == 1? 
                            BOARD_BRIGHT_COLOR :
                            BOARD_DARK_COLOR;
        }
    }
}