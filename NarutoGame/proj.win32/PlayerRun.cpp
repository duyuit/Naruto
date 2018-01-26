#include "PlayerRun.h"
#include "PlayerIDLE.h"
#include "PLayerJump.h"


PlayerRun::PlayerRun(PlayerData* playerData)
{
	this->mPlayerData = playerData;
}

PlayerRun::~PlayerRun()
{
}

void PlayerRun::Update(float dt)
{

}

void PlayerRun::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
	if (keys[EventKeyboard::KeyCode::KEY_SPACE])
	{
		mPlayerData->player->getPhysicsBody()->applyImpulse(Vec2(0, 140000));
		this->mPlayerData->player->SetState(new PLayerJump(this->mPlayerData));
		return;
	}
	
	if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
	{
		this->mPlayerData->player->isLeft = true;
		this->mPlayerData->player->setPosition(this->mPlayerData->player->getPosition() + Vec2(-8, 0));
		return;
	}
	else
	if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
	{
			this->mPlayerData->player->isLeft = false;
			this->mPlayerData->player->setPosition(this->mPlayerData->player->getPosition() + Vec2(8, 0));
			return;
	}else
	{
		this->mPlayerData->player->SetState(new PlayerIDLE(this->mPlayerData));
		return;
	}
}

PlayerState::StateAction PlayerRun::GetState()
{
	return RUN;
}
