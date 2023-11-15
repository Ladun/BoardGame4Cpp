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
    if(!m_ChessBoard->GetState<ChessBoardState>()->needRender)
        return;

    // Piece update
    const auto view1 = registry.view<TransformComponent, ChessPieceComponent>();
    for(auto it = view1.begin(); it != view1.end();)
    {
        auto &&[transform, pieceInfo] = view1.get(*it);
        if(pieceInfo.piece->m_Captured)
        {
            m_Scene->DestroyEntity({*it, m_Scene.get()});
        }
        else
        {
            transform.Translation = {pieceInfo.piece->m_Pos.x, 
                                     pieceInfo.piece->m_Pos.y, 
                                     transform.Translation.z};
            it++;                                     
        }
    }

    // for(auto &&[entity, transform, pieceInfo] : view1.each())
    // {
    //     transform.Translation = {pieceInfo.piece->m_Pos.x, 
    //                              pieceInfo.piece->m_Pos.y, 
    //                              transform.Translation.z};

    // }
    
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

    m_ChessBoard->GetState<ChessBoardState>()->needRender = false;
}