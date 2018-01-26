#include "PlayerFightUp.h"
#include "PLayerJump.h"
#include "PlayerParticle.h"


PlayerFightUp::PlayerFightUp(PlayerData* playerData)
{
	mPlayerData = playerData;
}

void PlayerFightUp::Update(float dt)
{
	mPlayerData->player->AddPosition(Vec2(3, 0));
	if (mPlayerData->player->mCurrentFrame == mPlayerData->player->mCurrentAnimate->get()->getAnimation()->getFrames().size() - 1)
	{
		mPlayerData->player->SetState(new PLayerJump(this->mPlayerData));
		return;
	}
}

void PlayerFightUp::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
}

void PlayerFightUp::HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo)
{
}

void PlayerFightUp::OnCollision(Node* sender)
{
	Player* pl = (Player*)sender;
	Vec2 posBang = Vec2((this->mPlayerData->player->getPosition().x + pl->getPosition().x) / 2, pl->getPosition().y + pl->getContentSize().height / 2);
	if (pl->mCurrentState->GetState() != PlayerState::HURTFLY)
	{
		pl->getPhysicsBody()->applyImpulse(Vec2(0, 180000));
		PlayerParticle::CreateHit(posBang, (Layer*)pl->getParent());
		pl->SetStateByTag(HURTFLY);
		return;
	}
}

PlayerState::StateAction PlayerFightUp::GetState()
{
	return FIGHTUP;
}

PlayerFightUp::~PlayerFightUp()
{
}
