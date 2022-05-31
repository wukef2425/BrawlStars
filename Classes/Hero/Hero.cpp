/**
* @file Hero.cpp
* @author wkf
*/

#include "Hero.h"

void Hero::changeHeroTo(cocos2d::Sprite* sprite)
{
	sprite_ = sprite;

	addChild(sprite_);
}

cocos2d::Sprite* Hero::getChosenHero()
{
	return sprite_;// 以公用接口拿到protected的东西
}

bool Hero::isAlive()
{
	return isAlive_;
}

void Hero::die()
{
	isAlive_ = false;;
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