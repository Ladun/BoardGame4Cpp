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
    
    DS_APP_DEBUG("Board graphic Update");
    // Board update
    const auto view2 = registry.view<SpriteRendererComponent, ChessBoardComponent>();
    for(auto &&[entity, sprite, chessBoardCom] : view2.each())
    {
        ChessBoardState* state = m_ChessBoard->GetState<ChessBoardState>();
        BoardInfo info = state->square[chessBoardCom.y][chessBoardCom.x];

        if(chessBoardCom.back)
        {    
            int color = PieceColorToInt(state->currentColor) ;
            sprite.Color = {glm::vec3(color - 0.2f * (color - 0.5f) * 2), 1.0f};
        }
        else 
        {

            if(info.boardSelected)
            {
                sprite.Color = (chessBoardCom.x + chessBoardCom.y) % 2 == 1? 
                                BOARD_BRIGHT_SELECTED_COLOR :
                                BOARD_DARK_SELECTED_COLOR;
            }
            else
            {
                sprite.Color = (chessBoardCom.x + chessBoardCom.y) % 2 == 1? 
                                BOARD_BRIGHT_COLOR :
                                BOARD_DARK_COLOR;
            }
        }
    }

    m_ChessBoard->GetState<ChessBoardState>()->needRender = false;
}