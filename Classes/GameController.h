#ifndef _GameController_H_
#define _GameController_H_

#include "cocos2d.h"
#include "EnemyBase.h"
#include "TowerBase.h"


USING_NS_CC;

class GameController
{
public:

	Vector<EnemyBase*> enemyVector;
	Vector<Sprite*> bulletVector;

	bool init();
	void clear();

	static GameController* getInstance();

private:
	static GameController * instance;
};
#endif 