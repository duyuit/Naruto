#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "spine/SkeletonRenderer.h"
using namespace CocosDenshion;

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;



Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // Hien thi vong tron do cua object
	Vect gravity(0.0f, -600.0f);
	scene->getPhysicsWorld()->setGravity(gravity);

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	//layer->setPhyWorld(scene->getPhysicsWorld());
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

float delta = 0;
void HelloWorld::update(float dt)
{
	
		_background_para->setPosition(_background_para->getPosition() - Vec2(1, 0));
		_background_para->updatePosition();
		setViewPointCenter(player->getPosition());
		CheckKeyBoard();
		//player->update(dt);

	

}
void HelloWorld::CheckKeyBoard()
{
	player->keys = keys;
	
		
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event)
{
	/*Vec2 touchLocation = touch->getLocationInView();
	auto moveAction = MoveTo::create(3, touchLocation);
	player->runAction(moveAction);
	return true;*/
	//auto touchPoint = touch->getLocation();
	//touchPoint = this->convertToNodeSpace(touchPoint);
	//float s = player->getPosition().distance(touchPoint);
	//auto moveAction = MoveTo::create(s/100.0f, touchPoint);
	//player->runAction(moveAction);

	player->Jump();

	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* unused_event)
{
}



bool HelloWorld::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size size = _director->getVisibleSize();

	_background_para = ParallaxNodeExtras::create();
	this->addChild(_background_para, 10);
	for (int i = 0; i<2; i++)
	{
		auto cloud = Sprite::create("cloud.png");
		cloud->setScale(0.5, 0.5);
		_background_para->addChild(cloud, 0, Vec2(1, 0), Vec2(i*(cloud->getContentSize().width), size.height*randomValueBetween(0.7, 0.9)));
	}
	for (int i = 0; i<2; i++)
	{
		auto cloud = Sprite::create("cloud2.png");
		cloud->setScale(0.5, 0.5);
		_background_para->addChild(cloud, 0, Vec2(1, 0), Vec2(i*(cloud->getContentSize().width), size.height*randomValueBetween(0.7, 0.9)));
	}


	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("untitled.tmx");
	this->addChild(_tileMap);
	TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Objects");


	for (int i = 0; i<objectGroup->getObjects().size(); i++)
	{

		Value objectemp = objectGroup->getObjects().at(i);

		float wi_box = objectemp.asValueMap().at("width").asFloat();
		float he_box = objectemp.asValueMap().at("height").asFloat();
		float x_box = objectemp.asValueMap().at("x").asFloat() + wi_box / 2;
		float y_box = objectemp.asValueMap().at("y").asFloat() + he_box / 2;

		auto edgeSp = Sprite::create();
		auto boundBody = PhysicsBody::createBox(Size(wi_box, he_box));

		boundBody->setDynamic(false);
		boundBody->getShape(0)->setRestitution(1.0f);
		boundBody->setContactTestBitmask(0x1);
		edgeSp->setPhysicsBody(boundBody);
		edgeSp->setPosition(Vec2(x_box, y_box));

		this->addChild(edgeSp); // Add vào Layer
	}

	


	
	player = new Player(this);
	this->addChild(player);
	player->Stand();
	



	auto Touchlistener = EventListenerTouchOneByOne::create();
	Touchlistener->setSwallowTouches(true);
	Touchlistener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	Touchlistener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Touchlistener, this);


	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = true;
	};
	
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = false;
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);
	this->scheduleUpdate();

	return true;

}

void HelloWorld::setViewPointCenter(Point position)
{

	Size winSize = _director->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Vec2 actualPosition = Vec2(x, y);

	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}

float HelloWorld::randomValueBetween(float low, float high)
{
	return (((float)rand() / RAND_MAX) * (high - low)) + low;
}
