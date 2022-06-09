#pragma once
#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class GameData
{
public:

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

	static GameData* getInstance();

private:

	static GameData* _instancePlayer;//当前人数


};

#endif // !_GAME_DATA_