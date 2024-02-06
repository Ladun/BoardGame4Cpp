#pragma once
#include "Packet/Protocol.pb.h"

namespace DawnNet
{

	using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
	extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

	enum : uint16
	{
		PKT_C_LOGIN = 1000,
		PKT_S_LOGIN = 1001,
		PKT_C_JOIN = 1002,
		PKT_S_JOIN = 1003,
		PKT_C_ACTION = 1004,
		PKT_S_ACTION = 1005,
		PKT_C_CHAT = 1006,
		PKT_S_CHAT = 1007,
	};

	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
	bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt);
	bool Handle_C_JOIN(PacketSessionRef& session, Protocol::C_JOIN& pkt);
	bool Handle_C_ACTION(PacketSessionRef& session, Protocol::C_ACTION& pkt);
	bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt);


	class ClientPacketHandler
	{
	public:
		static void Init()
		{
			for (int32 i = 0; i < UINT16_MAX; i++)
				GPacketHandler[i] = Handle_INVALID;
			GPacketHandler[PKT_C_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_LOGIN>(Handle_C_LOGIN, session, buffer, len); };
			GPacketHandler[PKT_C_JOIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_JOIN>(Handle_C_JOIN, session, buffer, len); };
			GPacketHandler[PKT_C_ACTION] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ACTION>(Handle_C_ACTION, session, buffer, len); };
			GPacketHandler[PKT_C_CHAT] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_CHAT>(Handle_C_CHAT, session, buffer, len); };
		}

		static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
		{
			PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
			return GPacketHandler[header->id](session, buffer, len);
		}
		static SendBufferRef MakeSendBuffer(Protocol::S_LOGIN& pkt) { return MakeSendBuffer(pkt, PKT_S_LOGIN); }
		static SendBufferRef MakeSendBuffer(Protocol::S_JOIN& pkt) { return MakeSendBuffer(pkt, PKT_S_JOIN); }
		static SendBufferRef MakeSendBuffer(Protocol::S_ACTION& pkt) { return MakeSendBuffer(pkt, PKT_S_ACTION); }
		static SendBufferRef MakeSendBuffer(Protocol::S_CHAT& pkt) { return MakeSendBuffer(pkt, PKT_S_CHAT); }

	private:
		template<typename PacketType, typename ProcessFunc>
		static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
		{
			PacketType pkt;
			if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
				return false;

			return func(session, pkt);
		}

		template<typename T>
		static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
		{
			const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
			const uint16 packetSize = dataSize + sizeof(PacketHeader);

			SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
			PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
			header->size = packetSize;
			header->id = pktId;
			pkt.SerializeToArray(&header[1], dataSize);
			// ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
			sendBuffer->Close(packetSize);

			return sendBuffer;
		}
	};
}