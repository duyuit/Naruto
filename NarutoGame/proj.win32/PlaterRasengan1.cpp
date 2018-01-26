#include "PlaterRasengan1.h"
#include "PlayerIDLE.h"
#include "2d/CCActionInstant.h"
#include "HelloWorldScene.h"


PlayerRasengan1::PlayerRasengan1(PlayerData* playerData)
{
	this->mPlayerData = playerData;
}

void PlayerRasengan1::Update(float dt)
{
	if (mPlayerData->player->mCurrentFrame <= 40)
	{
		if (mPlayerData->player->isLeft)
			mPlayerData->player->setAnchorPoint(Vec2(0, 0));
		else
			mPlayerData->player->setAnchorPoint(Vec2(1, 0));
	}
	else
	{
		mPlayerData->player->setAnchorPoint(Vec2(0.5, 0));
	}
	if (mPlayerData->player->mCurrentFrame == 51 && GetTickCount() - lastUpdate>500)
	{
		Vector<SpriteFrame*> rasengan1Object = Player::loadAnim("rasengan1.xml", "move");
		Sprite* rasengan = Sprite::createWithSpriteFrame(rasengan1Object.at(0));
		rasengan->setScale(1.5, 1.5);
		rasengan->setTag(HelloWorld::RASENGAN);
		mPlayerData->player->getParent()->addChild(rasengan);

		auto rasengan_body = PhysicsBody::createBox(rasengan->getContentSize());
		rasengan_body->setDynamic(false);
		rasengan_body->setContactTestBitmask(0x1);
		rasengan->setPhysicsBody(rasengan_body);

		Vector<SpriteFrame*> soilObject = Player::loadAnim("rasengan1.xml", "soil");
		Sprite* soil = Sprite::createWithSpriteFrame(soilObject.at(0));
		soil->setAnchorPoint(Vec2(0.5, 0));
		mPlayerData->player->getParent()->addChild(soil);
		rasengan->setFlipX(mPlayerData->player->isLeft);
		soil->setFlipX(mPlayerData->player->isLeft);
		if (mPlayerData->player->isLeft)
		{
			rasengan->setPosition(mPlayerData->player->getPosition() + Vec2(-mPlayerData->player->getContentSize().width, mPlayerData->player->getContentSize().height / 2 + 10));
			rasengan->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(rasengan1Object, 0.1f))));
			rasengan->runAction(Sequence::create(
				MoveTo::create(1, rasengan->getPosition() + Vec2(-400, 0)),
				CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, mPlayerData->player)), NULL));

			soil->setPosition(mPlayerData->player->getPosition() + Vec2(-mPlayerData->player->getContentSize().width / 2, -10));
			soil->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(soilObject, 0.06f))));
			soil->runAction(Sequence::create(
				MoveTo::create(1, soil->getPosition() + Vec2(-400, 0)),
				CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, mPlayerData->player)), NULL));
		}
		else
		{
			rasengan->setPosition(mPlayerData->player->getPosition() + Vec2(mPlayerData->player->getContentSize().width, mPlayerData->player->getContentSize().height / 2 + 10));
			rasengan->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(rasengan1Object, 0.1f))));
			rasengan->runAction(Sequence::create(
				MoveTo::create(1, rasengan->getPosition() + Vec2(400, 0)),
				CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, mPlayerData->player)), NULL));

			soil->setPosition(mPlayerData->player->getPosition() + Vec2(mPlayerData->player->getContentSize().width / 2, -10));
			soil->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(soilObject, 0.06f))));
			soil->runAction(Sequence::create(
				MoveTo::create(1, soil->getPosition() + Vec2(400, 0)),
				CallFuncN::create(CC_CALLBACK_1(Player::XoaChild, mPlayerData->player)), NULL));

		}

		lastUpdate = GetTickCount();
	}
		

}

void PlayerRasengan1::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
	if (!keys[EventKeyboard::KeyCode::KEY_R])
		this->mPlayerData->player->SetState(new PlayerIDLE(mPlayerData));
}

PlayerState::StateAction PlayerRasengan1::GetState()
{
	return RASENGAN1;
}

PlayerRasengan1::~PlayerRasengan1()
{
}
