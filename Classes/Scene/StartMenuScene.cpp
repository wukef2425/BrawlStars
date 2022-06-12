/**
*@file StartMenuScene.cpp
* @author wyf
*/

#include "cocos2d.h"
#include "StartMenuScene.h"
#include "Scene/SetScene.h"
#include "Scene/ChooseHero.h"
#include "User/UserInfo.h"

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

	initDecoration();
	initSetButton();
	initUserButton();
	initStartButton();
	initExitButton();

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);

	return true;
}

void StartMenuScene::initDecoration()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto* background = Sprite::create("Scene/MenuScene.jpg");       
	background->setScale(1.05f);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);       
	addChild(background, 0);

	auto* character = Sprite::create("StarMenuCuteHe.png");
	character->setPosition(origin.x + (character->getContentSize().width * 4) / 5, origin.y + (character->getContentSize().height * 2) / 5);      
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
	GameData::resetPlayerNum();
	Director::getInstance()->replaceScene(ChooseHero::createScene());

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
		float y = origin.y + exitBotton->getContentSize().height*2;
		exitBotton->setScale(1.3f);
		exitBotton->setPosition(cocos2d::Vec2(x, y));
	}

	exitButton_ = cocos2d::Menu::create(exitBotton, nullptr);
	this->addChild(exitButton_, 1);
	exitButton_->setPosition(cocos2d::Vec2::ZERO);
}

void StartMenuScene::exitCallback(cocos2d::Ref* pSender)
{
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

	auto userButton = cocos2d::MenuItemImage::create("UserYunHe.png", "UserYunHe.png", CC_CALLBACK_1(StartMenuScene::userCallback, this));
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
	Director::getInstance()->replaceScene(UserInfo::createScene());
}









