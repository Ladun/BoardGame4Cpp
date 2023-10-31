#pragma once

#include <DawnStar/DawnStar.hpp>

using namespace DawnStar;

class ObjectListPanel
{
public:
    ObjectListPanel(Ref<Scene>& targetScene);
    ~ObjectListPanel() = default;

    void OnImGuiRender();

private:
    Ref<Scene> m_TargetScene;
};    
