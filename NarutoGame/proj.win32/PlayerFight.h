#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerFight :public PlayerState
{
public:
	~PlayerFight();
	PlayerFight(PlayerData *playerData);
	void Update(float dt);

	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	void HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo);
	void OnCollision(Node* sender);
	int CountCombo = 0;
	virtual StateAction GetState();
};

