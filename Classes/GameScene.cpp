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

	//缓冲池
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");

	//背景图片
	auto bground = Sprite::create("playbg.png");
	bground->setPosition(winSize / 2);
	this->addChild(bground,-2);

	//地图
	_map = TMXTiledMap::create("sticktofortress.tmx");

	_bgLayer = _map->getLayer("BgLayer");


	_objectsgroup = _map->getObjectGroup("Objects");
	auto arrowPoint = _objectsgroup->getObject("ArrowPoint");//弓箭出现的地点
	float x = arrowPoint["x"].asFloat();
	float y = arrowPoint["y"].asFloat();

	//弓箭
	_arrow = Arrow::create();
	_arrow->setPosition(x, y);
	this->addChild(_arrow);
	this->setViewCenter(_arrow->getPosition());

	this->addChild(_map,-1);
	
	//准星
	_point = Sprite::create("point.png");
	_point->setPosition(winSize / 2);
	this->addChild(_point,5);
	_arrow->setTouchPosition(_point->getPosition());//弓箭瞄准准星
	_arrow->rotate();

	//触摸监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch,Event* event)
	{
		px = touch->getLocation().x;
		py = touch->getLocation().y;
		_arrow->schedule(schedule_selector(Arrow::shoot),0.2f);

		return true;
	};
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);

	listener->onTouchEnded=[&](Touch* touch, Event* event)
	{
		_arrow->unschedule(schedule_selector(Arrow::shoot));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	initBornEnemyVector();//初始化可能产生怪物的点
	this->schedule(schedule_selector(GameScene::addEnemy ),2.0f);//添加怪物
	this->schedule(schedule_selector(GameScene::CollisionDetection));//碰撞检测

	return true;
}

void GameScene::setViewCenter(Point position)//以某点为中心
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

void GameScene::onTouchMoved(Touch *touch, Event *unused_event)//移动准星并且让弓箭随准星移动
{
	int mx = touch->getLocation().x - px;
	int my = touch->getLocation().y - py;
	_point->runAction(MoveBy::create(0, Point(mx, my)));
	_arrow->setTouchPosition(_point->getPosition());;
	_arrow->rotate();
	px = touch->getLocation().x;
	py = touch->getLocation().y;
	_arrow->setTouchPosition(_point->getPosition());;
	
}

void GameScene::initBornEnemyVector()
{
	//调用getObject("对象名")方法获取对象组中的对象，它将返回ValueMap类型的值。
	Node *bornPoint = NULL;
	int count = 0;
	ValueMap point;
	point = _objectsgroup->getObject(std::to_string(count));
	//遍历每一个对象
	while (point.begin() != point.end())
	{
		//获取每个对象的X值，Y值
		float x = point.at("x").asFloat();
		float y = point.at("y").asFloat();
		//创建一个Node来保存路径点，并且设置它的坐标位置，然后把它加到pointsVector向量中去，方便以后查找。
		bornPoint = Node::create();
		bornPoint->setPosition(Point(x, y));
		this->_bornEnemy.pushBack(bornPoint);
		count++;
		point = _objectsgroup->getObject(std::to_string(count));
	}
	bornPoint = NULL;
}

void GameScene::addEnemy(float dt)//将敌人加到场景
{
	if (instance->enemyVector.size()>6)
	{
		return;
	}
	int rana = rand() % 3+rand()%5;
	auto enemy = creatEnemy();

	//怪物朝弓箭移动
	enemy->moveToArrow(_bornEnemy.at(rana)->getPosition(), 
		Point(_bornEnemy.at(rana)->getPositionX(), _arrow->getPositionY()));
	this->addChild(enemy);

}

EnemyBase* GameScene::creatEnemy()//随机创造一种类型敌人
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

void GameScene::CollisionDetection(float dt)//碰撞检测
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
		//弓箭的大小
		auto  bulletRect = Rect(bullet->getPositionX() + bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
			  bullet->getPositionY() + bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
			  bullet->getContentSize().width,
			  bullet->getContentSize().height);

		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			//怪物的大小
			auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 4,
				 enemy->sprite->getPositionY() - enemy->sprite->getContentSize().height / 4,
				 enemy->sprite->getContentSize().width / 2,
				 enemy->sprite->getContentSize().height / 2);

			//判断弓箭和怪物是否碰撞
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
				}
				bulletNeedToDelete.pushBack(bullet);
				break;
			}
		}
		for (EnemyBase* enemyTemp : enemyNeedToDelete)//遍历需要销毁的怪物
		{
			enemyTemp->enemyExpload();
			instance->enemyVector.eraseObject(enemyTemp);
		}
		enemyNeedToDelete.clear();
	}

	for (Sprite* bulletTemp : bulletNeedToDelete)//遍历需要销毁的子弹
	{
		instance->bulletVector.eraseObject(bulletTemp);
		bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}