#include "PlayerHurt.h"
#include "PlayerIDLE.h"


PlayerHurt::PlayerHurt(PlayerData* playerData)
{
	mPlayerData = playerData;
}

void PlayerHurt::Update(float dt)
{
	if (mPlayerData->player->mCurrentFrame == mPlayerData->player->mCurrentAnimate->get()->getAnimation()->getFrames().size() - 1)
	{
		mPlayerData->player->SetState(new PlayerIDLE(this->mPlayerData));
		return;
	}
}

void PlayerHurt::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
}

PlayerState::StateAction PlayerHurt::GetState()
{
	return HURT;
}

PlayerHurt::~PlayerHurt()
{
}
