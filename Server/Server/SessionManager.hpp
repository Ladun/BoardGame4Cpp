#pragma once

#include "GameSession.hpp"

class SessionManager : public Singleton<SessionManager>
{
public:
    void Add(Ref<GameSession> session);
    void Remove(Ref<GameSession> session);
    void BroadCast(SendBufferRef sendBuffer);

private:
    Set<Ref<GameSession>> _sessions;
};