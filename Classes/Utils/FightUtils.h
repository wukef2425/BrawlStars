#pragma once
#ifndef _FIGHT_UTILS_H_
#define _FIGHT_UTILS_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
/*记录战争中一些状态
* 选择的人物、地图
* 英雄的数量以及剩余的英雄数
*/
class FightUtils
{
public:
	/*枚举所有地图*/
	enum AllMap
	{
		MapA,
		MapB,
		MapC
	};
	/*枚举所有英雄*/
	enum AllHero
	{
		ChangYi,
		YunHe,
		HaoQing,
		SanYue,
		ShunDe
	};
	/*静态成员变量，存储切换场景时用到的信息*/
	static AllMap _map;
	static AllHero _hero;		//玩家使用的brawl
	static INT32 _heroNumber;	//brawler总数

	/*音乐设置*/
	static bool _musicOn;			//记录是否播放音乐
	static bool _effectOn;			//记录是否播放音效


};

#endif // !_FIGHT_UTILS_H_