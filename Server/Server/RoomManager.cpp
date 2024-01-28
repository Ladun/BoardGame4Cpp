#include "pch.hpp"
#include "RoomManager.hpp"
#include "GameSession.hpp"

Ref<Room> RoomManager::Create()
{
    static uint64 roomId = 1;
    WRITE_LOCK;
    
    Ref<Room> room = MakeShared<Room>(roomId, 2);
    roomId++;

    _rooms.insert({room->GetRoomId(), room});
    return room;
}

void RoomManager::Remove(uint64 roomId)
{
    WRITE_LOCK;
    if(_rooms.contains(roomId) == false)
    {
        // ASSERT
        return;
    }
    _rooms.erase(roomId);
}

Ref<Room> RoomManager::FindNoneFullRoom()
{
    READ_LOCK;
    // 현재는 가장 for-loop 돌면서 가장 처음 발견된 빈 룰을 반환
    for(auto& [key, room]: _rooms)
    {
        if(!room->IsFull())
        {
            return room;
        }
    }
    return nullptr;
}

Ref<Room> RoomManager::FindRoomById(uint64 roomId)
{
    READ_LOCK;

    if(_rooms.contains(roomId))
    {
        return _rooms.find(roomId)->second;
    }

    return nullptr;
}

bool RoomManager::CanEnterAnyRoom()
{
    READ_LOCK;
    
    for(auto& [key, room] : _rooms)
    {
        if(!room->IsFull())
        {
            return true;
        }
    }
    return false;
}
