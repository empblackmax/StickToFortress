#ifndef _Arrow_H_
#define _Arrow_H_

#include "TowerBase.h"
#include "GameController.h"


class Arrow :public TowerBase
{
public:

	virtual bool init();
	CREATE_FUNC(Arrow);

	
	void shoot(float dt);
	void removeBullet(Node* pSender);
	Sprite* ArrowBullet();
	void rotate();
	CC_SYNTHESIZE(Point,touchPosition,TouchPosition);
	//void shootPoint(Point position);

private:
	Sprite* rotateArrow;
	Vector<Sprite*> arrowBullet;
	//Point touchPosition;

};

#endif 
