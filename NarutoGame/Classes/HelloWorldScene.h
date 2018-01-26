#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ParallaxNodeExtras.h"
#include "proj.win32/Player.h"
#include <map>
#include "../../proj.win32/GameComponents/GameLog.h"
//USING_NS_CC;

using namespace cocos2d;



class HelloWorld : public cocos2d::Layer
{
private:
	
	ParallaxNodeExtras * _background_para;
	CCTMXTiledMap * _tileMap;
	CCTMXLayer *_background;
	Player *player1;
	Player *player2;
	Label* gameLabel;

	void update(float dt);
	float randomValueBetween(float low, float high);
	bool onTouchBegan(Touch* touch, Event* unused_event) override;
	void onTouchEnded(Touch* touch, Event* unused_event) override;
	
	void CheckKeyBoard();
	bool onContactBegin(const PhysicsContact &contact);
	bool onContactSeparate(const PhysicsContact &contact);

public:
	map<EventKeyboard::KeyCode, bool> keys;
	vector<EventKeyboard::KeyCode> keysCombo;
	vector<float> timeCombo;

	virtual bool init();
	void XoaChild(Node* sender);
	void setViewPointCenter(Point position);
	static cocos2d::Scene* createScene();

	static enum ObjectType
	{
		PLAYER,
		BRICK,
		SHURIKEN,
		RASENGAN
	};
	CREATE_FUNC(HelloWorld);


	float lastUpdate = 0;
};

#endif // __HELLOWORLD_SCENE_H__
