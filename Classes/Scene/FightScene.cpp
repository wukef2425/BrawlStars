/**
* @file FightScene.cpp
* @author wukef & wyf
*/

/*Fight界面主要要加载的内容有
1.UI部件，包括游戏时间/人物血量及蓝/生存人数/雾/雾的警告，他们是动态可变化的
2.监听器，通过鼠标/键盘/触摸检测来对人物动作进行改变
3.每一个元素所在的层：地图 0；障碍物、武器 1；设置层 5；结束层
4.分界线，就是外围的两个格子

*/

#include "FightScene.h"

USING_NS_CC;

Scene* FightScene::createScene()
{
    return FightScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool FightScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
   //不知道为什么加入tmx的时候老是加载错误，太气人了
	//auto* SnowMap = TMXTiledMap::create("Map/SnowMap.tmx");
	//addChild(SnowMap, 0);

    auto winSize = Director::getInstance()->getVisibleSize();

    auto origin = Director::getInstance()->getVisibleOrigin();

    auto background = DrawNode::create();

    /* 目前先放一个纯色背景，四个float参数调一调可以换颜色 */
    background->drawSolidRect(origin, winSize, cocos2d::Color4F(0.6f, 0.6f, 0.6f, 1.0f));

    this->addChild(background);

    listenToUserOperation("Hero/polar-bear.png");

    return true;
}

void FightScene::listenToUserOperation(const std::string& filename)
{
    currentPlayer = Player::create(filename);

    this->addChild(currentPlayer);// 好像要先加到player里再加到scene里？？？

    currentPlayer->scheduleUpdate();// 用来schedule update

    /* 监听键盘WASD实现移动 */
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();

    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::listenToKeyPresses, currentPlayer);

    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::listenToKeyReleases, currentPlayer);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    /* 监听鼠标 实现点击攻击 */
    auto eventListener = cocos2d::EventListenerTouchOneByOne::create();

    eventListener->onTouchBegan = CC_CALLBACK_2(FightScene::onTouchBegan, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

bool FightScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unusedEvent)
{
    Vec2 touchLocation = touch->getLocation();

    Vec2 offset = touchLocation - currentPlayer->getPosition();

    auto bullet = Sprite::create("Hero/Bullet/polar-bear-bullet.png");

    bullet->setPosition(currentPlayer->getPosition());

    this->addChild(bullet);

    offset.normalize();

    auto aid = offset * 1000;// 改动这个可以改子弹发射速率，后期可以不同的英雄不一样

    auto shootRange = aid + bullet->getPosition();

    auto actionMove = MoveTo::create(2.0f, shootRange);// 两秒到达目的地，也可以通过这个改速率

    auto actionRemove = RemoveSelf::create();

    bullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));

    return true;
}