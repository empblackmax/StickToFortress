#include "Pirate.h"

bool Pirate::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setRunSpeed(50);
	setVaule(20);
	sprite = Sprite::createWithSpriteFrameName("enemyRight2_1.png");
	this->addChild(sprite);
	animationRight = createAnimation("enemyRight2", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationRight, "runright2");
	animationLeft = createAnimation("enemyLeft2", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationLeft, "runleft2");
	animationExplode = createAnimation("explode2", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode2");

	createAndSetHpBar();
	//schedule(schedule_selector(Pirate::changeDirection), 0.4f);
	return true;
}

Pirate* Pirate::createPirate(/*Vector<Node*> points,*/ int hp)
{
	Pirate *pRet = new Pirate();
	if (pRet && pRet->init())
	{
		//pRet->setPointsVector(points);
		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);
		//pRet->runFllowPoint();

		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
//void Pirate::changeDirection(float dt)
//{
//	auto curr = currPoint();
//	if (curr == NULL)
//	{
//		return;
//	}
//	if (curr->getPositionX() > sprite->getPosition().x)
//	{
//		sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("runright2")));
//	}
//	else
//	{
//		sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("runleft2")));
//	}
//}
void Pirate::enemyExpload()
{
	hpBgSprite->setVisible(false);
	sprite->stopAllActions();
	//unschedule(schedule_selector(Pirate::changeDirection));
	sprite->setAnchorPoint(Point(0.5f, 0.25f));
	sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode2"))
		, CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
		, NULL));
}

