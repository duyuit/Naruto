#include "Player.h"
#include "spine/AttachmentVertices.h"

using namespace cocos2d;


Player::Player()
{
}

Player::Player(Layer *parent)
{
	Vector<SpriteFrame*> standFrameList = loadAnim("narutoAction.xml", "idle");
	Vector<SpriteFrame*> jumpFrameList = loadAnim("narutoAction.xml", "jump");
	Vector<SpriteFrame*> runFrameList = loadAnim("narutoAction.xml", "run");
	Vector<SpriteFrame*> fightFrameList = loadAnim("narutoAction.xml", "fight");
	Vector<SpriteFrame*> throwStandFrameList = loadAnim("narutoAction.xml", "throwstand");
	Vector<SpriteFrame*> throwJumpFrameList = loadAnim("narutoAction.xml", "throwJump");
	Vector<SpriteFrame*> fightUpFrameList = loadAnim("narutoAction.xml", "fightUp");

	Vector<SpriteFrame*> rasengan1FrameList = loadAnim("narutoAction.xml", "rasengan1");
	Vector<SpriteFrame*> dustFrameList = loadAnim("rasengan1.xml", "dust1");
	


	idleAnimation = Animation::createWithSpriteFrames(standFrameList, 0.08f);
	jumpAnimation= Animation::createWithSpriteFrames(jumpFrameList, 0.05f);
	idleAnimate = new RefPtr<Animate>(Animate::create(idleAnimation));
	jumpAnimate =new RefPtr<Animate>(Animate::create(jumpAnimation));
	runAnimate= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFrameList, 0.07f)));
	fightAnimate= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFrameList, 0.07f)));
	throwStand = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(throwStandFrameList, 0.07f)));
	throwJump= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(throwJumpFrameList, 0.07f)));
	fightRun = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightUpFrameList, 0.05f)));

	rasengan1 = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(rasengan1FrameList, 0.04f)));
	dustAnimate= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dustFrameList, 0.15f)));
	//runAnimate->get()->setResetFrame(3);
	//jumpping->autorelease();
	//standing->autorelease();
	//running->autorelease();

	this->initWithSpriteFrame(standFrameList.at(0));
	this->setPosition(100,200);
	this->setAnchorPoint(Vec2(0.5,0));
	auto player_body = PhysicsBody::createBox(this->getContentSize());

	player_body->setContactTestBitmask(0x1);
	player_body->setRotationEnable(false);
	player_body->setDynamic(true);
	player_body->getShape(0)->setRestitution(0.0f);//đàn hồi
	this->setPhysicsBody(player_body);

	
	
	dust = Sprite::createWithSpriteFrame(dustFrameList.at(0));
	dust->setAnchorPoint(Vec2(1, 0));
	dust->setVisible(false);
	parent->addChild(dust);
}

void Player::Jump()
{
	if (currentState == JUMP) return;
	this->stopAllActions();
	if( currentState == THROWJUMP)
	this->getPhysicsBody()->setVelocity(Vec2(this->getPhysicsBody()->getVelocity().x, 200));
	auto temp = jumpAnimate->get();
	temp->setTag(JUMP);
	this->runAction(temp);
	currentState = JUMP;

	
	runAnimate->get()->ResetAnimate();
	throwJump->get()->ResetAnimate();
}

void Player::Stand()
{
	if (currentState == IDLE) return;
	
	this->stopAllActions();
	this->runAction(RepeatForever::create(idleAnimate->get()));
	//this->runAction(runAnimate->get());
	currentState = IDLE;

	jumpAnimate->get()->ResetAnimate();
	runAnimate->get()->ResetAnimate();
	fightAnimate->get()->ResetAnimate();
	fightRun->get()->ResetAnimate();
	throwStand->get()->ResetAnimate();
}

void Player::Run()
	{
	if (currentState == THROWSTAND || currentState==THROWJUMP || currentState == FIGHT) return;
	float y = this->getPhysicsBody()->getVelocity().y;
	if (currentState != RUN)
	{
		this->stopAllActions();
		if (abs(y) > 0)
		{
			Jump();
			return;
		}
		this->runAction(RepeatForever::create(runAnimate->get()));
		dust->runAction(RepeatForever::create(dustAnimate->get()));
	}

	jumpAnimate->get()->ResetAnimate();
	currentState = RUN;
}

void Player::Fight()
{
	if (currentState == FIGHT) return;
	this->stopAllActions();
	if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] || keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
	{
		this->runAction(fightRun->get());
		fightAnimate->get()->ResetAnimate();
	}
	else
	{
		this->runAction(fightAnimate->get());
		fightRun->get()->ResetAnimate();
	}
	currentState = FIGHT;
}

void Player::ThrowStand()
{
	if (currentState == THROWSTAND) return;
	if (currentState != IDLE && currentState != RUN) return;
	this->stopAllActions();
	this->runAction(throwStand->get());	

	currentState = THROWSTAND;
	
}

void Player::ThrowJump()
{
	if (currentState == THROWJUMP) return;

	this->stopAllActions();
	this->runAction(throwJump->get());
	currentState = THROWJUMP;


	jumpAnimate->get()->ResetAnimate();
}

void Player::Rasengan1()
{
	if (currentState != IDLE ) return;
	this->stopAllActions();
	this->runAction(rasengan1->get());
	
	currentState = RASENGAN1;
}

Vector<SpriteFrame*> Player::loadAnim(char* path, string key)
{
	Vector<SpriteFrame*> list;

	tinyxml2::XMLDocument xml_doc;
	tinyxml2::XMLError eResult = xml_doc.LoadFile(path);

	tinyxml2::XMLElement* root = xml_doc.RootElement();
	tinyxml2::XMLElement* child = root->FirstChildElement();
	while (child)
	{
		if (child->Attribute("name") == key)
		{
			tinyxml2::XMLElement* ele = child->FirstChildElement();
			while (ele)
			{
				float x;
				ele->QueryFloatAttribute("x", &x);
				float y;
				ele->QueryFloatAttribute("y", &y);
				float w;
				ele->QueryFloatAttribute("w", &w);
				float h;
				ele->QueryFloatAttribute("h", &h);


				list.pushBack(SpriteFrame::create(child->Attribute("imagePath"), Rect(x, y, w, h)));

				ele = ele->NextSiblingElement();
			}
			break;
		}
		child = child->NextSiblingElement();
	}




	return list;

}
bool isActive = false;
void Player::update(float delta)
{
	bool checkIDLE = false;
	dust->setVisible(false);
	float x = this->getPhysicsBody()->getVelocity().x;
	float y = this->getPhysicsBody()->getVelocity().y;
	
	//if (abs(y) <10  && abs(x) <1 && currentState!=IDLE) Stand();
	if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
	{
		Run();
		isLeft = true;
		this->setFlipX(isLeft);
		this->setPosition(this->getPosition() - Vec2(5, 0));
		this->getPhysicsBody()->setVelocity(Vec2(-1, y));
		
		
		checkIDLE = true;
	}
	if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
	{
		
		Run();
		this->setFlipX(isLeft);
		isLeft = false;
		this->setPosition(this->getPosition() + Vec2(5, 0));
		this->getPhysicsBody()->setVelocity(Vec2(1, y));
		checkIDLE = true;
	}
	if (keys[EventKeyboard::KeyCode::KEY_SPACE])
	{
		Jump();
		this->getPhysicsBody()->setVelocity(Vec2(x, 150));
		checkIDLE = true;
	}
	if (keys[EventKeyboard::KeyCode::KEY_E])
	{
			Fight();
			checkIDLE = true;	
	}
	if (keys[EventKeyboard::KeyCode::KEY_R])
	{

		Rasengan1();
		checkIDLE = true;

	}
	if (keys[EventKeyboard::KeyCode::KEY_Q])
	{
		if(currentState==IDLE)
			ThrowStand();
		if (currentState == JUMP)
			ThrowJump();
		checkIDLE = true;

	}
	switch (currentState)
	{
	case IDLE:
		break;
	case RUN:
		dust->setVisible(true);
		if (isLeft)
		{
			dust->setPosition(this->getPosition() + Vec2(20, 0));
			dust->setAnchorPoint(Vec2(0, 0));
		}
		else
		{
			dust->setPosition(this->getPosition() + Vec2(-20, 0));
			dust->setAnchorPoint(Vec2(1, 0));
		}
		dust->setFlipX(isLeft);
		break;
	case JUMP:
		if (y == 0)
		{
			jumpAnimate->get()->setLockFrame(-1);
			Stand();
		}
		else
			if (jumpAnimate->get()->getCurrentFrameIndex() >= 2)
				jumpAnimate->get()->setLockFrame(2);
			checkIDLE = true;
		break;
	case THROWJUMP:
		if (throwJump->get()->getCurrentFrameIndex() == throwJump->get()->getAnimation()->getFrames().size() - 1)
		{
			Jump();
			checkIDLE = true;
			break;
		}
		if (throwJump->get()->getCurrentFrameIndex() == 1 && GetTickCount() - lastUpdate >= 200)
		{
			auto shuriken = Sprite::create("shuriken.png");
			this->getParent()->addChild(shuriken);
			auto shuriken_body = PhysicsBody::createBox(shuriken->getContentSize());
			shuriken_body->setDynamic(false);
			shuriken->setPhysicsBody(shuriken_body);
			if (isLeft)
			{
				shuriken->setPosition(this->getPosition() + Vec2(-this->getContentSize().width / 2, this->getContentSize().height / 2));
				auto move = MoveTo::create(1.5f,Vec2(shuriken->getPosition().x-400,0));
				auto rotate = RotateTo::create(1.5f, -360 * 6);

				shuriken->runAction(rotate);
				shuriken->runAction(Sequence::create(
					move,
					CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, this)), NULL));
			}
			else
			{
				shuriken->setPosition(this->getPosition() + this->getContentSize() / 2);
				auto move = MoveTo::create(1.5f, Vec2(shuriken->getPosition().x + 400, 0));
				auto rotate = RotateTo::create(1.5f, 360 * 6);

				shuriken->runAction(rotate);
				shuriken->runAction(Sequence::create(
					move,
					CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, this)), NULL));
			}
			lastUpdate = GetTickCount();
		 checkIDLE = true;
		}
		break;
	case FIGHT:
		if (fightAnimate->get()->getCurrentFrameIndex() == fightAnimate->get()->getAnimation()->getFrames().size() - 1) Stand();
		else checkIDLE = true;
		if (fightRun->get()->getCurrentFrameIndex() == fightRun->get()->getAnimation()->getFrames().size() - 1) Stand();
		else checkIDLE = true;
		break;
	case THROWSTAND:	
		if (throwStand->get()->getCurrentFrameIndex() == throwStand->get()->getAnimation()->getFrames().size() - 1) Stand();
		else checkIDLE = true;
		if(throwStand->get()->getCurrentFrameIndex() == 1&& GetTickCount()-lastUpdate>=200)
		{
			
			auto shuriken = Sprite::create("shuriken.png");
			this->getParent()->addChild(shuriken);
			auto shuriken_body = PhysicsBody::createBox(shuriken->getContentSize());
			shuriken_body->setDynamic(false);
			shuriken->setPhysicsBody(shuriken_body);
			if (isLeft)
			{
				shuriken->setPosition(this->getPosition() + Vec2(-this->getContentSize().width / 2, this->getContentSize().height / 2));
				auto move = MoveTo::create(1.5f, shuriken->getPosition() + Vec2(-400, 0));
				auto rotate = RotateTo::create(1.5f, -360 * 6);

				shuriken->runAction(rotate);
				shuriken->runAction(Sequence::create(
					move,
					CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, this)), NULL));
			}
			else
			{
				shuriken->setPosition(this->getPosition() + this->getContentSize() / 2);
				auto move = MoveTo::create(1.5f, shuriken->getPosition() + Vec2(400, 0));
				auto rotate = RotateTo::create(1.5f, 360 * 6);

				shuriken->runAction(rotate);
				shuriken->runAction(Sequence::create(
					move,
					CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, this)), NULL));
			}
			lastUpdate = GetTickCount();

		}
		break;
	case RASENGAN1:
	//59
		
			if (rasengan1->get()->getCurrentFrameIndex() <=40)
			{
				if(isLeft)
					this->setAnchorPoint(Vec2(0, 0));
				else
				this->setAnchorPoint(Vec2(1, 0));
			}
			else
			{
				this->setAnchorPoint(Vec2(0.5, 0));
			}
			if(rasengan1->get()->getCurrentFrameIndex()==51 && GetTickCount()-lastUpdate>500)
			{
				Vector<SpriteFrame*> rasengan1Object = loadAnim("rasengan1.xml", "move");
				Sprite* rasengan = Sprite::createWithSpriteFrame(rasengan1Object.at(0));
				this->getParent()->addChild(rasengan);
				
				auto rasengan_body = PhysicsBody::createBox(rasengan->getContentSize());
				rasengan_body->setDynamic(false);
				rasengan->setPhysicsBody(rasengan_body);

				Vector<SpriteFrame*> soilObject = loadAnim("rasengan1.xml", "soil");
				Sprite* soil = Sprite::createWithSpriteFrame(soilObject.at(0));
				soil->setAnchorPoint(Vec2(0.5, 0));
				this->getParent()->addChild(soil);
				rasengan->setFlipX(isLeft);
				soil->setFlipX(isLeft);
				if (isLeft)
				{
					rasengan->setPosition(this->getPosition() + Vec2(-this->getContentSize().width / 2, this->getContentSize().height / 2 + 10));
					rasengan->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(rasengan1Object, 0.1f))));
					rasengan->runAction(Sequence::create(
						MoveTo::create(1, rasengan->getPosition() + Vec2(-400, 0)),
						CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, this)), NULL));

					soil->setPosition(this->getPosition() + Vec2(-this->getContentSize().width / 2, -10));
					soil->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(soilObject, 0.06f))));
					soil->runAction(Sequence::create(
						MoveTo::create(1, soil->getPosition() + Vec2(-400, 0)),
						CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, this)), NULL));
				}else
				{
					rasengan->setPosition(this->getPosition() + Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 10));
					rasengan->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(rasengan1Object, 0.1f))));
					rasengan->runAction(Sequence::create(
						MoveTo::create(1, rasengan->getPosition() + Vec2(400, 0)),
						CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, this)), NULL));

					soil->setPosition(this->getPosition() + Vec2(this->getContentSize().width / 2, -10));
					soil->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(soilObject, 0.06f))));
					soil->runAction(Sequence::create(
						MoveTo::create(1, soil->getPosition() + Vec2(400, 0)),
						CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, this)), NULL));
					
				}

				lastUpdate = GetTickCount();
			}
			break;
	}
	
	if (!checkIDLE) Stand();
}

void Player::XoaChild(Node* sender)
{
	auto sprite = (Sprite *)sender;
	this->getParent()->removeChild(sprite, true);
}

Player::~Player()
{
}
