#pragma once


#include <DawnBoard/Chess/ChessBoard.hpp>

#include "SceneWrapper.hpp"

using namespace DawnBoard::Chess;

class GameLayer;

class GameScene : public SceneWrapper
{
public:
    GameScene(GameLayer* layer);
    virtual ~GameScene() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
    
	std::string GetTextureNameByPieceType(PieceType type, PieceColor color);

// Content Method
public:
    void ResetBoard();

private:
    GameLayer* _layer;
	Ref<ChessBoard> _chessBoard;
};