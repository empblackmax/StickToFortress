#ifndef _Bandit_H_
#define _Bandit_H_


#include "EnemyBase.h"
#include "cocos2d.h"

USING_NS_CC;


class Bandit : public EnemyBase
{
public:
	virtual bool init() override;

	static Bandit* createBandit( int hp);//创建怪物
	void enemyExpload();//销毁怪物
};


#endif