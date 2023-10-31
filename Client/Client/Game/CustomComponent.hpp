#pragma once

#include <DawnStar/Scene/Scene.hpp>
#include <DawnStar/Scene/Entity.hpp>



struct ChessComponent
{
    bool a;

};
template<>
void DawnStar::Scene::OnComponentAdded<ChessComponent>(DawnStar::Entity entity, ChessComponent& component)
{
    
}