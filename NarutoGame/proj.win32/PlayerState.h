#pragma once
#include  "PlayerDtate.h"
#include <map>
#include "base/CCEventKeyboard.h"
#include "vector"
using namespace std;
using namespace cocos2d;
class PlayerState
{
public:
	enum StateAction
	{
		IDLE,SWIPE,
		RUN,
		JUMP,
		FIGHT, FIGHTUP,FIGHTDOWN,
		COMBO,
		THROWSTAND,
		THROWJUMP,
		RASENGAN1,
		HURT,
		HURTFLY
	};

	virtual StateAction GetState()=0;
	virtual void Update(float dt);
	virtual void HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys);
	virtual void HandleCombo( vector<EventKeyboard::KeyCode> keysCombo,  vector<float> timeCombo);
	virtual void OnCollision(Node* sender);
	PlayerState();
	~PlayerState();

protected:
	PlayerState(PlayerData *playerData);
	PlayerData *mPlayerData;
	float lastUpdate = 0;
};


