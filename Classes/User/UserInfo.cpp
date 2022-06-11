/**
*@file SetScene.cpp
* @author wyf
*/
/*页面要实现的内容：
查看用户的昵称头像并可以更改
查看用户目前的奖杯数（必须）
查看经验值和等级
查看胜场数
返回主页面（必须）
*/
#include "UserInfo.h"
#include "Scene/StartMenuScene.h"

USING_NS_CC;

Scene* UserInfo::createScene()
{
    return UserInfo::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool UserInfo::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //记得先设一个背景图片，好统筹的，其实可以花到一起，包括文字啥的，就是考验艺术家王的设计能力，但记得不要遮挡
    //这三个按钮的位置并没有好好放，记得改一下，并且设置可以在里面添加新功能
    initDecoration();//一些让画面美观的东西

    initReturnMenu();
    return true;
}

void UserInfo::initDecoration()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //设置背景图片
    auto* setScene = Sprite::create("Scene/SetScene.jpg");        //设置类背景图
    setScene->setScale(0.8f);
    setScene->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //让背景图像居中显示
    addChild(setScene, 0);
    
}

void UserInfo::initReturnMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto returnButton = cocos2d::MenuItemImage::create("Button/Return.png", "Button/Return.png", CC_CALLBACK_1(UserInfo::menuReturnCallback, this));

    if (returnButton == nullptr ||
        returnButton->getContentSize().width <= 0 ||
        returnButton->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + (visibleSize.width * 4) / 5 - returnButton->getContentSize().width / 3;
        float y = origin.y + (visibleSize.height * 2) / 3;
        returnButton->setScale(0.9f);
        returnButton->setPosition(cocos2d::Vec2(x, y));
    }
    returnButton_ = cocos2d::Menu::create(returnButton, nullptr);
    this->addChild(returnButton_, 1);
    returnButton_->setPosition(cocos2d::Vec2::ZERO);
}

void UserInfo::menuReturnCallback(Ref* pSender)
{
    //摁下返回按钮，切换到menu页面
    Director::getInstance()->replaceScene(StartMenuScene::createScene());
}