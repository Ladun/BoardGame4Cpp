#include <pch.hpp>
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
