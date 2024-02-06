#pragma once

#include <Game/Scene/SceneWrapper.hpp>

class GameLayer;

class RobbyScene : public SceneWrapper
{
public:
    RobbyScene(GameLayer* layer);
    virtual ~RobbyScene() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;

// Content method
public:
    void ControlLoadingScreen(bool run);

private:
    GameLayer* _layer;
    Entity _loadingScreen;
};