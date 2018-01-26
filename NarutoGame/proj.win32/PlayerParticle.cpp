#include "PlayerParticle.h"
#include "Player.h"


PlayerParticle::PlayerParticle()
{
}

void PlayerParticle::CreateSmokeFall(Vec2 pos,Layer* layer)
{
	Vector<SpriteFrame*> dualSmokeFrameList =Player::loadAnim("particle.xml", "dualSmoke");
	RefPtr<Animate> *dualSmoke = new RefPtr<Animate>(Animate::create(Animation::createWithSpriteFrames(dualSmokeFrameList, 0.04f)));
	Sprite *smoke = Sprite::create();
	smoke->setScale(1.5, 1.5);
	smoke->setAnchorPoint(Vec2(0.5, 0));
	smoke->setPosition(pos);
	layer->addChild(smoke);

	auto sequence = Sequence::create(dualSmoke->get(), RemoveSelf::create(), NULL);
	smoke->runAction(sequence);
	/*dualSmoke->get()->autorelease();
	smoke->autorelease();*/
}

void PlayerParticle::CreateHit(Vec2 pos, Layer* layer)
{
	auto bang = Sprite::create("Bang.png");
	bang->setScale(1.5, 1.5);
	bang->setPosition(pos);
	bang->setScale(0, 0);
	auto scaleAction = ScaleTo::create(0.2, 0.3, 0.3);
	layer->addChild(bang);
	bang->runAction(Sequence::create(scaleAction, RemoveSelf::create(), NULL));
}


PlayerParticle::~PlayerParticle()
{
}
