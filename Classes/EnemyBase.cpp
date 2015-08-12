#include "EnemyBase.h"

EnemyBase::EnemyBase()
:sprite(NULL)
, hpBgSprite(NULL)
, animationRight(NULL)
, animationLeft(NULL)
, animationExplode(NULL)
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

void EnemyBase::createAndSetHpBar()//Ѫ��
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

Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay)//��������
{
	//����һ��֡����Vector�����洢������ÿһ֡
	Vector<SpriteFrame*> animFrames;

	//����ÿһ֡��ͨ��getSpriteFrameByName�������������������д���������ÿһ֡��ͬʱ�����ӵ� animFrames��������ȥ
	for (int i = 1; i <= framesNum; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "_%i.png", i);
		std::string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	//createWithSpriteFrames��������һ������֡����������һ��Animation����
	return Animation::createWithSpriteFrames(animFrames, delay);
}

void EnemyBase::moveToArrow(Point position1,Point position2)
{
	sprite->setPosition(position1);
	auto moveTo = MoveTo::create(15.0f, position2);
	sprite->runAction(moveTo);
}

