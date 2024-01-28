#pragma once

#include "Room.hpp"

class RoomManager : public Singleton<RoomManager>
{
public:
    Ref<Room> Create();
    void Remove(uint64 roomId);
    
    Ref<Room> FindNoneFullRoom(); // TODO: remove or modify
    Ref<Room> FindRoomById(uint64 roomId);

    bool CanEnterAnyRoom();

private:
    USE_LOCK;
    Map<uint64, Ref<Room>> _rooms;
};