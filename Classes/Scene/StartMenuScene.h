#pragma once
#ifndef __STARTMENU_SCENE_H__
#define __STARTMENU_SCENE_H__

#include "cocos2d.h"

class StartMenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void StartMenuScene::initDecoration();//一些让画面美观的插件

	void StartMenuScene::initSetButton();//设置按钮

	void StartMenuScene::setCallback(cocos2d::Ref* pSender);

	void StartMenuScene::initUserButton();//用户信息查看按钮

	void StartMenuScene::userCallback(cocos2d::Ref* pSender);

	void StartMenuScene::initStartButton();//普通开始按钮

	void StartMenuScene::initOnlineButton();//联网开始按钮

	void StartMenuScene::startCallback(cocos2d::Ref* pSender);

	void StartMenuScene::initExitButton();//离开按钮

	void StartMenuScene::exitCallback(cocos2d::Ref* pSender);

	//void StartMenuScene::loadingFightScene();//地图加载工具,一直搞不懂为啥不能直接加载

	CREATE_FUNC(StartMenuScene);

protected:

	cocos2d::Menu* startButton_;

	cocos2d::Menu* onlineButton_;

	cocos2d::Menu* exitButton_;

	cocos2d::Menu* setButton_;

	cocos2d::Menu* userButton_;


};

#endif // __STARTMENU_SCENE_H__