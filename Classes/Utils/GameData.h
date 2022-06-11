#pragma once
#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include "cocos2d.h"

USING_NS_CC;

class GameData
{
public:

	static int getRemainingPlayer();

	static void deleteDiedPlayer();

	static void resetPlayerNum();

	static int GameData::getChooseHero();

	static void ChangeHeroToShunDe();
	static void ChangeHeroToHaoQing();
	static void ChangeHeroToChangYi();
	static void ChangeHeroToYunHe();
	static void ChangeHeroToSanYue();

private:

	static int remainingPlayer;  // 当前人数

	static int _chooseHero;
};

#endif // !_GAME_DATA_