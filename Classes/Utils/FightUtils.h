#pragma once
#ifndef _FIGHT_UTILS_H_
#define _FIGHT_UTILS_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class FightUtils
{
public:
	/*枚举所有英雄*/
	enum AllHero
	{
		ChangYi,
		YunHe,
		HaoQing,
		SanYue,
		ShunDe
	};

	/*用来记录战斗场景的一系列属性
    包括选择的人物、地图、人物剩余的个数人物的蓝量血量*/

	static AllHero _hero;		//玩家使用的brawl
	

};

#endif // !_FIGHT_UTILS_H_