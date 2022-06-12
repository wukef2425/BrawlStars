/**
*@file StartLoginScene.cpp
* @author wyf
*/
#include "StartLoginScene.h"
#include "StartMenuScene.h"
#include "AudioEngine.h"
USING_NS_CC;

Scene* StartLoginScene::createScene()
{
    return StartLoginScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartLoginScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto* background = Sprite::create("Scene/MyLoginScene.jpg");        //创建精灵类，背景图片为background.jpg
    background->setScale(1.05f);
    background->setPosition(visibleSize.width / 2, visibleSize.height / 2);        //让背景图像居中显示
    addChild(background, 0);

    auto* agetip = Sprite::create("AgeTip.jpg");        //agetip
    agetip->setScale(0.7f);
    if (agetip == nullptr)
    {
        problemLoading("'AgeTip.jpg'");
    }
    else
    {
        agetip->setPosition(visibleSize.width - (agetip->getContentSize().width*2)/3, visibleSize.height - (agetip->getContentSize().height * 2) / 3);        //让适龄提示在右上角
        addChild(agetip, 1);
    }
    
    auto* gamelogo = Sprite::create("GameLogo.png");        //logo
    
    if (gamelogo == nullptr)
    {
        problemLoading("'GameLogo.png'");
    }
    else
    {
        gamelogo->setPosition((2 * gamelogo->getContentSize().width) / 3, visibleSize.height - (2*gamelogo->getContentSize().height) / 3);        //让游戏logo在左上角
        addChild(gamelogo, 2);
    }

    //loginitem
    auto LoginItem = MenuItemImage::create(
        "Login.png",
        "Login.png",
        CC_CALLBACK_1(StartLoginScene::menuCloseCallback, this));
    LoginItem->setScale(0.6f);
    if (LoginItem == nullptr ||
        LoginItem->getContentSize().width <= 0 ||
        LoginItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/2 ;
        float y = origin.y + visibleSize.height/5;
        LoginItem->setPosition(Vec2(x, y));
    }

    BGMOn();

    auto menu = Menu::create(LoginItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void StartLoginScene::BGMOn()
{
    BGM_ID = AudioEngine::play2d("BGM.mp3", true, 0.5f);
}

void StartLoginScene::BGMOff()
{
    AudioEngine::pause(BGM_ID);
}

void StartLoginScene::BGMContinue()
{
    AudioEngine::preload("BGM.mp3");
    AudioEngine::resume(BGM_ID);
}


void StartLoginScene::menuCloseCallback(Ref* pSender)
{
    //switch to menu
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, StartMenuScene::createScene()));

}