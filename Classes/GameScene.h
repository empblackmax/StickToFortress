#ifndef _GameScene_H_
#define _GameScene_H_

#include "cocos2d.h"
#include "Thief.h"
#include "Bandit.h"
#include "Pirate.h"
#include "Arrow.h"
#include "GameController.h"

USING_NS_CC;

class GameScene :public Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(GameScene);

	void setViewCenter(Point position);

	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	void initBornEnemyVector();//初始化可能产生怪物的所有地点
	void CollisionDetection(float dt);//碰撞检测
	void addEnemy(float dt);//添加怪物到场景

	EnemyBase* creatEnemy();
private:
	TMXTiledMap* _map;//地图
	TMXLayer* _bgLayer;//背景层
	Size winSize;
	TMXObjectGroup* _objectsgroup;//对象组
	Arrow* _arrow;//弓箭
	float px, py;
	Sprite* _point;//准星
	Vector<Node*> _bornEnemy;//怪物出现地点
	GameController* instance;
	EnemyBase* currenemy;
};

#endif