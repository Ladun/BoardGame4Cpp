#include "pch.hpp"
#include "SessionManager.hpp"
#include "GameSession.hpp"
#include "Player.hpp"


void SessionManager::Add(Ref<GameSession> session)
{
	_sessions.insert(session);
}

void SessionManager::Remove(Ref<GameSession> session)
{
	_sessions.erase(session);
}

void SessionManager::BroadCast(SendBufferRef sendBuffer)
{
	for (auto session : _sessions)
	{
		session->Send(sendBuffer);
	}
}