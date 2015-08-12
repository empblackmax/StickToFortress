#include "Thief.h"


bool Thief::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	//初始化怪物的移动速度，左右方向的动画
    setRunSpeed(25);
    setVaule(10);
    sprite = Sprite::createWithSpriteFrameName("enemyRight1_1.png");
    this->addChild(sprite);
    animationRight = createAnimation("enemyRight1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationRight, "runright1");
    animationLeft = createAnimation("enemyLeft1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationLeft, "runleft1");
    animationExplode= createAnimation("explode1", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode1");
    
    createAndSetHpBar();
	return true;
}

Thief* Thief::createThief( int hp)
{
    Thief *pRet = new Thief();
    if (pRet && pRet->init())
    {

		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);
        
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


void Thief::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode1"))
                                       ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                                       , NULL));
}




