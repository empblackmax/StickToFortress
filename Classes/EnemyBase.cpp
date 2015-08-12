#include "EnemyBase.h"

EnemyBase::EnemyBase()
:sprite(NULL)
, hpBgSprite(NULL)
//, pointCounter(0)
, animationRight(NULL)
, animationLeft(NULL)
, animationExplode(NULL)
//, pointsVector(NULL)
, runSpeed(0)
, maxHp(0)
, currHp(0)
, hpPercentage(100)
, hpBar(NULL)
, enemySuccessful(false)
{
}

EnemyBase::~EnemyBase()
{
}

bool EnemyBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void EnemyBase::createAndSetHpBar()//血条
{
	hpBgSprite = Sprite::createWithSpriteFrameName("hpBg1.png");
	hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height));
	sprite->addChild(hpBgSprite);

	hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp1.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(hpPercentage);
	hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 3 * 2));
	hpBgSprite->addChild(hpBar);
}

Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay)//创建动画
{
	//创建一个帧缓存Vector向量存储动画的每一帧
	Vector<SpriteFrame*> animFrames;

	//遍历每一帧，通过getSpriteFrameByName（“纹理名”）方法中创建动画的每一帧，同时把它加到 animFrames向量里面去
	for (int i = 1; i <= framesNum; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "_%i.png", i);
		std::string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	//createWithSpriteFrames方法基于一个精灵帧向量，返回一个Animation对象
	return Animation::createWithSpriteFrames(animFrames, delay);
}

void EnemyBase::moveToArrow(Point position1,Point position2)
{
	sprite->setPosition(position1);
	auto moveTo = MoveTo::create(15.0f, position2);
	sprite->runAction(moveTo);
}


//Node* EnemyBase::currPoint()//获得敌人当前所处的路径点
//{
//	if (pointsVector.size() > 0)
//	{
//		return this->pointsVector.at(pointCounter);
//	}
//	else
//	{
//		return NULL;
//	}
//}
//
//Node* EnemyBase::nextPoint()//下一个移动点
//{
//	int maxCount = this->pointsVector.size();
//	pointCounter++;
//	if (pointCounter < maxCount)
//	{
//		auto node = this->pointsVector.at(pointCounter);
//		return node;
//	}
//	else
//	{
//		setEnemySuccessful(true);
//	}
//	return NULL;
//}
//
//void EnemyBase::runFllowPoint()
//{
//	auto temp = currPoint();
//	sprite->setPosition(temp->getPosition());
//	auto point = nextPoint();
//
//	if (point != NULL)
//	{
//		auto duration = temp->getPosition().getDistance(point->getPosition()) / getRunSpeed();
//		auto moveTo = MoveTo::create(duration, point->getPosition());
//		auto callFuncN = CallFuncN::create(CC_CALLBACK_0(EnemyBase::runFllowPoint, this));
//		sprite->runAction(Sequence::create(moveTo, callFuncN, NULL));
//	}
//}
//
//
//void EnemyBase::setPointsVector(Vector<Node*> points)
//{
//	this->pointsVector = points;
//}
//
