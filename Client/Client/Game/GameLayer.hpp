#pragma once

#include <DawnStar/DawnStar.hpp>
#include <DawnStar/Debug/RenderStatPanel.hpp>
#include <DawnStar/Debug/ObjectListPanel.hpp>

#include <DawnBoard/Chess/ChessBoard.hpp>

#include "Scene/SceneWrapper.hpp"

using namespace DawnStar;

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event& e) override;

	void ChangeScene(std::string name);

private:
	bool OnWindowResize(WindowResizeEvent& e);
	bool OnMouseMoved(MouseMovedEvent& e);

	Ref<SceneWrapper> GetSceneByName(std::string name);

private:
	RenderStatPanel _statPanel;
	ObjectListPanel _objListPanel;
	
	std::map<std::string, Ref<SceneWrapper>> _scenes; 
	Ref<SceneWrapper> _currentScene;
};