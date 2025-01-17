#include <pch.hpp>
#include "ChessGraphicSystem.hpp"

#include "../../Utils/Utils.hpp"
#include "CustomComponent.hpp"

#include <DawnBoard/Chess/ChessBoardState.hpp>

ChessGraphicSystem::ChessGraphicSystem(Ref<Scene>& scene, Ref<ChessBoard>& chessBoard)
    : SystemBase(scene), _chessBoard(chessBoard)
{
}

void ChessGraphicSystem::OnUpdate(Timestep ts, entt::registry &registry)
{
    // TODO: King 움직이면 오류 생김.
    // Piece update
    const auto view1 = registry.view<TransformComponent, SpriteRendererComponent, ChessPieceComponent>();
    bool updateSpriteOrder = false;
    for(auto it = view1.begin(); it != view1.end(); it++)
    {
        auto &&[transform, sprite, pieceInfo] = view1.get(*it);
        if(pieceInfo.piece->m_Captured)
        {
            if(pieceInfo.captured)
                continue;
            pieceInfo.captured = true;
            
            if(pieceInfo.piece->m_Color == PieceColor::BLACK)
            {
                transform.Translation = {_blackCaptured % _capturedMaxColumn + 8.5, -_blackCaptured / _capturedMaxColumn, 0};
                _blackCaptured++;
            }
            else
            {
                transform.Translation = {_whiteCaptured % _capturedMaxColumn + 8.5, _whiteCaptured / _capturedMaxColumn + 7, 0};
                _whiteCaptured++;
            }
        }
        else
        {

            if(pieceInfo.currentPos != pieceInfo.piece->m_Pos &&
               !pieceInfo.doAnimation && pieceInfo.time < 0.1f)
            {
                pieceInfo.doAnimation = true;
                sprite.SortingOrder = 1;

                updateSpriteOrder = true;
            }

            float dstX = pieceInfo.currentPos.x;
            float dstY = pieceInfo.currentPos.y;

            if(pieceInfo.doAnimation)
            {
                dstX += (pieceInfo.piece->m_Pos.x - pieceInfo.currentPos.x) * pieceInfo.time;
                dstY += (pieceInfo.piece->m_Pos.y - pieceInfo.currentPos.y) * pieceInfo.time;
                pieceInfo.time += ts / pieceInfo.animTime;
                if(pieceInfo.time > 1.0f)
                {
                    pieceInfo.time = 0.0f;
                    pieceInfo.doAnimation = false;
                    pieceInfo.currentPos = pieceInfo.piece->m_Pos;
                    sprite.SortingOrder = 0;

                    updateSpriteOrder = true;
                }
            }            

            transform.Translation = {dstX, dstY, pieceInfo.doAnimation};
        }
    }
    if(updateSpriteOrder)
    {
	    _scene->SortComponents<SpriteRendererComponent>(
            [](const auto& lhs, const auto& rhs)
            {
                return lhs.SortingOrder < rhs.SortingOrder;
            });
    }

    // for(auto &&[entity, transform, pieceInfo] : view1.each())
    // {
    //     transform.Translation = {pieceInfo.piece->m_Pos.x, 
    //                              pieceInfo.piece->m_Pos.y, 
    //                              transform.Translation.z};
    // }
    
    // Board update
    const auto view2 = registry.view<SpriteRendererComponent, ChessBoardComponent>();
    for(auto &&[entity, sprite, chessBoardCom] : view2.each())
    {
        ChessBoardState* state = _chessBoard->GetState<ChessBoardState>();
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
}