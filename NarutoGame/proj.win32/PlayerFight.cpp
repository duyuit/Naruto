#include "PlayerFight.h"
#include "PlayerIDLE.h"
#include "HelloWorldScene.h"
#include "PlayerParticle.h"


PlayerFight::~PlayerFight()
{
}

PlayerFight::PlayerFight(PlayerData* playerData)
{
	this->mPlayerData = playerData;
}
int frameStop = 3;
void PlayerFight::Update(float dt)
{
	//if (mPlayerData->player->mCurrentFrame != 0 && mPlayerData->player->mCurrentFrame != 4 && mPlayerData->player->mCurrentFrame != 8)
	if (mPlayerData->player->mCurrentFrame == 2 || mPlayerData->player->mCurrentFrame == 5 || mPlayerData->player->mCurrentFrame == 9)
	{
		if(mPlayerData->player->isLeft)
			mPlayerData->player->AddPosition(Vec2(-3, 0));
		else
		mPlayerData->player->AddPosition(Vec2(3, 0));
	}
	if (mPlayerData->player->mCurrentFrame >= frameStop)
	{
		mPlayerData->player->SetState(new PlayerIDLE(this->mPlayerData));
		return;
	}
	
}
bool lastPress = true;
void PlayerFight::HandleKeyboard(std::map<EventKeyboard::KeyCode, bool> keys)
{
	
}

void PlayerFight::HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo)
{
	HelloWorld *hi = (HelloWorld*)this->mPlayerData->player->getParent();
	int size = keysCombo.size();
	if (keysCombo.size() == 1) return;
	if (keysCombo.size() >= 3)
	{
		if (timeCombo.at(size - 1) - timeCombo.at(size - 2) > 500)
		{
			hi->keysCombo.clear();
			hi->timeCombo.clear();
			return;
		}
		if (keysCombo.at(size - 1) == keysCombo.at(size - 2) && keysCombo.at(size - 2) == keysCombo.at(size - 3) && keysCombo.at(size - 2) == EventKeyboard::KeyCode::KEY_E)
		{

			hi->keysCombo.clear();
			hi->timeCombo.clear();
			frameStop = 11;
			return;
		}
	}
	if (keysCombo.size() >= 2 )
	{
		
		
		if (timeCombo.at(size - 1) - timeCombo.at(size - 2) > 500)
		{
			hi->keysCombo.clear();
			hi->timeCombo.clear();
			frameStop = 3;
			return;
		}
		if (keysCombo.at(size - 1) == keysCombo.at(size - 2) && keysCombo.at(size - 2) == EventKeyboard::KeyCode::KEY_E)
		{
			frameStop = 7;
		}
		
	}
	

}

void PlayerFight::OnCollision(Node* sender)
{
	Player* pl = (Player*)sender;
	if (this->mPlayerData->player->mCurrentState->GetState() == PlayerState::FIGHT && pl->mCurrentState->GetState() != PlayerState::HURT)
	{
		int mFrame = this->mPlayerData->player->mCurrentFrame;
		if (mFrame == 2 || mFrame == 5 || mFrame == 9)
		{
			Vec2 posBang =Vec2((this->mPlayerData->player->getPosition().x + pl->getPosition().x)/2,pl->getPosition().y+pl->getContentSize().height/2);
			this->mPlayerData->player->mCurrentCombo++;
			PlayerParticle::CreateHit(posBang, (Layer*)pl->getParent());
			pl->SetStateByTag(HURT);
		}
		return;
	}
}

PlayerState::StateAction PlayerFight::GetState()
{
	return FIGHT;
}
