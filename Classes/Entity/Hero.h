/**
* @file Hero.h
* @author wukef & wyf
*/

#ifndef __Hero_H__
#define __Hero_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "Consts.h"

USING_NS_CC_EXT;
USING_NS_CC;

class Hero :public cocos2d::Sprite
{
protected:

	bool isAlive_ = true;// 是否存活

	bool ultimateReady_ = false;// 大招好了没

	int attack_;// 攻击值

	int defend_;// 防御值

	ControlSlider* _hpSlider;//血条
	int health_;// 当前生命
	int healthInit_;//初始生命

	ControlSlider* _mpSlider;// 蓝条
	int bullet_ = bulletFull;// 当前弹药
	int bulletInit_ = bulletFull;// 初始弹药

	ControlSlider* _spSlider;// 技能条
	int skill_ = 0;// 当前积攒怒气值
	int skillInit_ = ultiFull;// 最大技能值

public:

	/* 生命状态 */

	bool isAlive();

	void receiveDamage(int damage, Hero*& injuredSprite, Hero*& killer);

	void die(Hero*& diedSprite, Hero*& killer);

	Hero* createEnergy(Hero*& energyGenerator, Hero*& energyReceiver);

	
	/* 攻击状态 */

	int dealDamage();

	int currentBullet();

	bool isUltimateSkillReady();

	void chargeForUlitmateSkill(int charge);
	
	virtual void ultimateSkill();

	void clearUltimateSkillProgress();

	void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

	
	/* UI */
	
	void Hero::initHpSlider();
	Vec2 Hero::getHpSliderPos();
	void Hero::update_hp();

	void Hero::initMpSlider();
	Vec2 Hero::getMpSliderPos();
	void Hero::update_mp();

	void Hero::initSpSlider();
	Vec2 Hero::getSpSliderPos();
	void Hero::update_sp();


	virtual ~Hero() = default;

};

#endif