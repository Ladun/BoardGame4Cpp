#include "pch.hpp"
#include "GameSession.hpp"
#include "SessionManager.hpp"
#include "ClientPacketHandler.hpp"
#include "Player.hpp"

#include <DawnNet/Network/IOContext.hpp>

void GameSession::OnConnected()
{
    Ref<GameSession> gameSession = std::static_pointer_cast<GameSession>(shared_from_this());
    IOContext::Instance().Post(std::bind(
        &SessionManager::Add, 
        &SessionManager::Instance(), gameSession
    ));

    std::cout << Socket().remote_endpoint().address().to_string() << " connected\n";

    // Create player data
    static Atomic<uint64> playerId = 1;

    _player = MakeShared<Player>();
    _player->playerId = playerId;
    playerId.fetch_add(1);
    _player->name = "Test";
    _player->ownerSession = gameSession;
}

void GameSession::OnDisconnected()
{
    IOContext::Instance().Post(std::bind(
        &SessionManager::Remove, 
        &SessionManager::Instance(), std::static_pointer_cast<GameSession>(shared_from_this())
    ));
    std::cout << "disconnected\n";
}

void GameSession::OnRecvPacket(BYTE *buffer, int32 len)
{
    PacketSessionRef session = GetPacketSessionRef();
    DawnNet::PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    
    std::cout << header->id << " Packet recieved\n";
    ClientPacketHandler::HandlePacket(session, buffer, len);

}

void GameSession::OnSend(int32 len)
{
    std::cout << len << " Packet send\n";
}
