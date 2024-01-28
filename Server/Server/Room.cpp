#include "pch.hpp"
#include "Room.hpp"
#include "GameSession.hpp"

Room::Room(uint64 roomId, uint32 maxPlayers) 
    : _roomId(roomId), _maxPlayers(maxPlayers)
{

}

void Room::Enter(Ref<Player> player)
{
    _players.insert({player->playerId, player});
    player->ownerSession->_room = shared_from_this();
}

void Room::Leave(Ref<Player> player)
{
    if(_players.contains(player->playerId) == false)
    {
        // ASSERT
        return;
    }
    _players.erase(player->playerId);
    player->ownerSession->_room.reset();
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
    for(auto& [key, player] : _players)
    {
        player->ownerSession->Send(sendBuffer);
    }
}
