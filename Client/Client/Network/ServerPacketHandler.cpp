#include <pch.hpp>
#include "ServerPacketHandler.hpp"

#include "NetworkManager.hpp"
#include <Game/Scene/RobbyScene.hpp>
#include <Game/Scene/GameScene.hpp>

#include <DawnBoard/Chess/ChessObject.hpp>

using namespace DawnBoard::Chess;

namespace DawnNet
{
	PacketHandlerFunc GPacketHandler[UINT16_MAX];

	// 직접 컨텐츠 작업자

	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		return false;
	}

	bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
	{
		return true;
	}

	bool Handle_S_JOIN(PacketSessionRef& session, Protocol::S_JOIN& pkt)
	{
		const auto layer = NetworkManager::Instance().GetLayer();

		// If current scene is not "Robby", it's wrong packet
		if(layer->GetCurrentScene()->GetName() != "Robby")
		{
			return true;
		}

		if(pkt.success())
		{
			layer->ChangeScene("Game");
			auto scene = static_pointer_cast<GameScene>(layer->GetCurrentScene());

			scene->SetPlayerColor(IntToPieceColor(pkt.currentplayercolor()));
		}
		else
		{
			static_pointer_cast<RobbyScene>(layer->GetCurrentScene())->ControlLoadingScreen(false);
		}

		return true;
	}

	bool Handle_S_ACTION(PacketSessionRef& session, Protocol::S_ACTION& pkt)
	{
		const auto layer = NetworkManager::Instance().GetLayer();
		// If current scene is not "Robby", it's wrong packet
		if(layer->GetCurrentScene()->GetName() != "Game")
		{
			return true;
		}
		static_pointer_cast<GameScene>(layer->GetCurrentScene())->ApplyAction(pkt);
		

		return true;
	}

	bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
	{
		std::cout << pkt.nickname() << ": " << pkt.msg() << std::endl;
		return true;
	}
}