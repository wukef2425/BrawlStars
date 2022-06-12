#include "VolumeScene.h"

USING_NS_CC;

#include "Scene/SetScene.h"

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* VolumeScene::scene()
{
	Scene* scene = Scene::create();
	VolumeScene* layer = VolumeScene::create();
	scene->addChild(layer, 1);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* back_spr = Sprite::create("Scene/VolumeScene.png");
	back_spr->setScale(0.8f);
	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); 
    
	scene->addChild(back_spr);
	return scene;
}

bool VolumeScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//回到设置界面
	auto pReturnItem = cocos2d::MenuItemImage::create(
		"Button/ReturnSet.png",
		"Button/ReturnSet.png",
		CC_CALLBACK_1(VolumeScene::settingSceneCallback, this));

	pReturnItem->setPosition(Vec2(8*visibleSize.width/10, 7*visibleSize.height/9));


	pMenu = cocos2d::Menu::create(pReturnItem, nullptr);
	pMenu->setScale(1.2f);
	pMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(pMenu, 2);

	return true;
}

//回设置界面
void VolumeScene::settingSceneCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
