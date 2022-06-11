/**
*@file StartScene.cpp
* @author wyf
*/
#include "InstructionScene.h"
#include "SetScene.h"
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

    //ÉèÖÃ±³¾°Í¼Æ¬
    auto* setScene = Sprite::create("Scene/introductionScene.png");        //ÉèÖÃÀà±³¾°Í¼
    setScene->setScale(0.67f);
    setScene->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //ÈÃ±³¾°Í¼Ïñ¾ÓÖÐÏÔÊ¾
    addChild(setScene, 0);
   //ÉèÖÃ·µ»Ø¼ü
    initReturnMenu();

    return true;
}

void InstructionScene::initReturnMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto returnButton = cocos2d::MenuItemImage::create("Button/SetReturn.png", "Button/SetReturn.png", CC_CALLBACK_1(InstructionScene::menuReturnCallback, this));

    if (returnButton == nullptr ||
        returnButton->getContentSize().width <= 0 ||
        returnButton->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - returnButton->getContentSize().width / 3;
        float y = origin.y + visibleSize.height-returnButton->getContentSize().height / 3;
        returnButton->setScale(0.7f);
        returnButton->setPosition(cocos2d::Vec2(x, y));
    }
    returnButton_ = cocos2d::Menu::create(returnButton, nullptr);
    returnButton_->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(returnButton_, 1);

}

void InstructionScene::menuReturnCallback(Ref* pSender)
{
    //ÞôÏÂ·µ»Ø°´Å¥£¬ÇÐ»»µ½setÒ³Ãæ
    Director::getInstance()->replaceScene(SetScene::createScene());
}