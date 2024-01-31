#include <pch.hpp>
#include <DawnStar/DawnStar.hpp>
#include "GameSession.hpp"
#include "ServerPacketHandler.hpp"

#include <Network/NetworkManager.hpp>
#include <Game/Scene/RobbyScene.hpp>

void GameSession::OnConnected()
{
    // Protocol::C_LOGIN pkt;
    // auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
    // Send(sendBuffer);

    DS_APP_DEBUG("Connect to {0}", Socket().remote_endpoint().address().to_string());
    
    const auto layer = NetworkManager::Instance().GetLayer();
    static_pointer_cast<RobbyScene>(layer->GetCurrentScene())->ControlLoadingScreen(false);
}

void GameSession::OnDisconnected()
{
    DS_APP_DEBUG("disconnected");
}

void GameSession::OnRecvPacket(BYTE *buffer, int32 len)
{
    DawnNet::PacketSessionRef session = GetPacketSessionRef();
    DawnNet::PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

    DS_APP_DEBUG("{0} packet recieved", header->id);
    ServerPacketHandler::HandlePacket(session, buffer, len);

}

void GameSession::OnSend(int32 len)
{
    DS_APP_DEBUG("{0} packet send", len);
}
