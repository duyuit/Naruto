#include "PlayerThrowStand.h"
#include "PlayerIDLE.h"
#include "2d/CCActionInstant.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

PlayerThrowStand::PlayerThrowStand(PlayerData* playerData)
{
	this->mPlayerData = playerData;
}

void PlayerThrowStand::Update(float dt)
{
	if (mPlayerData->player->mCurrentFrame == 1 && GetTickCount() - lastUpdate >= 200)
	{

		auto shuriken = Sprite::create("shuriken.png");
		shuriken->setTag(HelloWorld::ObjectType::SHURIKEN);
		shuriken->setScale(1.5, 1.5);
		
		mPlayerData->player->getParent()->addChild(shuriken);
		auto shuriken_body = PhysicsBody::createBox(shuriken->getContentSize());
		shuriken_body->setContactTestBitmask(0x1);
		shuriken_body->setDynamic(false);
		shuriken->setPhysicsBody(shuriken_body);
		if (mPlayerData->player->isLeft)
		{
			shuriken->setPosition(mPlayerData->player->getPosition() + Vec2(-mPlayerData->player->getContentSize().width, mPlayerData->player->getContentSize().height));
			auto move = MoveTo::create(1.0f, shuriken->getPosition() + Vec2(-400, 0));
			auto rotate = RotateTo::create(1.5f, -360 * 6);


			shuriken->runAction(rotate);
			shuriken->runAction(Sequence::create(
				move,
				RemoveSelf::create(), NULL));
		}
		else
		{
			shuriken->setPosition(mPlayerData->player->getPosition() + Vec2(mPlayerData->player->getContentSize().width, mPlayerData->player->getContentSize().height));
			auto move = MoveTo::create(1.0f, shuriken->getPosition() + Vec2(400, 0));
			auto rotate = RotateTo::create(1.5f, 360 * 6);

			shuriken->runAction(rotate);
			shuriken->runAction(Sequence::create(
				move,
				RemoveSelf::create(), NULL));
		}
		lastUpdate = GetTickCount();
		return;
	}
	if (mPlayerData->player->mCurrentFrame == mPlayerData->player->mCurrentAnimate->get()->getAnimation()->getFrames().size() - 1)
	{
		mPlayerData->player->SetState(new PlayerIDLE(this->mPlayerData));
		return;
	}

}

void PlayerThrowStand::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
}

PlayerState::StateAction PlayerThrowStand::GetState()
{
	return THROWSTAND;
}



PlayerThrowStand::~PlayerThrowStand()
{
}
