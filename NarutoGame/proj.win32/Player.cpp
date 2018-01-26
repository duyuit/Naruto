#include "Player.h"
#include "spine/AttachmentVertices.h"
#include "PlayerIDLE.h"
#include "PlayerRun.h"
#include "PlayerHurt.h"
#include "PlayerHurtFly.h"
#include "HelloWorldScene.h"
#include "PLayerJump.h"
#include "PlayerSwipe.h"
#include "PlayerFight.h"
#include "PlayerFightUp.h"
#include "PlayerFightDown.h"
#include "PlayerCombo.h"
#include "PlayerThrowStand.h"
#include "PlayerThrowJump.h"
#include "PlaterRasengan1.h"
#include "PlayerParticle.h"

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
	Vector<SpriteFrame*> fightRunFrameList = loadAnim("narutoAction.xml", "fightRun"); 	Vector<SpriteFrame*> fightUpFrameList = loadAnim("narutoAction.xml", "fightUp"); Vector<SpriteFrame*> fightDownFrameList = loadAnim("narutoAction.xml", "fightJump");
	Vector<SpriteFrame*> hurtFrameList = loadAnim("narutoAction.xml", "hurt");
	Vector<SpriteFrame*> hurtFlyFrameList = loadAnim("narutoAction.xml", "hurtFly");
	Vector<SpriteFrame*> rasengan1FrameList = loadAnim("narutoAction.xml", "rasengan1");
	Vector<SpriteFrame*> comboFrameList = loadAnim("narutoAction.xml", "Combo");
	Vector<SpriteFrame*> dustFrameList = loadAnim("rasengan1.xml", "dust1");


	Vector<SpriteFrame*> tesst = Player::loadAnim("particle.xml", "fallFire");
	testne = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(tesst, 0.1f)));
	

	

	//Khai bao animate
	comboAnimate= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(comboFrameList, 0.1f)));
	hurtFly = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(hurtFlyFrameList, 0.1f)));
	hurtAnimate = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(hurtFrameList, 0.07f)));
	idleAnimate = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(standFrameList, 0.08f)));
	jumpAnimate =new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(jumpFrameList, 0.05f)));
	runAnimate= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(runFrameList, 0.07f)));
	fightAnimate= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightFrameList, 0.07f))); 	fightUpAnimate = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightUpFrameList, 0.07f))); 	fightDownAnimate = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightDownFrameList, 0.07f)));
	throwStand = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(throwStandFrameList, 0.07f)));
	throwJump= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(throwJumpFrameList, 0.07f)));
	fightRun = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(fightRunFrameList, 0.05f)));
	rasengan1 = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(rasengan1FrameList, 0.04f)));
	dustAnimate= new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dustFrameList, 0.15f)));


	this->initWithSpriteFrame(standFrameList.at(0));
	this->setPosition(100,200);
	this->setAnchorPoint(Vec2(0.5,0));
	this->setScale(1.5,1.5);

	
	auto verti = PhysicsBody::createBox(Size(this->getContentSize().width-20,this->getContentSize().height));
	verti->setContactTestBitmask(0x1);
	verti->setRotationEnable(false);
	verti->setDynamic(true);
	verti->getShape(0)->setRestitution(0.0f);//đàn hồi
	this->setPhysicsBody(verti);

	
	
	//dust = Sprite::createWithSpriteFrame(dustFrameList.at(0));
	//dust->setAnchorPoint(Vec2(1, 0));
	//dust->setVisible(false);
	//parent->addChild(dust);

	this->mData = new PlayerData();
	this->mData->player = this;
	mCurrentState = new PlayerIDLE(mData);
	mCurrentAnimate = idleAnimate;
	mCurrentAction = mCurrentAnimate->get();
	SetState(new PlayerHurt(mData));


}



void Player::SetState(PlayerState *state)
{
	if(mCurrentState!=NULL && mCurrentState != nullptr)
	delete mCurrentState;
	if(mCurrentAnimate != NULL && mCurrentAnimate != nullptr)
	mCurrentAnimate->get()->ResetAnimate();

	mCurrentState = state;
	this->stopAction(mCurrentAction);
	switch (mCurrentState->GetState())
	{
	case PlayerState::IDLE:
	
		//this->getPhysicsBody()->setRotationOffset(0);
		this->getPhysicsBody()->setPositionOffset(Vec2(0, 0));
		
		mCurrentAnimate = idleAnimate;
		mCurrentAction = RepeatForever::create(mCurrentAnimate->get());
	

		break;
	case PlayerState::RUN:
		mCurrentAnimate = runAnimate;
		mCurrentAction = RepeatForever::create(mCurrentAnimate->get());
		break;
	case PlayerState::RASENGAN1:
		mCurrentAnimate = rasengan1;
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::JUMP:
		this->getPhysicsBody()->setPositionOffset(Vec2(0, 0));
		mCurrentAnimate = jumpAnimate;
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::FIGHT:
		mCurrentAnimate = fightAnimate;
		if (isLeft)
			this->getPhysicsBody()->setPositionOffset(Vec2(-10, 0));
		else
			this->getPhysicsBody()->setPositionOffset(Vec2(10, 0));
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::THROWSTAND:
		mCurrentAnimate = throwStand;
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::THROWJUMP:
		mCurrentAnimate = throwJump;
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::HURT:
		mCurrentAnimate = hurtAnimate;
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::HURTFLY:
	/*	this->getPhysicsBody()->setRotationOffset(90);
		this->getPhysicsBody()->setPositionOffset(Vec2(0, -this->getContentSize().width/2));*/
		mCurrentAnimate = hurtFly;
		mCurrentAnimate->get()->setLockFrame(1);
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::FIGHTUP:
		mCurrentAnimate = fightUpAnimate;
		if (isLeft)
			this->getPhysicsBody()->setPositionOffset(Vec2(-20, 0));
		else
			this->getPhysicsBody()->setPositionOffset(Vec2(20, 0));
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::FIGHTDOWN:
		mCurrentAnimate = fightDownAnimate;
		if (isLeft)
			this->getPhysicsBody()->setPositionOffset(Vec2(-20, 0));
		else
			this->getPhysicsBody()->setPositionOffset(Vec2(20, 0));
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::SWIPE:
		mCurrentAnimate = runAnimate;
		mCurrentAction = mCurrentAnimate->get();
		break;
	case PlayerState::COMBO:
		mCurrentAnimate = comboAnimate;
		mCurrentAction = mCurrentAnimate->get();
		break;
	}
	this->runAction(mCurrentAction);
}

void Player::SetStateByTag(PlayerState::StateAction action)
{
	switch (action) { 
	case PlayerState::IDLE: 
		this->SetState(new PlayerIDLE(mData));
		break;
	case PlayerState::SWIPE:this->SetState(new PlayerSwipe(mData)); break;
	case PlayerState::RUN:this->SetState(new PlayerRun(mData)); break;
	case PlayerState::JUMP:this->SetState(new PLayerJump(mData)); break;
	case PlayerState::FIGHT: this->SetState(new PlayerFight(mData)); break;
	case PlayerState::FIGHTUP:this->SetState(new PlayerFightUp(mData)); break;
	case PlayerState::FIGHTDOWN:this->SetState(new PlayerFightDown(mData)); break;
	case PlayerState::COMBO:this->SetState(new PlayerCombo(mData)); break;
	case PlayerState::THROWSTAND:this->SetState(new PlayerThrowStand(mData)); break;
	case PlayerState::THROWJUMP:this->SetState(new PlayerThrowJump(mData)); break;
	case PlayerState::RASENGAN1:this->SetState(new PlayerRasengan1(mData)); break;
	case PlayerState::HURT:this->SetState(new PlayerHurt(mData)); break;
	case PlayerState::HURTFLY:this->SetState(new PlayerHurtFly(mData)); break;
	default: ; }
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

	this->setFlipX(isLeft);
	mCurrentState->HandleCombo(keysCombo, timeCombo);
	mCurrentState->HandleKeyboard(keys);
	mCurrentFrame = mCurrentAnimate->get()->getCurrentFrameIndex();
	if (isCollider)
		OnCollision(enemy);
	mCurrentState->Update(delta);

}

void Player::XoaChild(Node* sender)
{
	auto sprite = (Sprite *)sender;
	this->getParent()->removeChild(sprite, true);
}

void Player::OnCollision(Node* sender)
{
	if(sender->getTag()!=1)
	{
		if (sender->getTag() == HelloWorld::RASENGAN && mCurrentState->GetState() != PlayerState::HURTFLY)
		{
			this->getPhysicsBody()->applyImpulse(Vec2(80000, 120000));
			this->SetStateByTag(PlayerState::HURTFLY);
			return;
		}
		if (sender->getTag() == HelloWorld::SHURIKEN && mCurrentState->GetState() != PlayerState::HURT)
		{
			PlayerParticle::CreateHit(sender->getPosition(),(Layer*) this->getParent());
			sender->stopAllActions();
			sender->runAction(RemoveSelf::create());
			this->SetStateByTag(PlayerState::HURT);
			return;
		}
		/*if (sender->getTag() == HelloWorld::BRICK && mCurrentState->GetState()==PlayerState::HURTFLY)
		{
			this->SetStateByTag(PlayerState::IDLE);
		}*/
	}
	else
	{
		mCurrentState->OnCollision(sender);
	}
}

void Player::SetEnemy(Player* enemy)
{
	this->enemy = enemy;
}

RECT Player::GetBound()
{
	RECT rect;
	rect.left = this->getPosition().x - this->getContentSize().width/2 +10;
	rect.right = this->getPosition().x + this->getContentSize().width / 2 - 10;
	rect.top = this->getPosition().y + this->getContentSize().height;
	rect.bottom = this->getPosition().y;
	return rect;
}

void Player::ChangeIDLE()
{
	SetState(new PlayerIDLE(mData));
}

void Player::ChangeJump()
{
	mCurrentAnimate->get()->ResetAnimate();
	this->stopAction(mCurrentAction);
	mCurrentAction = jumpAnimate->get();
	this->runAction(mCurrentAction);
	
}

void Player::AddPosition(Vec2 pos)
{
	this->setPosition(this->getPosition() + pos);
}

Player::~Player()
{
}
