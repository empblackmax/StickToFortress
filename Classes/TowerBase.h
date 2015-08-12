#ifndef _TowerBase_H_
#define _TowerBase_H_

#include "cocos2d.h"

USING_NS_CC;

class TowerBase : public Sprite
{
public:
	TowerBase();

	virtual bool init();
	CREATE_FUNC(TowerBase);

	CC_SYNTHESIZE(int, lethality, Lethality);   // 杀伤力
	CC_SYNTHESIZE(float, rate, Rate);  //发射速率
	
};


#endif 
