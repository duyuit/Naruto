#pragma once

#include "PlayerState.h"
#include "Player.h"
class PlayerHurtFly :public PlayerState
{
public:
	PlayerHurtFly(PlayerData *playerData);
	void Update(float dt);
	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	void OnCollision(Node* sender);
	virtual StateAction GetState();
	~PlayerHurtFly();
};

