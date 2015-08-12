#ifndef _Thief_H_
#define _Thief_H_

#include "EnemyBase.h"
#include "cocos2d.h"

USING_NS_CC;

class Thief : public EnemyBase
{
public:
    virtual bool init() override;
    
    static Thief* createThief(/*Vector<Node*> points,*/ int hp);
    
    //void changeDirection(float dt);
    void enemyExpload();
    
};



#endif 
