/**
*@file StartScene.cpp
* @author wyf
*/
#include "StartScene.h"
#include "StartLoginScene.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //to zyy 进入时加入音效，就是那种进游戏dang一下，显得比较高级一点
    initTermLabel();//Animation of entrance

    scheduleOnce(SEL_SCHEDULE(&StartScene::ChangeScene), 1.0f);//switch scene
    
    //由于游戏资源还蛮多的，所以在考虑要不要提前预加载一下，时间够就预加载
    //到时候这里可以加个进度条伪装一下
    return true;
}

void StartScene::initTermLabel()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //The entry animation shows the name of our group
    auto label = Label::createWithTTF("COOL\nWZW\nTERM", "fonts/Marker Felt.ttf", 60);

    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2 + label->getContentSize().height / 2));

        this->addChild(label, 0);
    }
   
    //and some weird hints
}

//switch to loginScene
void StartScene::ChangeScene(float dt)
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, StartLoginScene::createScene()));
}