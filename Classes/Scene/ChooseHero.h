#ifndef _CHOOSEHERO_H_
#define _CHOOSEHERO_H_

#include "cocos2d.h"
#include "Scene/FightScene.h"


USING_NS_CC;

class ChooseHero : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	//预加载战斗场景
	void ChooseHero::preLoadingFightScene();
	//预加载按钮
	void initButton();
	//英雄选择按钮
	void initHeroButton();
	//按钮回调函数
	void ChooseHero::startGame(cocos2d::Ref* pSender);
	void ChooseHero::backToMenu(cocos2d::Ref* pSender);
	//英雄回调函数
	void menuShunDeCallback(cocos2d::Ref* pSender);
	void menuHaoQingCallback(cocos2d::Ref* pSender);
	void menuYunHeCallback(cocos2d::Ref* pSender);
	void menuChangYiCallback(cocos2d::Ref* pSender);
	void menuSanYueCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(ChooseHero);

private:

	cocos2d::Menu* backBtn_;
	cocos2d::Menu* enterBtn_;
	cocos2d::Menu* heroButton;

	FightScene* fightScene_;
};

#endif

