#pragma once

#include "PlayerState.h"
#include "Player.h"
class PlayerHurt :public PlayerState
{
public:
	PlayerHurt(PlayerData *playerData);
	~PlayerHurt();
	void Update(float dt);
	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);

	virtual StateAction GetState();
};