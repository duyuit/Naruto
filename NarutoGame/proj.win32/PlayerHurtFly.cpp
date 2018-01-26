#include "PlayerHurtFly.h"
#include "PlayerIDLE.h"
#include "PlayerParticle.h"
#include "HelloWorldScene.h"


PlayerHurtFly::PlayerHurtFly(PlayerData* playerData)
{
	mPlayerData = playerData;
}

void PlayerHurtFly::Update(float dt)
{
	if (this->mPlayerData->player->getPhysicsBody()->getVelocity().y == 0)
	{
		if (lastUpdate == 0)
		{
			this->mPlayerData->player->mCurrentAnimate->get()->setLockFrame(4);
			this->mPlayerData->player->stopAllActions();
			this->mPlayerData->player->runAction(this->mPlayerData->player->mCurrentAnimate->get());
			PlayerParticle::CreateSmokeFall(this->mPlayerData->player->getPosition(), (Layer*)this->mPlayerData->player->getParent());
			lastUpdate = GetTickCount();
			return;
		}
		if(GetTickCount()-lastUpdate>=400)
		{
			
			this->mPlayerData->player->SetState(new PlayerIDLE(mPlayerData));
		}
	
	}
	
}

void PlayerHurtFly::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
}

void PlayerHurtFly::OnCollision(Node* sender)
{
	
}

PlayerState::StateAction PlayerHurtFly::GetState()
{
	return HURTFLY;
}


PlayerHurtFly::~PlayerHurtFly()
{
}
