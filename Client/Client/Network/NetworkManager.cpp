#include <DawnNet/pch.hpp>
#include <DawnNet/Network/Service.hpp>

#include "NetworkManager.hpp"
#include "GameSession.hpp"


NetworkManager::NetworkManager()
    : service(nullptr)
{
    
}

NetworkManager::~NetworkManager()
{
    
}

void NetworkManager::Init()
{
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
