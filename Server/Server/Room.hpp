#pragma once

#include <DawnBoard/Chess/ChessBoard.hpp>

#include "Player.hpp"

using namespace DawnBoard::Chess;

struct RoomInfo
{
	int 		color; // 0=WHITE, 1=BLACK
	Ref<Player> player;
};

class Room : public std::enable_shared_from_this<Room>
{

public:
	Room(uint64 roomId, uint32 maxPlayers);

	void Enter(Ref<Player> player);
	void Leave(Ref<Player> player);
	void Broadcast(SendBufferRef sendBuffer);


	uint64 GetRoomId() { return _roomId; }
	bool IsFull() { return _infos.size() == _maxPlayers; }

	Ref<ChessBoard> GetChessBoard() { return _chessBoard; }

private:
	uint64 _roomId;
	uint32 _maxPlayers;

	Map<uint64, RoomInfo> _infos;
	Ref<ChessBoard> _chessBoard;

};