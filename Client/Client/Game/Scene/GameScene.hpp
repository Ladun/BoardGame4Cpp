#pragma once

#include <DawnStar/Debug/RenderStatPanel.hpp>
#include <DawnStar/Debug/ObjectListPanel.hpp>

#include <DawnBoard/Chess/ChessBoard.hpp>

#include "SceneWrapper.hpp"

using namespace DawnBoard::Chess;

class GameScene : public SceneWrapper
{
public:
    GameScene();
    virtual ~GameScene() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
    
	std::string GetTextureNameByPieceType(PieceType type, PieceColor color);

private:
	RenderStatPanel _statPanel;
	ObjectListPanel _objListPanel;
    
	Ref<ChessBoard> _chessBoard;
};