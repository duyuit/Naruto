#include "PLayerJump.h"
#include "PlayerIDLE.h"
#include "Player.h"
#include "PlayerThrowJump.h"
#include "PlayerFightDown.h"
#include "GameComponents/GameLog.h"

PLayerJump::PLayerJump(PlayerData* playerData)
{
	mPlayerData = playerData;


}



PLayerJump::~PLayerJump()
{

}

void PLayerJump::Update(float dt)
{
	if (this->mPlayerData->player->getPhysicsBody()->getVelocity().y == 0)
	{
	
		
				this->mPlayerData->player->SetState(new PlayerIDLE(this->mPlayerData));
				return;
	}
}

void PLayerJump::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
	if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
	{
		this->mPlayerData->player->isLeft = true;
		this->mPlayerData->player->setPosition(this->mPlayerData->player->getPosition() + Vec2(-5, 0));
	}
	else
		if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
		{
			this->mPlayerData->player->isLeft = false;
			this->mPlayerData->player->setPosition(this->mPlayerData->player->getPosition() + Vec2(5, 0));
		}

	if (keys[EventKeyboard::KeyCode::KEY_Q])
	{
		
		this->mPlayerData->player->SetState(new PlayerThrowJump(this->mPlayerData));
		return;
	}
	else
		if (keys[EventKeyboard::KeyCode::KEY_E])
		{

			this->mPlayerData->player->SetState(new PlayerFightDown(this->mPlayerData));
			return;
		}
}

void PLayerJump::OnCollision(Node* sender)
{
	GAMELOG("JUMP");
}

PlayerState::StateAction PLayerJump::GetState()
{
	return JUMP;
}
