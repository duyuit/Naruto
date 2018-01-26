#include "PlayerCombo.h"
#include "PLayerJump.h"
#include "PlayerHurtFly.h"
#include "PlayerParticle.h"


PlayerCombo::PlayerCombo(PlayerData* playerData)
{
	mPlayerData = playerData;
}

void PlayerCombo::Update(float dt)
{
	if (mPlayerData->player->mCurrentFrame == 6 || mPlayerData->player->mCurrentFrame == 11 || mPlayerData->player->mCurrentFrame == 18)
	{
		if (mPlayerData->player->isLeft)
			mPlayerData->player->getPhysicsBody()->setPositionOffset(Vec2(-20, 0));
		else
			mPlayerData->player->getPhysicsBody()->setPositionOffset(Vec2(20, 0));
	}else 	mPlayerData->player->getPhysicsBody()->setPositionOffset(Vec2(0, 0));
	
	if (mPlayerData->player->mCurrentFrame == 3 && lastFrame != 3)
	{
		if (mPlayerData->player->isLeft)
			mPlayerData->player->AddPosition(Vec2(-200, 0));
		else
			mPlayerData->player->AddPosition(Vec2(200, 0));
		lastFrame = 3;
		return;
	}
	else
		if (mPlayerData->player->mCurrentFrame == 9 && lastFrame != 9)
		{
			if (mPlayerData->player->isLeft)
			{
				if (target != nullptr)
					mPlayerData->player->setPosition(target->getPosition() + Vec2(-30, 0));
				else
					mPlayerData->player->AddPosition(Vec2(-100, 0));

			}
			else
			{
				if (target != nullptr)
					mPlayerData->player->setPosition(target->getPosition() + Vec2(30, 0));
				else
					mPlayerData->player->AddPosition(Vec2(100, 0));
			}

			lastFrame = 9;
			return;
		}
		else
			if (mPlayerData->player->mCurrentFrame == 15 && lastFrame != 15)
			{
				if (mPlayerData->player->isLeft)
				{
					if (target != nullptr)
						mPlayerData->player->setPosition(target->getPosition());
					else
						mPlayerData->player->AddPosition(Vec2(-130, 500));
				}
				else
				{
					if (target != nullptr)
						mPlayerData->player->setPosition(target->getPosition());
					else
						mPlayerData->player->AddPosition(Vec2(130, 100));
				}

				lastFrame = 15;
				return;
			}
			else if (mPlayerData->player->mCurrentFrame == mPlayerData->player->mCurrentAnimate->get()->getAnimation()->getFrames().size() - 1)
			{
				mPlayerData->player->SetStateByTag(JUMP);
			}
}

void PlayerCombo::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
}
 
void PlayerCombo::HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo)
{
}

void PlayerCombo::OnCollision(Node* sender)
{

	Player* pl = (Player*)sender;
	Vec2 posBang = Vec2((this->mPlayerData->player->getPosition().x + pl->getPosition().x) / 2, pl->getPosition().y + pl->getContentSize().height / 2);
	if (mPlayerData->player->mCurrentFrame>4 && mPlayerData->player->mCurrentFrame<8 && pl->mCurrentState->GetState()!=HURTFLY && !combo1)
	{
		if(this->mPlayerData->player->isLeft)
			pl->getPhysicsBody()->applyImpulse(Vec2(-120000, 60000));
		else
		pl->getPhysicsBody()->applyImpulse(Vec2(120000, 60000));
		pl->SetStateByTag(HURTFLY);
		PlayerParticle::CreateHit(posBang,(Layer*) pl->getParent());
		target = pl; //Set Target
		combo1 = true; //Da thuc hien xong combo1
		this->mPlayerData->player->mCurrentCombo++; //+ So combo hien tai len
		return;
	}
	if (mPlayerData->player->mCurrentFrame>10 && mPlayerData->player->mCurrentFrame<13 && !combo2)
	{

		pl->getPhysicsBody()->applyImpulse(Vec2(0, 180000));
		pl->SetStateByTag(HURTFLY);
		combo2 = true;
		target = pl;
		PlayerParticle::CreateHit(posBang, (Layer*)pl->getParent());
		this->mPlayerData->player->mCurrentCombo++;
		return;
	}
	if (mPlayerData->player->mCurrentFrame==16  && !combo3)
	{
		pl->getPhysicsBody()->applyImpulse(Vec2(0, -500000));
		pl->SetStateByTag(HURTFLY);
		combo3 = true;
		target = pl;
		PlayerParticle::CreateHit(posBang, (Layer*)pl->getParent());
		this->mPlayerData->player->mCurrentCombo++;
		return;
	}
}

PlayerState::StateAction PlayerCombo::GetState()
{
	return COMBO;
}

PlayerCombo::~PlayerCombo()
{
}
