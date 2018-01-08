#pragma once
#include "2d/CCSprite.h"
#include "tinyxml2/tinyxml2.h"
#include "3d/CCAnimate3D.h"
#include "base/CCRefPtr.h"

using namespace cocos2d;
using namespace std;
class Player:public cocos2d::Sprite
{
public:
	Player();
	Player(Layer *parent);
	~Player();
	enum StateAction
	{
		IDLE,
		RUN,
		JUMP,
		FIGHT,
		THROWSTAND,
		THROWJUMP,
		RASENGAN1
	};

	void Jump();
	void Stand();
	void Run();
	void Fight();
	void ThrowStand();
	void ThrowJump();
	void Rasengan1();
	StateAction currentState;
	map<EventKeyboard::KeyCode, bool> keys;
	void update(float delta) override;
	void XoaChild(Node* sender);
	CREATE_FUNC(Player);
private:
	Vector<SpriteFrame*> loadAnim(char* path, string key);
	Animation* idleAnimation, *jumpAnimation, *runAnimation;
	RefPtr<Animate> *idleAnimate;
    RefPtr<Animate> *jumpAnimate;
	RefPtr<Animate> *runAnimate;
	RefPtr<Animate> *fightAnimate;
	RefPtr<Animate>  *throwStand;
	RefPtr<Animate>  *throwJump;
	RefPtr<Animate>  *fightRun;
	RefPtr<Animate>  *rasengan1;
	RefPtr<Animate>  *dustAnimate;
	Sprite* dust;
	float lastUpdate = 0;
	float lastThrow = 0;
	bool isLeft = false;
};

