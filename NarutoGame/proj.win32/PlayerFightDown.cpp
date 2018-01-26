#include "PlayerFightDown.h"
#include "PLayerJump.h"
#include "PlayerParticle.h"


PlayerFightDown::PlayerFightDown(PlayerData* playerData)
{
	mPlayerData = playerData;
}

void PlayerFightDown::Update(float dt)
{
	if (mPlayerData->player->mCurrentFrame == mPlayerData->player->mCurrentAnimate->get()->getAnimation()->getFrames().size() - 1)
	{
		mPlayerData->player->SetState(new PLayerJump(this->mPlayerData));
		return;
	}
}

void PlayerFightDown::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
}

void PlayerFightDown::HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo)
{
}

PlayerState::StateAction PlayerFightDown::GetState()
{
	return FIGHTDOWN;
}

void PlayerFightDown::OnCollision(Node* sender)
{
	Player* pl = (Player*)sender;
	Vec2 posBang = Vec2((this->mPlayerData->player->getPosition().x + pl->getPosition().x) / 2, pl->getPosition().y + pl->getContentSize().height / 2);
	if(!isDone)
	{
		PlayerParticle::CreateHit(posBang, (Layer*)pl->getParent());
		pl->getPhysicsBody()->applyImpulse(Vec2(0, -220000));
		pl->SetStateByTag(HURTFLY);
		isDone = true;
	}

	

}

PlayerFightDown::~PlayerFightDown()
{
}
