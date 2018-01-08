#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ParallaxNodeExtras.h"
#include "proj.win32/Player.h"
#include <map>
//USING_NS_CC;

using namespace cocos2d;


class HelloWorld : public cocos2d::Layer
{
private:
	
	ParallaxNodeExtras * _background_para;
	CCTMXTiledMap * _tileMap;
	CCTMXLayer *_background;
	Player *player;
	void update(float dt);
	float randomValueBetween(float low, float high);
	bool onTouchBegan(Touch* touch, Event* unused_event) override;
	void onTouchEnded(Touch* touch, Event* unused_event) override;
	map<EventKeyboard::KeyCode, bool> keys;
	void CheckKeyBoard();
public:

	virtual bool init();
	void setViewPointCenter(Point position);
	static cocos2d::Scene* createScene();

	CREATE_FUNC(HelloWorld);



};

#endif // __HELLOWORLD_SCENE_H__
