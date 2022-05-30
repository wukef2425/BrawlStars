/**
*@file SetScene.cpp
* @author wyf
*/
#include "SetScene.h"
#include "StartMenuScene.h"

USING_NS_CC;

Scene* SetScene::createScene()
{
    return SetScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SetScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //记得先设一个背景图片，好统筹的，其实可以花到一起，包括文字啥的，就是考验艺术家王的设计能力，但记得不要遮挡
    //这三个按钮的位置并没有好好放，记得改一下，并且设置可以在里面添加新功能
    initDecoration();//一些让画面美观的东西
    initRuleBooks();
    initVolumeSound();
    initReturnMenu();
    return true;
}

void SetScene::initDecoration()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //设置背景图片
    auto* setScene = Sprite::create("Scene/SetScene.jpg");        //设置类背景图
    setScene->setScale(1.05f);
    setScene->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //让背景图像居中显示
    addChild(setScene, 0);
    //标签
    auto setLabel = Label::createWithTTF("Setting", "fonts/arial.ttf", 60);
    setLabel->enableGlow(Color4B::BLUE);
    if (setLabel == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        setLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - setLabel->getContentSize().height));
        this->addChild(setLabel, 1);
    }
}

void SetScene::initRuleBooks()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto ruleButton = cocos2d::MenuItemImage::create("Button/RuleBooks.png", "Button/RuleBooks.png", CC_CALLBACK_1(SetScene::ruleBooksCallback, this));

    if (ruleButton == nullptr ||
        ruleButton->getContentSize().width <= 0 ||
        ruleButton->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + (visibleSize.width*2)/5-ruleButton->getContentSize().width / 3;
        float y = origin.y + (visibleSize.height*2)/3;
        ruleButton->setScale(0.9f);
        ruleButton->setPosition(cocos2d::Vec2(x, y));
    }
    ruleButton_ = cocos2d::Menu::create(ruleButton, nullptr);
    this->addChild(ruleButton_, 1);
    ruleButton_->setPosition(cocos2d::Vec2::ZERO);
}

void SetScene::ruleBooksCallback(Ref* pSender)
{
    //摁下按钮，切换到说明书页面，由于说明书页面还没做，就等会吧~
    Director::getInstance()->replaceScene(StartMenuScene::createScene());
}

void SetScene::initVolumeSound()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto vosoButton = cocos2d::MenuItemImage::create("Button/VolumeSound.png", "Button/VolumeSound.png", CC_CALLBACK_1(SetScene::volumeSoundCallback, this));

    if (vosoButton == nullptr ||
        vosoButton->getContentSize().width <= 0 ||
        vosoButton->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + (visibleSize.width * 3) / 5 - vosoButton->getContentSize().width / 3;
        float y = origin.y + (visibleSize.height * 2) / 3;
        vosoButton->setScale(0.9f);
        vosoButton->setPosition(cocos2d::Vec2(x, y));
    }
    vosoButton_ = cocos2d::Menu::create(vosoButton, nullptr);
    this->addChild(vosoButton_, 1);
    vosoButton_->setPosition(cocos2d::Vec2::ZERO);
}

void SetScene::volumeSoundCallback(Ref* pSender)
{
    //摁下按钮，考虑不切换新界面，而是出现一个可以移动的条子，然后也可以关掉
    Director::getInstance()->replaceScene(StartMenuScene::createScene());
}

void SetScene::initReturnMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto returnButton = cocos2d::MenuItemImage::create("Button/Return.png", "Button/Return.png", CC_CALLBACK_1(SetScene::menuReturnCallback, this));

    if (returnButton == nullptr ||
        returnButton->getContentSize().width <= 0 ||
        returnButton->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + (visibleSize.width * 4) / 5 - returnButton->getContentSize().width/3;
        float y = origin.y + (visibleSize.height * 2) / 3;
        returnButton->setScale(0.9f);
        returnButton->setPosition(cocos2d::Vec2(x, y));
    }
    returnButton_ = cocos2d::Menu::create(returnButton, nullptr);
    this->addChild(returnButton_, 1);
    returnButton_->setPosition(cocos2d::Vec2::ZERO);
}

void SetScene::menuReturnCallback(Ref* pSender)
{
    //摁下返回按钮，切换到menu页面
    Director::getInstance()->replaceScene(StartMenuScene::createScene());
}
