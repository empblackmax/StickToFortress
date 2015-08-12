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
	//Vector<TowerBase*> towerVector;
	//Vector<GroupEnemy*> groupVector;

	/*CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, groupNum, GroupNum);
	CC_SYNTHESIZE(std::string, curMapName, CurMapName);
	CC_SYNTHESIZE(std::string, currLevelFile, CurrLevelFile);
	CC_SYNTHESIZE(std::string, nextLevelFile, NextLevelFile);
	CC_SYNTHESIZE(bool, isFinishedAddGroup, IsFinishedAddGroup);
	CC_SYNTHESIZE(std::string, curBgName, CurBgName);*/

	bool init();
	void clear();

	static GameController* getInstance();

private:
	static GameController * instance;
};
#endif 