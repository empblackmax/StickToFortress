#ifndef _EnemyBase_H_
#define _EnemyBase_H_

#include "cocos2d.h"

USING_NS_CC;

class EnemyBase : public Sprite
{
public:
	EnemyBase();
	~EnemyBase();
	virtual bool init() override;
	CREATE_FUNC(EnemyBase);

	Animation* createAnimation(std::string prefixName, int framesNum, float delay);//创建动画
	//virtual void changeDirection(float dt){};
	virtual void enemyExpload(){};
	//Node* currPoint();//当前路径点
	//Node* nextPoint();//下一路径点
	//void runFllowPoint();
	//void setPointsVector(Vector<Node*> points);//设置路径点集
	void createAndSetHpBar();//血条
	void moveToArrow(Point position1, Point position2);
private:
	//Vector<Node*> pointsVector;//路径点集
	
protected:
	//int pointCounter;
	Animation *animationRight;//左右动画
	Animation *animationLeft;
	Animation *animationExplode;
	CC_SYNTHESIZE(float, runSpeed, RunSpeed);
	CC_SYNTHESIZE(float, maxHp, MaxHp);
	CC_SYNTHESIZE(float, vaule, Vaule);
	CC_SYNTHESIZE(float, currHp, CurrHp);
	CC_SYNTHESIZE(float, hpPercentage, HpPercentage);
	CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);
	CC_SYNTHESIZE(bool, enemySuccessful, EnemySuccessful);
	Sprite* sprite;
	Sprite* hpBgSprite;
};



#endif 
