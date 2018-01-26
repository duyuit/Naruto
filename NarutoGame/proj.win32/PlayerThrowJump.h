#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerThrowJump :public PlayerState
{
public:
	PlayerThrowJump(PlayerData *playerData);
	~PlayerThrowJump();
	void Update(float dt);

	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	virtual StateAction GetState();
};




