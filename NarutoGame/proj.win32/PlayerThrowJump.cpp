#include "PlayerThrowJump.h"
#include "PLayerJump.h"
#include "2d/CCActionInstant.h"
#include "HelloWorldScene.h"
#include "PlayerIDLE.h"


PlayerThrowJump::PlayerThrowJump(PlayerData* playerData)
{
	this->mPlayerData = playerData;
}

void PlayerThrowJump::Update(float dt)
{
	if (mPlayerData->player->mCurrentFrame == 1 && GetTickCount() - lastUpdate >= 200)
	{

		auto shuriken = Sprite::create("shuriken.png");
		shuriken->setScale(1.5, 1.5);
		shuriken->setTag(HelloWorld::ObjectType::SHURIKEN);
		mPlayerData->player->getParent()->addChild(shuriken);
				auto shuriken_body = PhysicsBody::createBox(shuriken->getContentSize());
				shuriken_body->setContactTestBitmask(0x1);
				shuriken_body->setDynamic(false);
				shuriken->setPhysicsBody(shuriken_body);
				if (mPlayerData->player->isLeft)
				{
					shuriken->setPosition(mPlayerData->player->getPosition() + Vec2(-mPlayerData->player->getContentSize().width, mPlayerData->player->getContentSize().height));
					auto move = MoveTo::create(1.0f,Vec2(shuriken->getPosition().x-400,0));
					auto rotate = RotateTo::create(1.0f, -360 * 6);

					shuriken->runAction(rotate);
					shuriken->runAction(Sequence::create(
						move,
						RemoveSelf::create(), NULL));
				}
				else
				{
					shuriken->setPosition(mPlayerData->player->getPosition() + mPlayerData->player->getContentSize());
					auto move = MoveTo::create(1.0f, Vec2(shuriken->getPosition().x + 400, 0));
					auto rotate = RotateTo::create(1.0f, 360 * 6);

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
		mPlayerData->player->SetState(new PLayerJump(this->mPlayerData));
		return;
	}
	if (mPlayerData->player->mCurrentFrame == mPlayerData->player->mCurrentAnimate->get()->getAnimation()->getFrames().size() - 1)
	{
		mPlayerData->player->SetState(new PLayerJump(this->mPlayerData));
		return;
	}
	if (this->mPlayerData->player->getPhysicsBody()->getVelocity().y == 0)
	{


		this->mPlayerData->player->SetState(new PlayerIDLE(this->mPlayerData));
		return;
	}
}

void PlayerThrowJump::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
}

PlayerState::StateAction PlayerThrowJump::GetState()
{
	return THROWJUMP;
}

PlayerThrowJump::~PlayerThrowJump()
{
}
