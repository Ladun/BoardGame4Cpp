
#pragma once

class GameSession;

class Player
{
public:
	uint64					playerId = 0;
	std::string				name;
    
	Ref<GameSession>		ownerSession; // Cycle

};