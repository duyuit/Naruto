#pragma once

#include "PlayerState.h"
#include "Player.h"
class PLayerJump :public PlayerState
{
public:
	PLayerJump(PlayerData *playerData);
	~PLayerJump();
	void Update(float dt);
	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	void OnCollision(Node* sender);
	virtual StateAction GetState();
};




