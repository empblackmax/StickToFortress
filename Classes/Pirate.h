#ifndef _Pirate_H_
#define _Pirate_H_


#include "EnemyBase.h"
#include "cocos2d.h"

USING_NS_CC;

class Pirate : public EnemyBase
{
public:
	virtual bool init() override;

	static Pirate* createPirate( int hp);
	void enemyExpload();
};


#endif