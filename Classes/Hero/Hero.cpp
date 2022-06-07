/**
* @file Player.cpp
* @author wukef
*/

#include "Hero.h"

bool Hero::isAlive()
{
	return isAlive_;
}

void Hero::die()
{
	isAlive_ = false;
}

void Hero::receiveDamage(int damage)
{

	health_ -= (damage - defend_);

	if (health_ <= 0)
	{
		die();
	}
}

void Hero::dealDamage(int damage)
{
	;
}

void Hero::ultimateSkill(int damage)
{
	;
}

void Hero::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// 传引用，否则会被释放掉
{
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize()/10, PhysicsMaterial(0.f, 0.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(bitmask);// bitmask是碰撞的body种类 这一句是设置种类
	physicsBody->setContactTestBitmask(bitmask);// 这一句是在这个种类碰撞的时候通知
	sprite->setPhysicsBody(physicsBody);
	sprite->setTag(tag);
}