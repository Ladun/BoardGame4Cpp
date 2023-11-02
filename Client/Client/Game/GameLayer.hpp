#pragma once

#include <DawnStar/DawnStar.hpp>
#include <DawnStar/Debug/RenderStatPanel.hpp>
#include <DawnBoard/Chess/Logic/ChessBoard.hpp>

// TODO: move to DawnStar/Debug/ObjectListPanel.hpp
#include "../Utils/ObjectListPanel.hpp"

using namespace DawnStar;
using namespace DawnBoard::Chess;

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Event& e) override;

	std::string GetTextureNameByPieceType(PieceType type, PieceColor color);

private:
	bool OnWindowResize(WindowResizeEvent& e);

private:
	RenderStatPanel m_StatPanel;
	ObjectListPanel m_ObjListPanel;

	Ref<ChessBoard> m_ChessBoard;

	Ref<Scene> m_Scene;
};