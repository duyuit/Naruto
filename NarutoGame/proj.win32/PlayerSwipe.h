#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerSwipe :public PlayerState
{
public:
	PlayerSwipe(PlayerData *playerData);
	~PlayerSwipe();
	void Update(float dt);
	float alpha = 0;
	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	void HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo);
	virtual StateAction GetState();
};



