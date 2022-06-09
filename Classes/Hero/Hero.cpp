/**
* @file Player.cpp
* @author wukef
*/

#include "Hero.h"
#include "Consts.h"
#include "Scene/FightScene.h"


/******************************************生命状态*************************************************/

/* 是否存活 */
bool Hero::isAlive()
{
	return isAlive_;
}
/* killer使injuredSprite受到damage点伤害 */
void Hero::receiveDamage(int damage, Hero*& injuredSprite, Hero*& killer)
{
	injuredSprite->health_ -= (damage - defend_);// 这数据似乎不太对35的攻击打一下就死了？

	killer->chargeForUlitmateSkill(damage - injuredSprite->defend_);

	if (health_ <= 0)
	{ 
		die(injuredSprite, killer);
		injuredSprite->getParent()->unschedule(CC_SCHEDULE_SELECTOR(FightScene::createAI));
		injuredSprite->removeFromParentAndCleanup(true);
	}
}
/* killer杀死了diedSprite */
void Hero::die(Hero*& diedSprite, Hero*& killer)
{
	auto energy = Hero::createEnergy(diedSprite, killer);

	diedSprite->getParent()->addChild(energy);

	isAlive_ = false;
}
/* energyGenerator产生能量给energyReceiver */
Hero* Hero::createEnergy(Hero*& energyGenerator, Hero*& energyReceiver)
{
	auto energy = new(std::nothrow) Hero;

	if (energy == nullptr)
	{
		return nullptr;
	}

	auto tmp = Sprite::create("Hero/energy.png");

	if (tmp != nullptr)
	{
		//energy->bindPhysicsBodyAndTag(tmp, EnemyBulletAndPlayerBitmask, PlayerTag);// 加了物理特性position不对

		energy->setPosition(energyGenerator->getPosition());

		energy->addChild(tmp);

		auto moveTo = MoveTo::create(0.1f, energyReceiver->getPosition());
		auto removeSelf = RemoveSelf::create();
		energy->runAction(Sequence::create(moveTo, removeSelf, nullptr));

		auto blink = cocos2d::Blink::create(0.5f, 3);
		energyReceiver->runAction(blink);

		energy->autorelease();

		return energy;
	}

	return nullptr;
}

/******************************************攻击状态*************************************************/

/* 返回普攻数值 */
int Hero::dealDamage()
{
	return attack_;
}
/* 大招好了没 */
bool Hero::isUltimateSkillReady()
{
	return ultimateReady_;
}
/* 给大招充能charge点能量 */
void Hero::chargeForUlitmateSkill(int charge)
{
	ultimateProgress_ += charge;
	if (ultimateProgress_ >= ultiFull)
	{
		ultimateReady_ = true;
		ultimateProgress_ -= ultiFull;
	}
}
void Hero::ultimateSkill()
{
	;
}
void Hero::clearUltimateSkillProgress()
{
	ultimateReady_ = false;
}

void Hero::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// 传引用，否则会被释放掉
{
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize() * 0.5f, PhysicsMaterial(0.f, 0.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(bitmask);// bitmask是碰撞的body种类 这一句是设置种类
	physicsBody->setContactTestBitmask(bitmask);// 这一句是在这个种类碰撞的时候通知
	sprite->setPhysicsBody(physicsBody);
	sprite->setTag(tag);
}