#include "Gamepause.h"

USING_NS_CC;
#include "FightScene.h"
#include "Scene/ChooseHero.h"
#include "Scene/StartMenuScene.h"

Scene* Gamepause::scene(RenderTexture* sqr)
{

	Scene* scene = Scene::create();
	Gamepause* layer = Gamepause::create();
	scene->addChild(layer, 1);
	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
  //并将Sprite添加到GamePause场景层中
  //得到窗口的大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。
	back_spr->setFlippedY(true);            //翻转，因为UI坐标和OpenGL坐标不同
	back_spr->setColor(Color3B::GRAY); //图片颜色变灰色
	scene->addChild(back_spr);
	return scene;
}

bool Gamepause::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//图片框框
	auto* background = Sprite::create("Button/pause_background.png");
	background->setScale(1.2f);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2+50);
	addChild(background, 1);
	
	//继续游戏按钮
	auto pContinueItem = cocos2d::MenuItemImage::create(
		"Button/pause_continue.png",
		"Button/pause_continue.png",
		CC_CALLBACK_1(Gamepause::menuContinueCallback, this));

	pContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-50));

	pMenu = cocos2d::Menu::create(pContinueItem, nullptr);
	pMenu->setScale(1.6f);
	pMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(pMenu, 2);


	//重新开始游戏按钮
	auto pRestartItem = cocos2d::MenuItemImage::create(
		"Button/pause_restart.png",
		"Button/pause_restart.png",
		CC_CALLBACK_1(Gamepause::menuRestartCallback, this));

	pRestartItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));


	pMenu = cocos2d::Menu::create(pRestartItem, nullptr);
	pMenu->setScale(1.6f);
	pMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(pMenu, 2);

	//回主界面
	auto pLoginItem = cocos2d::MenuItemImage::create(
		"Button/pause_login.png",
		"Button/pause_login.png",
		CC_CALLBACK_1(Gamepause::menuLoginCallback, this));

	pLoginItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+50));


	pMenu = cocos2d::Menu::create(pLoginItem, nullptr);
	pMenu->setScale(1.6f);
	pMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(pMenu, 2);

	return true;
}
//继续游戏
void Gamepause::menuContinueCallback(Ref* pSender)
{
	Director::getInstance()->popScene();

}
//重新开始游戏
void Gamepause::menuRestartCallback(Ref* pSender)
{
	GameData::resetPlayerNum();
	Director::getInstance()->replaceScene(ChooseHero::createScene());
}
//回主界面
void Gamepause::menuLoginCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(StartMenuScene::createScene());
}

