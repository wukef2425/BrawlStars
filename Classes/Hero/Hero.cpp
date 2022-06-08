/**
* @file Player.cpp
* @author wukef
*/

#include "Hero.h"
#include "Consts.h"

bool Hero::isUltimateSkillReady()
{
	return ultimateProgress_;
}

bool Hero::isAlive()
{
	return isAlive_;
}

void Hero::receiveDamage(int damage, Hero*& sprite)
{

	health_ -= (damage - defend_);

	if (health_ <= 0)
	{
		// 给能量块绑定了物理躯干getPosition会失效？？是map问题吗？
		auto energy = cocos2d::Sprite::create("Hero/energy.png");
		energy->setPosition(sprite->getPosition());
		sprite->getParent()->addChild(energy);

		isAlive_ = false;
	}
	//auto blink = cocos2d::Blink::create(0.5f, 3);// 有概率出现打死了还有子弹的bug？？
	//sprite->runAction(blink);
}

void Hero::dealDamage(int damage)
{
	;
}

void Hero::ultimateSkill()
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