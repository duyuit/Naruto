#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerIDLE:public PlayerState
{
public:
	PlayerIDLE(PlayerData *playerData);
	~PlayerIDLE();
	void Update(float dt);

	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	void HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo);
	void OnCollision(Node* sender);
	virtual StateAction GetState();
};

