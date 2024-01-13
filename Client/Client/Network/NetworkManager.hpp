#pragma once

#include <DawnNet/Network/Service.hpp>
class NetworkManager : public DawnNet::Singleton<NetworkManager>
{
public:
    NetworkManager();
    ~NetworkManager();

    static void Init();
	template<typename Packet> 
    static void Send(Packet packet);

private:
    std::shared_ptr<DawnNet::ClientService> service;
};