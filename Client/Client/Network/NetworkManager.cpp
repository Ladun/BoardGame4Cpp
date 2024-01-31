#include <pch.hpp>
#include <DawnNet/Concurrency/ThreadManager.hpp>
#include <DawnNet/Network/IOContext.hpp>
#include "NetworkManager.hpp"
#include "GameSession.hpp"
#include "ServerPacketHandler.hpp"

NetworkManager::NetworkManager()
    : service(nullptr)
{
    
}

NetworkManager::~NetworkManager()
{
    
}

void NetworkManager::Init(GameLayer* layer)
{
    gameLayer = layer;
    ServerPacketHandler::Init();
    
    for(int i = 0; i < 2; i++)
    {
        DawnNet::GThreadManager->Launch([](){
            DawnNet::IOContext::Instance().Run();
            // Join은 App의 소멸자에서 진행
        });
    }
}

bool NetworkManager::Connect(std::string host, std::string port)
{
    if(service == nullptr)
    {
        service = MakeShared<DawnNet::ClientService>(
            MakeShared<GameSession>,
            host, port
        );
    }

    if(!service->Start())
    {
        return false;
    }

    return true;
}
