/**
* @file Player.cpp
* @author wukef & wyf
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
void Hero::receiveDamage(float damage, Hero*& injuredSprite, Hero*& killer)
{
	injuredSprite->health_ -= (damage - defend_);

	killer->chargeForUlitmateSkill(damage - injuredSprite->defend_);

	if (health_ <= 0)
	{
		die(injuredSprite, killer);
	}
}
/* receiveDamage重载 injuredSprite受伤 毒雾可用 */
void Hero::receiveDamage(float damage, Hero*& injuredSprite)
{
	injuredSprite->health_ -= (damage - defend_);

	if (health_ <= 0)
	{
		die(injuredSprite);
	}
}
/* killer杀死了diedSprite */
void Hero::die(Hero*& diedSprite, Hero*& killer)
{
	if (true == isAlive_)// 免得死很多次人数变负的
	{
		auto energy = Hero::createEnergy(diedSprite, killer);

		diedSprite->getParent()->addChild(energy);

		isAlive_ = false;

		if (diedSprite->dieTag_ == AIDieTag)
		{
			GameData::deleteDiedPlayer();
		}
	}
}
/* die重载 diedSprite死了 毒雾可用 */
void Hero::die(Hero*& diedSprite)
{
	if (true == isAlive_)// 免得死很多次人数变负的
	{
		isAlive_ = false;

		if (diedSprite->dieTag_ == AIDieTag)
		{
			GameData::deleteDiedPlayer();
		}
	}
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
		energy->setPosition(energyGenerator->getPosition());

		energy->addChild(tmp);

		auto moveTo = MoveTo::create(0.1f, energyReceiver->getPosition());
		auto removeSelf = RemoveSelf::create();
		energy->runAction(Sequence::create(moveTo, removeSelf, nullptr));

		auto blink = cocos2d::Blink::create(0.5f, 3);
		energyReceiver->runAction(blink);

		energyReceiver->healthInit_ += EnergyHealthBonus;
		energyReceiver->attack_ += EnergyAttackBonus;
		energyReceiver->defend_ += EnergyDefendBonus;

		energy->autorelease();

		return energy;
	}

	return nullptr;
}
void Hero::recoverHealth()
{
	if (health_ < healthInit_ && true == isAlive_)
	{
		health_ += HealthRecovery;
	}

}

/******************************************攻击状态*************************************************/

/* 返回普攻数值 */
float Hero::dealDamage()
{
	return attack_;
}
/* 返回当前子弹数目 */
float Hero::currentBullet()
{
	if (0 < bullet_ && bullet_ < 1.f)
	{
		bullet_ = 0;
	}
	else if (1.f < bullet_)
	{
		bullet_--;
	}
	return bullet_;
}
/* 大招好了没 */
bool Hero::isUltimateSkillReady()
{
	return ultimateReady_;
}
/* 给大招充能charge点能量 */
void Hero::chargeForUlitmateSkill(float charge)
{
	if (false == ultimateReady_)// 大招还没好时可以继续充能，不释放没法充能
	{
		skill_ += charge;
	}
	if (skill_ >= ultiFull)
	{
		ultimateReady_ = true;
	}
}
/* 确认施放大招 */
void Hero::confirmToReleaseUltimateSkill()
{
	confirm_ = true;
}
/* 是否确认施放大招 */
bool Hero::isReleaseConfirmed()
{
	return confirm_;
}
/* 大招（在子类实现）*/
void Hero::ultimateSkill(Vec2 touchWorldPosition)
{
	;
}
/* 大招放完之后清除进度条 */
void Hero::clearUltimateSkillProgress()
{
	skill_ -= ultiFull;
	ultimateReady_ = false;
}
/* 绑定物理躯干并tag */
void Hero::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// 传引用，否则会被释放掉
{
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize() * 0.5f, PhysicsMaterial(0.f, 0.f, 0.f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(bitmask);// bitmask是碰撞的body种类 这一句是设置种类
	physicsBody->setContactTestBitmask(bitmask);// 这一句是在这个种类碰撞的时候通知
	sprite->setPhysicsBody(physicsBody);
	sprite->setTag(tag);
}
void Hero::recoverBullet()
{
	if (bullet_ < bulletInit_ && true == isAlive_)
	{
		bullet_ += BulletRecovery;
	}

}

/************************************************血条和蓝条**********************************************************************/

//血条HP
void Hero::initHpSlider() 
{
	_hpSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/bloodHp.png", "Hero/FightHero/sliderThumb.png");

	_hpSlider->setEnabled(false);//让滑动条无法改变进度值
	_hpSlider->setMaximumValue(healthInit_);//设置滑动条的最大值
	_hpSlider->setMinimumValue(0);//设置滑动条的最小值
	_hpSlider->setValue(health_);//设置滑动条的当前值
	_hpSlider->setPosition(getHpSliderPos());//设置血条的位置
	this->addChild(_hpSlider);
}

Vec2 Hero::getHpSliderPos() 
{
	return Vec2(0, HpSliderPosY);
}

void Hero::update_hp()
{
	if (_hpSlider < 0)
	{
		_hpSlider = 0;
	}
	if (_hpSlider) 
	{
		_hpSlider->setValue(health_);
		_hpSlider->setPosition(getHpSliderPos());
	}
}
//蓝条MP
void Hero::initMpSlider() 
{
	_mpSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/bulletMp.png", "Hero/FightHero/sliderThumb.png");

	_mpSlider->setEnabled(false);//让滑动条无法改变进度值
	_mpSlider->setMaximumValue(bulletInit_);//设置滑动条的最大值
	_mpSlider->setMinimumValue(0);//设置滑动条的最小值
	_mpSlider->setValue(bullet_);//设置滑动条的当前值
	_mpSlider->setPosition(getMpSliderPos());//设置蓝条的位置
	this->addChild(_mpSlider);
}

Vec2 Hero::getMpSliderPos()
{
	return Vec2(0, MpSliderPosY);
}

void Hero::update_mp()
{
	if (_mpSlider < 0)
	{
		_mpSlider = 0;
	}
	if (_mpSlider) 
	{
		_mpSlider->setValue(bullet_);
		_mpSlider->setPosition(getMpSliderPos());
	}
}

//怒气值SP
void Hero::initSpSlider()
{
	_spSlider = ControlSlider::create("Hero/FightHero/bloodBg.png", "Hero/FightHero/heroSp.png", "Hero/FightHero/sliderThumb.png");

	_spSlider->setEnabled(false);//让滑动条无法改变进度值
	_spSlider->setMaximumValue(skillInit_);//设置滑动条的最大值
	_spSlider->setMinimumValue(0);//设置滑动条的最小值
	_spSlider->setValue(skill_);//设置滑动条的当前值
	_spSlider->setPosition(getSpSliderPos());//设置蓝条的位置
	this->addChild(_spSlider);
}

Vec2 Hero::getSpSliderPos() 
{
	return Vec2(0, SpSliderPosY);
}

void Hero::update_sp()
{
	if (_spSlider < 0)
	{
		_spSlider = 0;
	}
	if (_spSlider) 
	{
		_spSlider->setValue(skill_);
		_spSlider->setPosition(getSpSliderPos());
	}
}