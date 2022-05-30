/**
*@file StartScene.cpp
* @author wyf
*/
#include "StartScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
   
    if (!Scene::init())
    {
        return false;
    }
    
    initTermLabel();
 
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
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2 + label->getContentSize().height / 2));

        // add the label as a child to this layer
        this->addChild(label, 0);
    }

    
}
