#include "Thief.h"


bool Thief::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	//初始化小偷的移动速度，左右方向的动画
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
	//调用定时器schedule刷新自定义的changeDirection函数
	//schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);
	return true;
}

Thief* Thief::createThief(/*Vector<Node*> points,*/ int hp)
{
    Thief *pRet = new Thief();
    if (pRet && pRet->init())
    {
		// 设置怪物的路径点集
        //pRet->setPointsVector(points);
		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);

		// 让怪物沿着路径点移动
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

//void Thief::changeDirection(float dt)
//{
//    auto curr = currPoint();
//    if( curr == NULL )
//	{
//		return;
//	}
//    if(curr->getPositionX() > sprite->getPosition().x )
//    {
//        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright1"))) ;
//    }else
//	{
//        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft1"))  );
//    }
//}
void Thief::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    //unschedule(schedule_selector(Thief::changeDirection));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode1"))
                                       ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                                       , NULL));
}




