#include "PlayerSwipe.h"
#include "2d/CCActionInstant.h"


PlayerSwipe::PlayerSwipe(PlayerData* playerData)
{
	mPlayerData = playerData;
	if(mPlayerData->player->isLeft)
	{
		auto move = MoveTo::create(0.2f, this->mPlayerData->player->getPosition() + Vec2(-200, 0));
		this->mPlayerData->player->runAction(Sequence::create(move,
			CallFuncN::create(CC_CALLBACK_0(Player::ChangeIDLE, mPlayerData->player)), NULL));
	}
	else
	{
		auto move = MoveTo::create(0.2f, this->mPlayerData->player->getPosition() + Vec2(200, 0));
		this->mPlayerData->player->runAction(Sequence::create(move,
			CallFuncN::create(CC_CALLBACK_0(Player::ChangeIDLE, mPlayerData->player)), NULL));
	}
	
}

void PlayerSwipe::Update(float dt)
{
	SpriteFrame* sprite_frame = this->mPlayerData->player->mCurrentAnimate->get()->getAnimation()->getFrames().at(this->mPlayerData->player->mCurrentFrame)->getSpriteFrame();
	Sprite* sprite = Sprite::createWithSpriteFrame(sprite_frame);
	sprite->setScale(1.5, 1.5);
	sprite->setFlipX(this->mPlayerData->player->isLeft);
	sprite->setAnchorPoint(Vec2(0.5, 0));
	sprite->setPosition(this->mPlayerData->player->getPosition());
	this->mPlayerData->player->getParent()->addChild(sprite);
	sprite->setOpacity(alpha +=150);
	sprite->runAction(Sequence::create(RotateTo::create(0.1f,0), RemoveSelf::create(), NULL));
}

void PlayerSwipe::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
}

void PlayerSwipe::HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo)
{
}

PlayerState::StateAction PlayerSwipe::GetState()
{
	return SWIPE;
}

PlayerSwipe::~PlayerSwipe()
{
}
