#pragma once

#include "Player.hpp"

class Room : public std::enable_shared_from_this<Room>
{

public:
	Room(uint64 roomId, uint32 maxPlayers);

	void Enter(Ref<Player> player);
	void Leave(Ref<Player> player);
	void Broadcast(SendBufferRef sendBuffer);


	uint64 GetRoomId() { return _roomId; }
	bool IsFull() { return _players.size() == _maxPlayers; }

private:
	uint64 _roomId;
	Map<uint64, Ref<Player>> _players;

	uint32 _maxPlayers;
};