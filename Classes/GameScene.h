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
	void initBornEnemyVector();
	void CollisionDetection(float dt);
	void addEnemy(float dt);

	EnemyBase* creatEnemy();
private:
	TMXTiledMap* _map;
	TMXLayer* _objects;
	Size winSize;
	TMXObjectGroup* _objectsgroup;
	Arrow* _arrow;
	float px, py;
	Sprite* _point;
	Vector<Node*> _bornEnemy;
	GameController* instance;
	EnemyBase* currenemy;
};

#endif