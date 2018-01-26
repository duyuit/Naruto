#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerFightUp :public PlayerState
{
public:
	PlayerFightUp(PlayerData *playerData);
	void Update(float dt);

	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	void HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo);
	void OnCollision(Node* sender);
	virtual StateAction GetState();
	~PlayerFightUp();
};



