#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerThrowStand :public PlayerState
{
public:
	PlayerThrowStand(PlayerData *playerData);
	~PlayerThrowStand();
	void Update(float dt);

	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);

	virtual StateAction GetState();
	

};


