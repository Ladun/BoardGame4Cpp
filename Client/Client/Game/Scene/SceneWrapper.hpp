#pragma once

#include <DawnStar/DawnStar.hpp>

using namespace DawnStar;

class SceneWrapper
{
public:
    SceneWrapper(std::string name) 
        : _name(name)
    {
        _scene = CreateRef<Scene>();
    }
    virtual ~SceneWrapper() = default;

    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;

	virtual void OnUpdate(Timestep ts) = 0;
	virtual void OnImGuiRender() = 0;

    Ref<Scene>& GetScene() { return _scene; }
    std::string GetName() { return _name; }

protected:
    std::string _name;
    Ref<Scene> _scene;

};