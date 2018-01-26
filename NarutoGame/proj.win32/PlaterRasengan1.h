#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerRasengan1 :public PlayerState
{
public:
	PlayerRasengan1(PlayerData *playerData);
	~PlayerRasengan1();
	void Update(float dt);


	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	virtual StateAction GetState();
};

