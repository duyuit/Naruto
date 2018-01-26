#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerRun :public PlayerState
{
public:
	PlayerRun(PlayerData *playerData);
	~PlayerRun();
	void Update(float dt);

	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);

	virtual StateAction GetState();
};

