#include <DawnNet/pch.hpp>
#include "NetworkManager.hpp"
#include "GameSession.hpp"

NetworkManager::NetworkManager()
{
    service = DawnNet::MakeShared<DawnNet::ClientService>(
        DawnNet::MakeShared<GameSession>,
        "", ""
    );
}

NetworkManager::~NetworkManager()
{
    
}

void NetworkManager::Init()
{
    
}