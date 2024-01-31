#include <pch.hpp>
#include <DawnStar/DawnStar.hpp>
#define DS_PLATFORM_WINDOWS
#include <DawnStar/Core/EntryPoint.hpp>

#include <DawnNet/Concurrency/ThreadManager.hpp>

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
        DawnNet::GThreadManager->Join();   
    }
};

DawnStar::Application* DawnStar::CreateApplication()
{
    return new GameApp();
};