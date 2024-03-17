#pragma once


#include <DawnBoard/Chess/ChessBoard.hpp>

#include <Game/Scene/SceneWrapper.hpp>
#include <Network/NetworkManager.hpp>

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
    void ApplyAction(Protocol::S_ACTION& pkt);

    PieceColor GetPlayerColor() { return _playerColor; }
    void SetPlayerColor(PieceColor color) { _playerColor = color; }

private:
    GameLayer* _layer;
    Entity _indicator;
    Entity _colorIndicator;

	Ref<ChessBoard> _chessBoard;
    PieceColor      _playerColor;
};