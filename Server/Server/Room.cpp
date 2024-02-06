#include "pch.hpp"
#include "Room.hpp"
#include "GameSession.hpp"
#include "ClientPacketHandler.hpp"

#include <random>


Room::Room(uint64 roomId, uint32 maxPlayers) 
    : _roomId(roomId), _maxPlayers(maxPlayers)
{

	_chessBoard = MakeShared<ChessBoard>();
    _chessBoard->Init();
    
}

void Room::Enter(Ref<Player> player)
{
    // TODO: test code. maybe this code move to other func
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    int color;
    if(_infos.size() == _maxPlayers - 1)
    {
        auto iter = _infos.end();
        iter--;
        color = !iter->second.color; 
    }
    else
    {
        color = dist(gen);
    }

    _infos.insert({player->playerId, {color, player}});
    player->ownerSession->_room = shared_from_this();
    
    // Send Packet
    Protocol::S_JOIN joinPkt;
    joinPkt.set_success(true);		
    joinPkt.set_currentplayercolor(color);
    
    auto sendBuffer = ClientPacketHandler::MakeSendBuffer(joinPkt);
    player->ownerSession->Send(sendBuffer);
}

void Room::Leave(Ref<Player> player)
{
    if(_infos.contains(player->playerId) == false)
    {
        // ASSERT
        return;
    }
    _infos.erase(player->playerId);
    player->ownerSession->_room.reset();
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
    for(auto& [key, info] : _infos)
    {
        info.player->ownerSession->Send(sendBuffer);
    }
}
