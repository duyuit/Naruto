#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class PlayerParticle
{
public:
	PlayerParticle();
	static void CreateSmokeFall(Vec2 pos, Layer* layer);
	static void CreateHit(Vec2 pos, Layer* layer);
	~PlayerParticle();
};

