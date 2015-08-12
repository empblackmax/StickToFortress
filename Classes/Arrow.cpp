#include "Arrow.h"


bool Arrow::init()
{
	if (!TowerBase::init())
	{
		return false;
	}

	//初始化箭塔
	setLethality(20);
	setRate(1);
	auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
	addChild(baseplate);

	rotateArrow = Sprite::createWithSpriteFrameName("arrow.png");
	rotateArrow->setPosition(0, baseplate->getContentSize().height / 4);
	addChild(rotateArrow);

	return true;
}


Sprite* Arrow::ArrowBullet()//生成子弹
{
	Sprite* bullet = Sprite::createWithSpriteFrameName("arrowBullet.png");
	bullet->setPosition(rotateArrow->getPosition());
	bullet->setRotation(rotateArrow->getRotation());
	addChild(bullet);

	return bullet;
}

void Arrow::rotate()
{
	////检测炮塔视线范围内距离它最近的敌人
	//checkNearestEnemy();
	//if (nearestEnemy != NULL)
	//{
	//	//如果最近的敌人nearestEnemy存在，弓箭则会旋转，所以我们需要计算弓箭旋转的角度和旋转时间
	
	//touchPosition = this->convertToNodeSpace(touchPosition);
	auto rotateVector = touchPosition - this->getPosition();
	auto rotateRadians = rotateVector.getAngle();
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1*rotateRadians);
	//auto rotateVector = nearestEnemy->sprite->getPosition() - this->getPosition();
	//	auto rotateRadians = rotateVector.getAngle();
	//	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);

		//计算旋转时间
		auto speed = 0.5 / M_PI;
		auto rotateDuration = fabs(rotateRadians * speed);
		auto rotateTo = RotateTo::create(rotateDuration, rotateDegrees);
		//auto rotateBy = RotateBy::create(rotateDuration, rotateDegrees);
		rotateArrow->runAction(rotateTo);
	//	//让弓箭顺序执行旋转动作和shoot方法
	//	rotateArrow->runAction(Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
	//		CallFunc::create(CC_CALLBACK_0(ArrowTower::shoot, this)),
	//		NULL));
	//}
}

void Arrow::shoot(float dt)//在弓箭处生成一颗子弹，发动射击
{
	GameController *instance = GameController::getInstance();
	auto bulletVector = instance->bulletVector;

	//if (nearestEnemy != NULL && nearestEnemy->getCurrHp() > 0)
	//{
		auto currBullet = ArrowBullet();
		instance->bulletVector.pushBack(currBullet);
		arrowBullet.pushBack(currBullet);
		auto moveDuration = getRate();
		Point shootVector = touchPosition - this->getPosition();
		shootVector.normalize();
		shootVector = shootVector*(-1);
		Point normalizedShootVector = shootVector;

		auto farthestDistance = Director::getInstance()->getWinSize().height;
		Point overshotVector = normalizedShootVector * farthestDistance;
		Point offscreenPoint = (rotateArrow->getPosition() - overshotVector);

		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
			CallFuncN::create(CC_CALLBACK_1(Arrow::removeBullet, this)),
			NULL));
		currBullet = NULL;
}


void Arrow::removeBullet(Node* pSender)//销毁子弹
{
	GameController *instance = GameController::getInstance();

	auto bulletVector = instance->bulletVector;

	Sprite *sprite = (Sprite *)pSender;
	instance->bulletVector.eraseObject(sprite);
	sprite->removeFromParent();
}

//void Arrow::shootPoint(Point position)//瞄准准星
//{
//
//}