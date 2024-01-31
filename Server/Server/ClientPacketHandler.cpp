#include "pch.hpp"
#include "ClientPacketHandler.hpp"
#include "SessionManager.hpp"
#include "GameSession.hpp"
#include "Player.hpp"
#include "RoomManager.hpp"

#include <DawnNet/Network/IOContext.hpp>

namespace DawnNet
{

	PacketHandlerFunc GPacketHandler[UINT16_MAX];

	// 직접 컨텐츠 작업자

	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		return false;
	}

	bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
	{
		// Return player list to client
		// Player list를 다음과 같이 가져오면 문제점이 하나 있음
		// sessionManager의 _sessions에 별도의 lock을 걸지 않고 가져오니 Race Condition에 걸릴 수 있음
		/* 
		Vector<Ref<Player>> players;
		for(auto session: SessionManager::Instance()._session)
		{
			players.push_back(session->_player);
		}
		*/
		// 근데 현재 동기화 관련 작업은 IOContext::Post로 처리하고 있어서 어떻게 처리해야 할지 고민
		// Post는 JobQueue같은 느낌으로 strand 오브젝트를 통해서 작업을 모아서 순차적으로 실행하는 것이다.
		// 따라서 별도의 충돌이 일어날 일이 없다.
		// Lock이랑 Post를 둘 다 쓴다? 그럴바에 그냥 Lock만 쓰는게 낫지 않을까?

		return true;
	}

	bool Handle_C_JOIN(PacketSessionRef& session, Protocol::C_JOIN& pkt)
	{
		Ref<GameSession> gameSession = static_pointer_cast<GameSession>(session);

		Ref<Room> room;
		// If there no room or rooms are already full.
		if(RoomManager::Instance().CanEnterAnyRoom() == false)
		{
			// Make room
			room = RoomManager::Instance().Create();
		}
		// else find room can enter
		else
		{
			room = RoomManager::Instance().FindNoneFullRoom();
		}

		// Enter room
		IOContext::Instance().Post(std::bind(
			&Room::Enter, 
			room.get(), gameSession->_player
		));

		// Send Packet
		Protocol::S_JOIN joinPkt;
		joinPkt.set_success(true);		
		
		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(joinPkt);
		session->Send(sendBuffer);

		return true;
	}

	bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt)
	{
		std::cout << pkt.nickname() << ": " << pkt.msg() << std::endl;

		Protocol::S_CHAT chatPkt;
		chatPkt.set_nickname(pkt.nickname());
		chatPkt.set_msg(pkt.msg());
		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);

		SessionManager::Instance().BroadCast(sendBuffer);
		IOContext::Instance().Post(std::bind(
			&SessionManager::BroadCast, 
			&SessionManager::Instance(), sendBuffer
		));

		return true;
	}
}