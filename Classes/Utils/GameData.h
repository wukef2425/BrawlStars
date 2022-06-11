#pragma once
#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include "cocos2d.h"

USING_NS_CC;

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

	static AllHero _hero;		 // 用来控制currentPlayer选谁

	static int getRemainingPlayer();

	static void deleteDiedPlayer();

	static void resetPlayerNum();

private:

	static int remainingPlayer;  // 当前人数

};

#endif // !_GAME_DATA_