#include "PlayerState.h"



PlayerState::PlayerState()
{
}


PlayerState::~PlayerState()
{
}


PlayerState::StateAction PlayerState::GetState()
{
	return IDLE;
}

void PlayerState::Update(float dt)
{
}

PlayerState::PlayerState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}
void PlayerState::HandleKeyboard(std::map<cocos2d::EventKeyboard::KeyCode, bool> keys)
{

}

void PlayerState::HandleCombo(vector<EventKeyboard::KeyCode> keysCombo, vector<float> timeCombo)
{

}

void PlayerState::OnCollision(Node * sender)
{
}
