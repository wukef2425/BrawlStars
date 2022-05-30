/**
*@file StartMenuScene.cpp
* @author wyf
*/
#include "StartMenuScene.h"
#include "SetScene.h"
#include "FightScene.h"
USING_NS_CC;

Scene* StartMenuScene::createScene()
{
	return StartMenuScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//加载小插件
	initDecoration();//一些让画面美观的东西
	initSetButton();//设置界面，里面有规则说明/音量调整/返回原来界面
	initUserButton();//用户信息查看界面
	initStartButton();//开始按钮
	initOnlineButton();//联网开始按钮
	initExitButton();//离开按钮
	//loadingFightScene();//斗争地图加载,不太理解的是为什么要提前加载好，不可以去了界面再加吗

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);//API常用接口，目前我也看不懂

	return true;
}

void StartMenuScene::initDecoration()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//设置背景图片
	auto* background = Sprite::create("Scene/MenuScene.jpg");        //创建精灵类，背景图片为background.jpg
	background->setScale(1.05f);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //让背景图像居中显示
	addChild(background, 0);
	//设置人物肖像
	auto* character = Sprite::create("StarMenuCuteHe.png");
	character->setPosition(origin.x + (character->getContentSize().width * 4) / 5, origin.y + (character->getContentSize().height * 2) / 5);        //让背景图像居中显示
	addChild(character, 1);
}

void StartMenuScene::initStartButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto startButton = cocos2d::MenuItemImage::create("Button/Start.png", "Button/Start.png", CC_CALLBACK_1(StartMenuScene::startCallback, this));

	if (startButton == nullptr ||
		startButton->getContentSize().width <= 0 ||
		startButton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - startButton->getContentSize().width;
		float y = origin.y + startButton->getContentSize().height * 3;
		startButton->setScale(1.3f);
		startButton->setPosition(cocos2d::Vec2(x, y));
	}
	startButton_ = cocos2d::Menu::create(startButton, nullptr);
	this->addChild(startButton_, 1);
	startButton_->setPosition(cocos2d::Vec2::ZERO);
}

void StartMenuScene::startCallback(cocos2d::Ref* pSender)
{
	//fightScene_->settingLayer_->backgroundMusicID_ = cocos2d::AudioEngine::play2d("audio/bgm_1low.mp3", true, .5);
	//加了一个背景音乐，目前我们还是不加吧
	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(false);
	//Director::getInstance()->replaceScene(FightScene::createScene());
}

/*目前看不懂，是联网状态要考虑的东西
void StartMenuScene::startOnlineCallback(cocos2d::Ref* pSender)
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	auto label = cocos2d::Label::createWithTTF("Connecting to Server...", "fonts/IRANYekanBold.ttf", 36);
	label->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	label->setPosition(winSize / 2);
	label->enableOutline(cocos2d::Color4B(194, 69, 69, 255), 5);
	auto remove = cocos2d::RemoveSelf::create();
	auto delay = cocos2d::DelayTime::create(.1f);
	auto fade2 = cocos2d::FadeTo::create(1, 0);

	auto connect = cocos2d::CallFunc::create([=]() {
		Client::getInstance()->initialization();
		Client::getInstance()->Send("Join");
		cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(false);
		goToFightScene();
		});
	label->runAction(cocos2d::Sequence::create(delay, connect, fade2, remove, nullptr));
	addChild(label, 3);
}*/

void StartMenuScene::initOnlineButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto onlineButton = cocos2d::MenuItemImage::create("Button/OnlineStart.png", "Button/OnlineStart.png", CC_CALLBACK_1(StartMenuScene::startCallback, this));

	if (onlineButton == nullptr ||
		onlineButton->getContentSize().width <= 0 ||
		onlineButton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - onlineButton->getContentSize().width;
		float y = origin.y + onlineButton->getContentSize().height * 2;
		onlineButton->setScale(1.3f);
		onlineButton->setPosition(cocos2d::Vec2(x, y));
	}

	onlineButton_ = cocos2d::Menu::create(onlineButton, nullptr);
	this->addChild(onlineButton_, 1);
	onlineButton_->setPosition(cocos2d::Vec2::ZERO);
}

void StartMenuScene::initExitButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto exitBotton = cocos2d::MenuItemImage::create("Button/Leave.png", "Button/Leave.png", CC_CALLBACK_1(StartMenuScene::exitCallback, this));
	if (exitBotton == nullptr ||
		exitBotton->getContentSize().width <= 0 ||
		exitBotton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - exitBotton->getContentSize().width;
		float y = origin.y + exitBotton->getContentSize().height;
		exitBotton->setScale(1.3f);
		exitBotton->setPosition(cocos2d::Vec2(x, y));
	}

	exitButton_ = cocos2d::Menu::create(exitBotton, nullptr);
	this->addChild(exitButton_, 1);
	exitButton_->setPosition(cocos2d::Vec2::ZERO);
}

void StartMenuScene::exitCallback(cocos2d::Ref* pSender)
{
	//Client::clientRelease();//也许大概是清空内存的意思？？？
	Director::getInstance()->end();
}

void StartMenuScene::initSetButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto setButton = MenuItemImage::create(
		"SetButton.png",
		"SetButton.png",
		CC_CALLBACK_1(StartMenuScene::setCallback, this));

	if (setButton == nullptr ||
		setButton->getContentSize().width <= 0 ||
		setButton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - setButton->getContentSize().width;
		float y = visibleSize.height - setButton->getContentSize().height;
		setButton->setPosition(cocos2d::Vec2(x, y));
	}
	setButton_ = cocos2d::Menu::create(setButton, nullptr);
	this->addChild(setButton_, 1);
	setButton_->setPosition(cocos2d::Vec2::ZERO);
}

void StartMenuScene::setCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(SetScene::createScene());
}

void StartMenuScene::initUserButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto userButton = cocos2d::MenuItemImage::create("UserYunHe.png", "UserYunHe.png", CC_CALLBACK_1(StartMenuScene::startCallback, this));
	//加入头像，想改成动态的，到时候看看行不行
	if (userButton == nullptr ||
		userButton->getContentSize().width <= 0 ||
		userButton->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + userButton->getContentSize().width;
		float y = visibleSize.height - userButton->getContentSize().height;
		userButton->setScale(1.3f);
		userButton->setPosition(cocos2d::Vec2(x, y));
	}

	userButton_ = cocos2d::Menu::create(userButton, nullptr);
	this->addChild(userButton_, 1);
	userButton_->setPosition(cocos2d::Vec2::ZERO);
	//加入用户信息框，可以显示用户的昵称和等级，也是动态的可以改的

}

void StartMenuScene::userCallback(cocos2d::Ref* pSender)
{
	//Director::getInstance()->replaceScene(UserInfo::createScene());
}

/*不理解为什么要提前加载而不是打开新界面之后再加载，我想搞成打开界面后再加载
void StartMenuScene::loadingFightScene()
{
	auto snowMap= TMXTiledMap::create("Map/SnowMap.tmx");
	snowMap->setPosition(Vec2(0, 0));//位置还需要再次确定一下o
	addChild(snowMap);

	snowMap = FightScene::create(_tileMap1, _tileMap2, _tileMap3, Obstacle::createObsSet(1), 1);//添加地图以及障碍物
	snowMap->bindPlayer(Player::create("MIKU/idle_down/idle_down1.png"));//这个加载了用户
	snowMap->retain();//先看看是啥

	//AudioEngine::preload("audio/bgm_1low.mp3");//加载音乐
}*/

/*void StartMenuScene::loadingFightScene()
{
	auto _tileMap1 = TMXTiledMap::create("map/map_1/map/bottomMap.tmx");//这个好像是瓦片地图的槽子哦
	_tileMap1->setPosition(Vec2(0, 0));

	auto _tileMap2 = TMXTiledMap::create("map/map_1/map/middleMap.tmx");
	_tileMap2->setPosition(Vec2(0, 50 * 32));

	auto _tileMap3 = TMXTiledMap::create("map/map_1/map/topMap.tmx");
	_tileMap3->setPosition(Vec2(0, 100 * 32));
	//学长是把瓦片地图分为三部分来加载，所以载入场景的时候也是三部分载入的
	fightScene_ = FightScene::create(_tileMap1, _tileMap2, _tileMap3, Obstacle::createObsSet(1), 1);//添加地图以及障碍物
	fightScene_->bindPlayer(Player::create("MIKU/idle_down/idle_down1.png"));//这个加载了用户
	fightScene_->retain();//先看看是啥


	AudioEngine::preload("audio/bgm_1low.mp3");//加载音乐
}*/

