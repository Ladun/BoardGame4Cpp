#include "CustomComponent.hpp"

// TODO: Make macro;
template<>
void DawnStar::Scene::OnComponentAdded<ChessGraphicComponent>(DawnStar::Entity entity, ChessGraphicComponent& component)
{
    
}

template<>
void DawnStar::Scene::OnComponentAdded<TestComponent>(DawnStar::Entity entity, TestComponent& component)
{

}

template<>
void DawnStar::Scene::OnComponentAdded<IndicatorComponent>(DawnStar::Entity entity, IndicatorComponent& component)
{

}