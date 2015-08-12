#include "TowerBase.h"


TowerBase::TowerBase()
: lethality(0)
, rate(0)

{
}

bool TowerBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	//this->scheduleUpdate();
	return true;
}



