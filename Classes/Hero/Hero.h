/**
* @file Hero.h
* @author wukef
*/

#ifndef __Hero_H__
#define __Hero_H__

#include "cocos2d.h"
USING_NS_CC;

class Hero :public cocos2d::Sprite
{
protected:

	friend class StatusBar;//状态条 包括生命和弹药数量两种

	class HealthBar;//生命条

	class BulletBar;//弹药条

	bool isAlive_ = true;//是否存活

	int health_;//当前生命

	int bullet_;//当前弹药

	int maxHealth_;//最大生命

	int attack_;//攻击值

	int defend_;//防御值

	int energy_;//死了以后掉落多少能量

public:

	bool isAlive();

	virtual void die();

	virtual void receiveDamage(int damage);

	virtual void dealDamage(int damage);

	virtual void ultimateSkill(int damage);

	void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

	virtual ~Hero() = default;

};

#endif