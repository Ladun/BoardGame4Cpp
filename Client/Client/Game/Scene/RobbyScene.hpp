#pragma once

#include "SceneWrapper.hpp"

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

private:
    GameLayer* _layer;
};