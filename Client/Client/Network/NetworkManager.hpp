#pragma once

#include "ServerPacketHandler.hpp"

class NetworkManager : public DawnNet::Singleton<NetworkManager>
{
public:
    NetworkManager();
    ~NetworkManager();

    void Init();
    bool Connect(std::string host, std::string port);
	template<typename Packet> 
    void Send(Packet packet)
    {
        auto sendBuffer = DawnNet::ServerPacketHandler::MakeSendBuffer(packet);
        service->Broadcast(sendBuffer);
    }

private:
    DawnNet::ClientServiceRef service;
};
