#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "spine/SkeletonRenderer.h"
#include "proj.win32/PLayerJump.h"
#include "proj.win32/PlayerParticle.h"
using namespace CocosDenshion;

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;



Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // Hien thi vong tron do cua object
	Vect gravity(0.0f, -1000.0f);
	scene->getPhysicsWorld()->setGravity(gravity);

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	//layer->setPhyWorld(scene->getPhysicsWorld());
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
int lastCombo = -1;
void HelloWorld::update(float dt)
{

	_background_para->setPosition(_background_para->getPosition() - Vec2(1, 0));
	_background_para->updatePosition();
	if (player1->mCurrentCombo != lastCombo)
	{
		if (player1->getPosition().x - this->getContentSize().width / 2 + gameLabel->getContentSize().width / 2 < 0)
		{
			lastCombo = player1->mCurrentCombo;
			gameLabel->setString(to_string(lastCombo));
			gameLabel->setPosition(gameLabel->getContentSize().width / 2 + 50, this->getContentSize().height - 100);
		}
		else
			gameLabel->setPosition(player1->getPosition().x - this->getContentSize().width / 2 + gameLabel->getContentSize().width / 2 + 50, this->getContentSize().height - 100);

	}
	setViewPointCenter(player1->getPosition());
	CheckKeyBoard();	
}
void HelloWorld::CheckKeyBoard()
{
	player1->keys = keys;
	player1->keysCombo = keysCombo;
	player1->timeCombo = timeCombo;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event)
{

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
	this->addChild(_background_para,2);
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
		boundBody->getShape(0)->setFriction(10.0f);
		boundBody->setDynamic(false);
		boundBody->getShape(0)->setRestitution(100.0f);
		boundBody->setContactTestBitmask(0x1);
		edgeSp->setPhysicsBody(boundBody);
		edgeSp->setPosition(Vec2(x_box, y_box));

		this->addChild(edgeSp); // Add vào Layer
	}

	


	
	player1 = new Player(this);
	player1->setTag(1);
	player1->getPhysicsBody()->setCategoryBitmask(0x01);    // 0010
	player1->getPhysicsBody()->setCollisionBitmask(0x02);   // 0001
	this->addChild(player1);
	

	player2 = new Player(this);
	player2->setTag(1);
	player2->setPosition(Vec2(300, 200));
	player2->getPhysicsBody()->setCategoryBitmask(0x01);    // 0010
	player2->getPhysicsBody()->setCollisionBitmask(0x01);   // 0001
	this->addChild(player2);
	
	player1->SetEnemy(player2);
	player2->SetEnemy(player1);

	gameLabel = Label::create("LabelTTF with Shadow", "fonts/SHOWG.TTF", 24);
	gameLabel->setString("kk");
	gameLabel->setTextColor(Color4B(237, 28, 36,255));
	gameLabel->enableOutline(Color4B::BLACK, 5);
	this->addChild(gameLabel,3);

	auto Touchlistener = EventListenerTouchOneByOne::create();
	Touchlistener->setSwallowTouches(true);
	Touchlistener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	Touchlistener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Touchlistener, this);


	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = true;
	
		keysCombo.push_back(keyCode);
		timeCombo.push_back(GetTickCount());
		
		
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = false;
		
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);
	

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(HelloWorld::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	this->scheduleUpdate();

	return true;

}

void HelloWorld::XoaChild(Node* sender)
{
	auto sprite = (Sprite *)sender;
	this->removeChild(sprite, true);
}

bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{


	auto ObjA = contact.getShapeA()->getBody()->getNode();

	auto ObjB = contact.getShapeB()->getBody()->getNode();



	if (ObjA->getTag() == 1 && ObjB->getTag() ==1)
	{
	
		player1->isCollider = true;
		player2->isCollider = true;

	}
	if (ObjA->getTag() == BRICK && ObjB->getTag() == 1 || ObjA->getTag() == 1 && ObjB->getTag() == BRICK)
	{
		if (ObjB->getTag() == 1)
		{
			Player *pl = (Player*)ObjB;
			pl->OnCollision(ObjA);
		}
		else
		{
			Player *pl = (Player*)ObjA;
			pl->OnCollision(ObjB);
		}
	}

	if (ObjA->getTag() == SHURIKEN && ObjB->getTag() ==1)
	{
		Player *pl = (Player*)ObjB;
		pl->OnCollision(ObjA);

	}
	if (ObjA->getTag() == RASENGAN && ObjB->getTag() == 1 || ObjA->getTag() == 1 && ObjB->getTag() == RASENGAN)
	{
		Player *pl;
		if(ObjA->getTag() == 1) 
			pl = (Player*)ObjA;
		else
			pl = (Player*)ObjB;
		pl->OnCollision(ObjA);
		PlayerParticle::CreateHit(contact.getContactData()->points[0], this);
	}


	return true;

}

bool HelloWorld::onContactSeparate(const PhysicsContact& contact)
{
	auto ObjA = contact.getShapeA()->getBody()->getNode();

	auto ObjB = contact.getShapeB()->getBody()->getNode();



	if (ObjA->getTag() == 1 && ObjB->getTag() == 1)
	{
		player1->isCollider = false;
		player2->isCollider = false;
	}
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
