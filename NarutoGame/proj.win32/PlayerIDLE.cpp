#include "PlayerIDLE.h"
#include "PlayerRun.h"
#include "PLayerJump.h"
#include "PlayerThrowStand.h"
#include "PlaterRasengan1.h"
#include "PlayerFight.h"
#include "HelloWorldScene.h"
#include "PlayerFightUp.h"
#include "PlayerSwipe.h"
#include "PlayerCombo.h"


PlayerIDLE::PlayerIDLE(PlayerData* playerData)
{
	this->mPlayerData = playerData;

}

PlayerIDLE::~PlayerIDLE()
{
}

void PlayerIDLE::Update(float dt)
{
	
}

void PlayerIDLE::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
	if(keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
	{
		this->mPlayerData->player->isLeft = true;
		this->mPlayerData->player->SetState(new PlayerRun(this->mPlayerData));
		return;
	}else
	if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
	{
	
		this->mPlayerData->player->isLeft = false;
		this->mPlayerData->player->SetState(new PlayerRun(this->mPlayerData));
		return;
	}

	if (keys[EventKeyboard::KeyCode::KEY_Q])
	{
		this->mPlayerData->player->SetState(new PlayerThrowStand(this->mPlayerData));
		return;
	}else
	if (keys[EventKeyboard::KeyCode::KEY_SPACE])
	{
		
		mPlayerData->player->getPhysicsBody()->applyImpulse(Vec2(0,140000));
		this->mPlayerData->player->SetState(new PLayerJump(this->mPlayerData));
		return;
	}else
	if (keys[EventKeyboard::KeyCode::KEY_R])
	{
		
		this->mPlayerData->player->SetState(new PlayerRasengan1(this->mPlayerData));
		return;
	}else
	if(keys[EventKeyboard::KeyCode::KEY_E])
	{
		if (keys[EventKeyboard::KeyCode::KEY_UP_ARROW])
		{
			this->mPlayerData->player->SetState(new PlayerFightUp(this->mPlayerData));
			return;
		}
		this->mPlayerData->player->SetState(new PlayerFight(this->mPlayerData));
		return;
	}
	if (keys[EventKeyboard::KeyCode::KEY_Z])
	{
	
		this->mPlayerData->player->SetState(new PlayerCombo(this->mPlayerData));
		return;
	}


}

void PlayerIDLE::HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo)
{
	if (keysCombo.size() >= 2)
	{
		int size = keysCombo.size();
		if (timeCombo.at(size - 1) - timeCombo.at(size - 2) > 500) return;
		if (keysCombo.at(size - 1) == keysCombo.at(size - 2) && (keysCombo.at(size - 2) == EventKeyboard::KeyCode::KEY_RIGHT_ARROW || keysCombo.at(size - 2) == EventKeyboard::KeyCode::KEY_LEFT_ARROW))
		{
			HelloWorld *hi = (HelloWorld*)this->mPlayerData->player->getParent();
			hi->keysCombo.clear();
			hi->timeCombo.clear();
			this->mPlayerData->player->SetState(new PlayerSwipe(mPlayerData));
		
			
		}
	}
}

void PlayerIDLE::OnCollision(Node* sender)
{
	GAMELOG("IDLE");
}

PlayerState::StateAction PlayerIDLE::GetState()
{
	return IDLE;
}
