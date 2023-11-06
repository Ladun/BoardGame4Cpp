#pragma once

#include <DawnStar/DawnStar.hpp>

using namespace DawnStar;

class TestSystem : public SystemBase
{
protected:
    virtual void OnUpdate(Timestep ts, entt::registry& registry) override;
};