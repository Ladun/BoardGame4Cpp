#include <DawnStar/dspch.hpp>
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
    // Piece update
    const auto view1 = registry.view<TransformComponent, SpriteRendererComponent, ChessPieceComponent>();
    bool updateSpriteOrder = false;
    for(auto it = view1.begin(); it != view1.end();)
    {
        auto &&[transform, sprite, pieceInfo] = view1.get(*it);
        if(pieceInfo.piece->m_Captured)
        {
            _scene->DestroyEntity({*it, _scene.get()});
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
            it++;                                     
        }
    }
    if(updateSpriteOrder)
        _scene->SortForSprites();

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