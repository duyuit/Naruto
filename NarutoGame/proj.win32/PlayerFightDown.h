#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerFightDown :public PlayerState
{
public:
	PlayerFightDown(PlayerData *playerData);
	void Update(float dt);

	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	void HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo);
	virtual StateAction GetState();
	void OnCollision(Node* sender);
	bool isDone = false;
	~PlayerFightDown();
};


