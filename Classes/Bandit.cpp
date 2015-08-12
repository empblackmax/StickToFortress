#include "Bandit.h"


bool Bandit::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setRunSpeed(70);
	setVaule(30);
	sprite = Sprite::createWithSpriteFrameName("enemyRight3_1.png");
	this->addChild(sprite);
	animationRight = createAnimation("enemyRight3", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationRight, "runright3");
	animationLeft = createAnimation("enemyLeft3", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationLeft, "runleft3");
	animationExplode = createAnimation("explode3", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode3");

	createAndSetHpBar();
	//schedule(schedule_selector(Bandit::changeDirection), 0.4f);
	return true;
}

Bandit* Bandit::createBandit(/*Vector<Node*> points,*/ int hp)
{
	Bandit *pRet = new Bandit();
	if (pRet && pRet->init())
	{
		/*pRet->setPointsVector(points);*/
		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);
		/*pRet->runFllowPoint();*/

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
//void Bandit::changeDirection(float dt)
//{
//	auto curr = currPoint();
//	if (curr == NULL)
//	{
//		return;
//	}
//	if (curr->getPositionX() > sprite->getPosition().x)
//	{
//		sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("runright3")));
//	}
//	else
//	{
//		sprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("runleft3")));
//	}
//}
void Bandit::enemyExpload()
{
	hpBgSprite->setVisible(false);
	sprite->stopAllActions();
	//unschedule(schedule_selector(Bandit::changeDirection));
	sprite->setAnchorPoint(Point(0.5f, 0.25f));
	sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode3"))
		, CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
		, NULL));
}