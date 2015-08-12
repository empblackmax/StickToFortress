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

	Animation* createAnimation(std::string prefixName, int framesNum, float delay);//��������
	//virtual void changeDirection(float dt){};
	virtual void enemyExpload(){};
	//Node* currPoint();//��ǰ·����
	//Node* nextPoint();//��һ·����
	//void runFllowPoint();
	//void setPointsVector(Vector<Node*> points);//����·���㼯
	void createAndSetHpBar();//Ѫ��
	void moveToArrow(Point position1, Point position2);
private:
	//Vector<Node*> pointsVector;//·���㼯
	
protected:
	//int pointCounter;
	Animation *animationRight;//���Ҷ���
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
