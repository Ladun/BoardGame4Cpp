#include <DawnStar/DawnStar.hpp>
#define DS_PLATFORM_WINDOWS
#include <DawnStar/Core/EntryPoint.hpp>

#include "Game/GameLayer.hpp"

class GameApp: public DawnStar::Application
{
public:
    GameApp()
        : Application("BoardGame4cpp", 800, 600)
    {
        PushLayer(new GameLayer());
    }
    ~GameApp()
    {
        
    }
};

DawnStar::Application* DawnStar::CreateApplication()
{
    return new GameApp();
};