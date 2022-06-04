#ifndef _CHOOSEHERO_H_
#define _CHOOSEHERO_H_

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "Scene/FightScene.h"
#include "Scene/StartMenuScene.h"
//#include "Hero/HeroMessage.h"
//#include "Hero/HeroMessageUtil.h"

USING_NS_CC;

class ChooseHero : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	//预加载战斗场景
	void ChooseHero::preLoadingFightScene();

	void initButton();
	
	//按钮回调函数
	void ChooseHero::startGame(cocos2d::Ref* pSender);
	void ChooseHero::backToMenu(cocos2d::Ref* pSender);
	void ChooseHero::leftHero(Ref* pSender);
	void ChooseHero::rightHero(Ref* pSender);

	//void loadHeroes();

	//void initHeroMsg();

	void setCurHeroMsg(int index);
	
	CREATE_FUNC(ChooseHero);

private:
	
	cocos2d::Menu* backBtn_;
	cocos2d::Menu* enterBtn_;
	cocos2d::Menu* leftBtn_;
	cocos2d::Menu* rightBtn_;

	int cur_hero_index=0;
	
	//std::vector<HeroItem> heroArray;
	
	FightScene* fightScene_;
};

/*

class HeroItem : public Ref {

	friend class ChooseHero;

public:

	HeroItem(const std::string& name, const int id, const std::string& resourceName);
	~HeroItem();

private:
	std::string name;
	int id;
	std::string resourceName;
	
};
*/

#endif
