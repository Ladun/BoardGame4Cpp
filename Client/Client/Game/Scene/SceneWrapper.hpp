#pragma once

#include <DawnStar/DawnStar.hpp>

using namespace DawnStar;

class SceneWrapper
{
public:
    SceneWrapper() = default;
    virtual ~SceneWrapper() = default;

    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;

	virtual void OnUpdate(Timestep ts) = 0;
	virtual void OnImGuiRender() = 0;

    Ref<Scene> GetScene() { return _scene; }

protected:
    Ref<Scene> _scene;

};