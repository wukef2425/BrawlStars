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
/************************************************血条和蓝条**********************************************************************/
//to wkf 蓝条和血条已经设计好了，然后现在的问题是怎么调用
//想法是可以设成player的子节点但是我不会调哭泣 或者是在position那里，返回的是人物的position有关内容
//这个也可以调到fightscene界面，但是这样又涉及到了另一些信息的调用

//血条HP
void Hero::initHpSlider() {

	_hpSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/bloodHp.png", "Hero/FightHero/sliderThumb.png");

	_hpSlider->setEnabled(false);//让滑动条无法改变进度值
	_hpSlider->setMaximumValue(healthInit_);//设置滑动条的最大值
	_hpSlider->setMinimumValue(0);//设置滑动条的最小值
	_hpSlider->setValue(health_);//设置滑动条的当前值
	_hpSlider->setPosition(getHpSliderPos());//设置血条的位置
	this->addChild(_hpSlider);
}

Point Hero::getHpSliderPos() {

	//这个想要设计成坐标为人物的getposition
	return Point(0, 0);
}

void Hero::update_hp() {

	if (_hpSlider < 0)
		_hpSlider = 0;
	if (_hpSlider) {
		_hpSlider->setValue(health_);
		_hpSlider->setPosition(getHpSliderPos());
	}

}
//蓝条MP
void Hero::initMpSlider() {

	_mpSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/bulletMp.png", "Hero/FightHero/sliderThumb.png");

	_mpSlider->setEnabled(false);//让滑动条无法改变进度值
	_mpSlider->setMaximumValue(bulletInit_);//设置滑动条的最大值
	_mpSlider->setMinimumValue(0);//设置滑动条的最小值
	_mpSlider->setValue(bullet_);//设置滑动条的当前值
	_mpSlider->setPosition(getMpSliderPos());//设置蓝条的位置
	this->addChild(_mpSlider);

}

Point Hero::getMpSliderPos() {

	//这个想要设计成坐标为人物的getposition
	return Point(0, 0);
}

void Hero::update_mp() {

	if (_mpSlider < 0)
		_mpSlider = 0;
	if (_mpSlider) {
		_mpSlider->setValue(bullet_);
		_mpSlider->setPosition(getMpSliderPos());
	}

}

//还得设计个能量条，积攒大招用的
//怒气值SP
void Hero::initSpSlider() {

	_spSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/heroSp.png", "Hero/FightHero/sliderThumb.png");

	_spSlider->setEnabled(false);//让滑动条无法改变进度值
	_spSlider->setMaximumValue(skillInit_);//设置滑动条的最大值
	_spSlider->setMinimumValue(0);//设置滑动条的最小值
	_spSlider->setValue(skill_);//设置滑动条的当前值
	_spSlider->setPosition(getSpSliderPos());//设置蓝条的位置
	this->addChild(_spSlider);

}

Point Hero::getSpSliderPos() {

	//这个想要设计成坐标为人物的getposition
	return Point(0, 0);
}

void Hero::update_sp() {

	if (_spSlider < 0)
		_spSlider = 0;
	if (_spSlider) {
		_spSlider->setValue(skill_);
		_spSlider->setPosition(getSpSliderPos());
	}

}