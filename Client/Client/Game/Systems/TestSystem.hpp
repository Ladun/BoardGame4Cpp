#pragma once

#include <DawnStar/DawnStar.hpp>

using namespace DawnStar;

class TestSystem : public SystemBase
{
public: 
    TestSystem(Ref<Scene>& scene) : SystemBase(scene) {}
protected:
    virtual void OnUpdate(Timestep ts, entt::registry& registry) override;
};