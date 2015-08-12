#include "GameScene.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	winSize = Director::getInstance()->getWinSize();
	instance = GameController::getInstance();

	//�����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");

	//����ͼƬ
	auto bground = Sprite::create("playbg.png");
	bground->setPosition(winSize / 2);
	this->addChild(bground,-2);

	//��ͼ��
	_map = TMXTiledMap::create("sticktofortress.tmx");
	//_map->setAnchorPoint(Point(0.5f, 0.5f));
	//_map->setPosition(Point(winSize.width / 2, winSize.height / 2 ));
	_objects = _map->getLayer("BgLayer");
	/*_objects->setAnchorPoint(Point(0.5f, 0.5f));
	_objects->setPosition(winSize / 2);*/

	_objectsgroup = _map->getObjectGroup("Objects");
	auto arrowPoint = _objectsgroup->getObject("ArrowPoint");
	float x = arrowPoint["x"].asFloat();
	float y = arrowPoint["y"].asFloat();

	//����
	_arrow = Arrow::create();
	_arrow->setPosition(x, y);
	this->addChild(_arrow);
	this->setViewCenter(_arrow->getPosition());

	this->addChild(_map,-1);

	_point = Sprite::create("point.png");
	_point->setPosition(winSize / 2);
	this->addChild(_point,5);
	_arrow->setTouchPosition(_point->getPosition());;
	_arrow->rotate();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch,Event* event)
	{
		px = touch->getLocation().x;
		py = touch->getLocation().y;
		/*_arrow->setTouchPosition(_point->getPosition());;
		_arrow->rotate();*/
		_arrow->schedule(schedule_selector(Arrow::shoot),0.2f);

		return true;
	};
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	
	/*listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
	_arrow->setTouchPosition(touch->getLocation());
	_arrow->schedule(schedule_selector(Arrow::rotate));
	};*/
	listener->onTouchEnded=[&](Touch* touch, Event* event)
	{
		_arrow->unschedule(schedule_selector(Arrow::shoot));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	initBornEnemyVector();
	//addEnemy();
	this->schedule(schedule_selector(GameScene::addEnemy ),2.0f);
	this->schedule(schedule_selector(GameScene::CollisionDetection));

	return true;
}

void GameScene::setViewCenter(Point position)
{
	float x = std::max(position.x, winSize.width / 2);
	float y = std::max(position.y, winSize.height / 2);

	x = std::min(x, _map->getMapSize().width*_map->getTileSize().width-winSize.width/2);
	y = std::min(y, _map->getMapSize().height*_map->getTileSize().height - winSize.height / 2);

	auto actualPosition = Point(x, y);

	auto winCenter = Point(winSize / 2);

	auto viewCenter = winCenter - actualPosition;

	this->setPosition(viewCenter);

}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	/*_arrow->setTouchPosition(_point->getPosition());;
	_arrow->rotate();*/
	int mx = touch->getLocation().x - px;
	int my = touch->getLocation().y - py;
	_point->runAction(MoveBy::create(0, Point(mx, my)));
	_arrow->setTouchPosition(_point->getPosition());;
	_arrow->rotate();
	px = touch->getLocation().x;
	py = touch->getLocation().y;
	_arrow->setTouchPosition(_point->getPosition());;
	/*_arrow->rotate();
	_arrow->setTouchPosition(_point->getPosition());*/
	
	
	
}

void GameScene::initBornEnemyVector()
{
	//����getObject("������")������ȡ�������еĶ�����������ValueMap���͵�ֵ��
	Node *bornPoint = NULL;
	int count = 0;
	ValueMap point;
	point = _objectsgroup->getObject(std::to_string(count));
	//����ÿһ������
	while (point.begin() != point.end())
	{
		//��ȡÿ�������Xֵ��Yֵ
		float x = point.at("x").asFloat();
		float y = point.at("y").asFloat();
		//����һ��Node������·���㣬����������������λ�ã�Ȼ������ӵ�pointsVector������ȥ�������Ժ���ҡ�
		bornPoint = Node::create();
		bornPoint->setPosition(Point(x, y));
		this->_bornEnemy.pushBack(bornPoint);
		count++;
		point = _objectsgroup->getObject(std::to_string(count));
	}
	bornPoint = NULL;
}

void GameScene::addEnemy(float dt)//�����˼ӵ�����
{
	if (instance->enemyVector.size()>6)
	{
		return;
	}
	int rana = rand() % 3+rand()%5;
	auto enemy = creatEnemy();
	//enemy->setPosition(_bornEnemy.at(rana)->getPosition());
	//enemy->sprite->setPosition(_bornEnemy.at(rana)->getPosition());
	//enemy->moveToArrow(_arrow->getPosition());
	enemy->moveToArrow(_bornEnemy.at(rana)->getPosition(), Point(_bornEnemy.at(rana)->getPositionX(), _arrow->getPositionY()));
	this->addChild(enemy);

}

EnemyBase* GameScene::creatEnemy()//�������һ�����͵���
{
	int ranb = rand() % 2+rand()%2;
	
	switch (ranb)
	{
	case 0:
		currenemy = Thief::createThief(5);
		instance->enemyVector.pushBack(currenemy);
		break;
	case 1:
		currenemy = Bandit::createBandit(7);
		instance->enemyVector.pushBack(currenemy);
		break;
	case 2:
		currenemy = Pirate::createPirate(9);
		instance->enemyVector.pushBack(currenemy);
		break;
	default:
		break;
	}

	return currenemy;
}

void GameScene::CollisionDetection(float dt)//��ײ���
{
	auto bulletVector = instance->bulletVector;
	auto enemyVector = instance->enemyVector;

	if (bulletVector.empty() || enemyVector.empty())
	{
		return;
	}
	Vector<EnemyBase*> enemyNeedToDelete;
	Vector<Sprite*> bulletNeedToDelete;
	for (int i = 0; i < bulletVector.size(); i++)
	{
		auto bullet = bulletVector.at(i);
		if (bullet->getParent() == NULL)
		{
			return;
		}
		auto  bulletRect = Rect(bullet->getPositionX() + bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
			  bullet->getPositionY() + bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
			  bullet->getContentSize().width,
			  bullet->getContentSize().height);

		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			//auto enemyRect = enemy->sprite->getBoundingBox();
			auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 4,
				 enemy->sprite->getPositionY() - enemy->sprite->getContentSize().height / 4,
				 enemy->sprite->getContentSize().width / 2,
				 enemy->sprite->getContentSize().height / 2);
			/*auto aa = enemy->sprite->getPositionX();
			auto bb = enemy->sprite->getPositionY();*/
			if (bulletRect.intersectsRect(enemyRect))
			{
				auto currHp = enemy->getCurrHp();
				currHp--;
				enemy->setCurrHp(currHp);

				auto currHpPercentage = enemy->getHpPercentage();
				auto offHp = 100 / enemy->getMaxHp();
				currHpPercentage -= offHp;
				if (currHpPercentage < 0)
				{
					currHpPercentage = 0;
				}
				enemy->setHpPercentage(currHpPercentage);
				enemy->getHpBar()->setPercentage(currHpPercentage);

				if (currHp <= 0)
				{
					enemyNeedToDelete.pushBack(enemy);
					//auto valueMoney = enemy->getVaule();
					//money += valueMoney;
					//auto moneyText = std::to_string(money);
					//moneyLabel->setString(moneyText);
				}
				bulletNeedToDelete.pushBack(bullet);
				break;
			}
		}
		for (EnemyBase* enemyTemp : enemyNeedToDelete)
		{
			enemyTemp->enemyExpload();
			instance->enemyVector.eraseObject(enemyTemp);
		}
		enemyNeedToDelete.clear();
	}

	for (Sprite* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
		bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}