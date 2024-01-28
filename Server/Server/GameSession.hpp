#pragma once

#include <DawnNet/Network/Service.hpp>
#include "Player.hpp"
#include "Room.hpp"

class GameSession : public PacketSession
{
public:
	~GameSession()
	{
	}

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;

public:
	Ref<Player> _player;

	std::weak_ptr<Room> _room;
};