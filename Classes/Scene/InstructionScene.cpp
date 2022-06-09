/**
*@file StartScene.cpp
* @author wyf
*/
#include "InstructionScene.h"
#include "cocos2d.h"
USING_NS_CC;

Scene* InstructionScene::createScene()
{
    return InstructionScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool InstructionScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //…Ë÷√±≥æ∞Õº∆¨
    auto* setScene = Sprite::create("Scene/SetScene.jpg");        //…Ë÷√¿‡±≥æ∞Õº
    setScene->setScale(1.05f);
    setScene->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //»√±≥æ∞ÕºœÒæ”÷–œ‘ æ
    addChild(setScene, 0);
   
    return true;
}
