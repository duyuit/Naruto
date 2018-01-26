#pragma once
#include "2d/CCSprite.h"
#include "tinyxml2/tinyxml2.h"
#include "3d/CCAnimate3D.h"
#include "base/CCRefPtr.h"
#include "PlayerState.h"
#include "PlayerDtate.h"
using namespace cocos2d;
using namespace std;
class Player:public cocos2d::Sprite
{
public:
	Player();
	Player(Layer *parent);
	~Player();

	RefPtr<Animate>  *mCurrentAnimate;
	PlayerState *mCurrentState;
	PlayerData *mData;
	map<EventKeyboard::KeyCode, bool> keys;
	vector<EventKeyboard::KeyCode> keysCombo; 
	vector<float> timeCombo;
	int mCurrentFrame = 0;
	bool isLeft = false;
	bool isCollider = false;
	Player* enemy;
	int mCurrentCombo = 0;

	static Vector<SpriteFrame*> loadAnim(char* path, string key);
	void SetState(PlayerState *action);			//Set State by new State(mData)
	void SetStateByTag(PlayerState::StateAction action); //Set state by put type of State
	void update(float delta) override;
	void XoaChild(Node* sender);
	void OnCollision(Node* sender);
	void SetEnemy(Player* enemy);
	
	RECT GetBound();
	CREATE_FUNC(Player);
	void ChangeIDLE();
	void ChangeJump();
	void AddPosition(Vec2 pos);

private:

	RefPtr<Animate> *idleAnimate;
	RefPtr<Animate> *jumpAnimate;
	RefPtr<Animate> *runAnimate;
	RefPtr<Animate> *fightAnimate,*fightUpAnimate,*fightDownAnimate;
	RefPtr<Animate>  *throwStand;
	RefPtr<Animate>  *throwJump;
	RefPtr<Animate>  *fightRun;
	RefPtr<Animate>  *hurtAnimate,*hurtFly;
	RefPtr<Animate>  *rasengan1;
	RefPtr<Animate>  *dustAnimate;
	RefPtr<Animate> *comboAnimate;

	RefPtr<Animate> *testne;

	Action* mCurrentAction;



};

