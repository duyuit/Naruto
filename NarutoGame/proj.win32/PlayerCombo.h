#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerCombo :public PlayerState
{
public:
	PlayerCombo(PlayerData *playerData);
	~PlayerCombo();
	void Update(float dt);

	void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	void HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo);
	int lastFrame = 0;

	bool combo1 = false;
	bool combo2 = false;
	bool combo3 = false;
	void OnCollision(Node* sender);
	Player* target=nullptr;
	virtual StateAction GetState();
};

