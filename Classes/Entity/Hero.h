/**
* @file Hero.h
* @author wukef
*/

#ifndef __Hero_H__
#define __Hero_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
USING_NS_CC;

class Hero :public cocos2d::Sprite
{
protected:

	friend class StatusBar;// 状态条 包括生命和弹药数量两种

	class HealthBar;// 生命条

	class BulletBar;// 弹药条

	bool isAlive_ = true;// 是否存活

	bool ultimateProgress_ = false;// 大招进度条

	ControlSlider* _hpSlider;//血条
	int health_;// 当前生命
	int healthInit_;//初始生命

	ControlSlider* _mpSlider;//蓝条
	int bullet_;// 当前弹药
	int bulletInit_;//初始生命

	ControlSlider* _spSlider;//技能条
	int skill_;// 当前积攒怒气值
	int skillInit_;//最大技能值

	int maxHealth_;// 最大生命

	int attack_;// 攻击值

	int defend_;// 防御值

	int energy_;// 死了以后掉落多少能量

	
public:

	Hero* create(const std::string& filename);

	bool isAlive();

	bool isUltimateSkillReady();

	void receiveDamage(int damage, Hero*& sprite);

	virtual void dealDamage(int damage);

	virtual void ultimateSkill();

	void bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag);

	virtual ~Hero() = default;

	void Hero::initHpSlider();
	Point Hero::getHpSliderPos();
	void Hero::update_hp();

	void Hero::initMpSlider();
	Point Hero::getMpSliderPos();
	void Hero::update_mp();

	void Hero::initSpSlider();
	Point Hero::getSpSliderPos();
	void Hero::update_sp();
};

#endif