#pragma once

#include "ServerPacketHandler.hpp"
#include "../Game/GameLayer.hpp"

#include <DawnNet/Network/Service.hpp>

class NetworkManager : public DawnNet::Singleton<NetworkManager>
{
public:
    NetworkManager();
    ~NetworkManager();

    void Init(GameLayer* layer);
    bool Connect(std::string host, std::string port);

	template<typename Packet> 
    void Send(Packet packet)
    {
        auto sendBuffer = DawnNet::ServerPacketHandler::MakeSendBuffer(packet);
        service->Broadcast(sendBuffer);
    }

public:
    GameLayer* GetLayer() { return gameLayer; }

private:
    DawnNet::ClientServiceRef service;
    GameLayer* gameLayer;
};
