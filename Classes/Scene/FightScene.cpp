/**
* @file FightScene.cpp
* @author wukef & wyf
*/


#include "cocos2d.h"
#include <vector>
#include <string>

#include "Consts.h"
#include "FightScene.h"
#include "Scene/ChooseHero.h"


USING_NS_CC;
using namespace std;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/* 预先加载地图函数, */
FightScene::FightScene(TMXTiledMap* map) : _tileMap(map)
{
    currentPlayer = nullptr;
};

FightScene* FightScene::create(TMXTiledMap* map)
{
    auto pRet = new(std::nothrow) FightScene(map);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
    return nullptr;
}

Scene* FightScene::createScene()
{
    auto scene = Scene::createWithPhysics();

    if (scene != nullptr)
    {
        scene->addChild(this, 0);
        scene->getPhysicsWorld()->setAutoStep(true);
        scene->getPhysicsWorld()->setGravity(cocos2d::Vec2::ZERO);
        scene->retain();
        return scene;
    }
    return nullptr;
}

/* 界面初始化函数 */
bool FightScene::init()
{

    if (!Scene::init()|| !Scene::initWithPhysics())
    {
        return false;
    }

    //to zyy 游戏加载的时候加入音乐组件

    initMap();//初始化地图

    //initUI(); 加入ui组件，包括剩余人数，蓝条血条，设置键（音乐和音效各种东西to zyy），暂停和退出按钮（不知道是不是ui）

    initHero();//初始化英雄

    initAI();//初始化AI

    listenToUserOperation();//监听用户操作，相当于一个战斗管控器，但感觉只要有监听就可以，这个可以放在战斗类里？？？

    setCamera();

    //this->schedule(CC_SCHEDULE_SELECTOR(FightScene::createAI), 0.5f);// 0.5秒执行一次schedule AI会0.5秒更新一次目的地，追着你跑

    this->scheduleUpdate();


    return true;
}

/* 需要添加的信息有：镜头的跟随、人物的移动、草坪的状态、人物移动要注意是否有障碍物 */
void FightScene::update(float dt)
{
    //this->setViewPointCenter(playerPos);//to wkf 设置镜头跟随可以加到这里
    // 
    // 
    // 
    // //人物移动的跟随应该放置在update中
    //更新玩家的位置
    //Vec2 playerPos = currentPlayer->getPosition();
    //this->setPlayerPosition(playerPos);//to wkf 就是在这里更改玩家的位置，先传到setplayerposition函数中进行判断，如果可以更改的话就setposition，不可以的话
                                       //就直接return达到无法移动的效果
    //考虑ai的移动是否也要加到这里，不过可能会不同步，需要调一下时间
                                       //this->setGrassOpacity(playerPos);//草丛的变化也应该加到这里
   
}

/*****************************************战斗所需函数************************************************/
void FightScene::listenToUserOperation()
{
    this->addChild(this->currentPlayer);// 好像要先加到player里再加到scene里？？？

    this->currentPlayer->scheduleUpdate();// 用来schedule update

    /* 监听键盘WASD实现移动 */
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::listenToKeyPresses, this->currentPlayer);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::listenToKeyReleases, this->currentPlayer);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    /* 监听鼠标 实现点击攻击 */
    auto eventListener = cocos2d::EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(FightScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

    /* 碰撞监听 */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(FightScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool FightScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unusedEvent)
{
    /* 创造currentBullet并设置初始位置 */
    auto currentBullet = Sprite::create("Hero/Bullet/polar-bear-bullet.png");// 因为子弹是打一个删一个的，所以只能放在onTouchBegan内部
    currentBullet->setPosition(this->currentPlayer->getPosition());// 初始位置是从currentPlayer出发

    /* 给currentBullet绑定物理躯干 */
    bindPhysicsBodyAndTag(currentBullet, PlayerBulletAndEnemyBitmask, PlayerBulletTag);

    /* 加入渲染树 */
    this->addChild(currentBullet);

    /* touch转世界坐标 */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 touchWorldPosition = touch->getLocation() + currentPlayer->getPosition() - Vec2(winSize.width * 0.5f, winSize.height * 0.5f);

    Vec2 offset = touchWorldPosition - this->currentPlayer->getPosition();
    offset.normalize();// currentPlayer位置指向鼠标touch位置的单位向量

    /* 定义一些动作 */
    auto actionMove = MoveBy::create(1.5f, offset * ShootSpeed);// 1.5秒到达目的地
    auto actionRemove = RemoveSelf::create();// 删掉自身

    /* 让currentBullet完成上面的一系列动作 */
    currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));

    return true;
}

bool FightScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    /* 获取两个碰撞的物体 */
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    /* 火花特效 & 删除标记为BulletTag的那个node(就是之前标记的currentBullet) */
    if (nodeA && nodeB)
    {
        auto currentHero = dynamic_cast<Hero*>(currentPlayer);
        if (nodeA->getTag() == PlayerBulletTag && nodeB->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeA);
            AI->receiveDamage(currentPlayer->dealDamage(), AI, currentHero);
        }
        else if (nodeB->getTag() == PlayerBulletTag && nodeA->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeB);
            AI->receiveDamage(currentPlayer->dealDamage(), AI, currentHero);
        }
        else if (nodeA->getTag() == EnemyBulletTag && nodeB->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeA);
        }
        else if (nodeB->getTag() == EnemyBulletTag && nodeA->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeB);
        }
        //else if (nodeA->getTag() == EnergyTag && nodeB->getTag() == PlayerTag)
        //{
            //nodeA->removeFromParentAndCleanup(true);
        //}
        //else if (nodeB->getTag() == EnergyTag && nodeA->getTag() == PlayerTag)
        //{
            //nodeB->removeFromParentAndCleanup(true);
        //}
    }

    return true;

}

void FightScene::showSpark(const std::string& filename, cocos2d::Node*& node)
{
    auto spark = Sprite::create(filename);
    spark->setPosition(node->getPosition());
    this->addChild(spark);
    auto scaleTo = ScaleTo::create(0.5f, 0.5f, 0.5f);
    auto actionRemove = RemoveSelf::create();
    spark->runAction(Sequence::create(scaleTo, actionRemove, nullptr));
    node->removeFromParentAndCleanup(true);
}

void FightScene::createAI(float delta)
{
    auto destination = this->currentPlayer->getPosition();
    auto actionMoveAI = MoveTo::create(1.5f, destination);// 1.5秒移动到目的地
    AI->runAction(actionMoveAI);

    Vec2 playerPosition = this->currentPlayer->getPosition();

    /* 创造currentBullet并设置初始位置 */
    auto currentBullet = Sprite::create("Hero/Bullet/enemy-bullet.png");
    currentBullet->setPosition(AI->getPosition());// 初始位置是从AI出发

    /* 给currentBullet绑定物理躯干 */
    bindPhysicsBodyAndTag(currentBullet, EnemyBulletAndPlayerBitmask, EnemyBulletTag);// 只管敌人子弹与玩家的接触

    /* 加入渲染树 */
    this->addChild(currentBullet);

    Vec2 offset = playerPosition - AI->getPosition();
    offset.normalize();// currentPlayer位置指向鼠标touch位置的单位向量

    /* 定义一些动作 */
    auto actionMove = MoveBy::create(2.0f, offset * ShootSpeed);// 2.0秒到达目的地
    auto actionRemove = RemoveSelf::create();// 删掉自身

    /* 让currentBullet完成上面的一系列动作 */
    currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}

void FightScene::bindPhysicsBodyAndTag(cocos2d::Sprite*& sprite, int bitmask, int tag)// 传引用，否则会被释放掉
{
    auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0.f, 0.f, 0.f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(bitmask);// bitmask是碰撞的body种类 这一句是设置种类
    physicsBody->setContactTestBitmask(bitmask);// 这一句是在这个种类碰撞的时候通知
    sprite->setPhysicsBody(physicsBody);
    sprite->setTag(tag);
}
/******************************************界面初始化*************************************************/
/*初始化地图，添加障碍物/草坪/毒烟/宝箱/人物及ai坐标*/
void FightScene::initMap()
{
    //添加地图,记得添加地图的选择
    //mapChoose界面，将选择的地图传入参数中
    
    this->addChild(_tileMap, 0);//map是已经预加载好的

    //分属性添加内容

    _background = _tileMap->getLayer("Basic");//基础背景

    _barrier = _tileMap->getLayer("Barrier");//障碍物,考虑砖块与小河是否要分开，因为砖块可摧毁

    _collidable = _tileMap->getLayer("Collision");//碰撞图层
    _collidable->setVisible(false);

    _grass = _tileMap->getLayer("Grass");//草丛

    _smoke = _tileMap->getLayer("Smoke");//毒烟
    _xSmokeMin = 0,
    _xSmokeMax = _tileMap->getMapSize().width,
    _ySmokeMin = 0,
    _ySmokeMax = _tileMap->getMapSize().height;
    this->smokeMove(SmokeSpeed);

    //毒烟的移动，一共会移动30次，每20秒移动一次，游戏一共6min
    //to wkf 不知道这个函数是什么个用法，要是有其它调用方式可以更改一下
    //this->schedule([=](float dt) {				//每20秒刷新
        //smokeMove();
        //}, SmokeSpeed, "smoke move");
    //this->schedule(CC_SCHEDULE_SELECTOR(FightScene::smokeMove), SmokeSpeed);// 还有个办法就是加float delta


}
/* 绑定指定人物 */
void FightScene::initHero()
{
    //通过选择的人物来调用不同的createPlayer函数进行
    switch (FightUtils::_hero)
    {
    case FightUtils::ChangYi:
        this->currentPlayer = ChangYi::createPlayer();
        break;
    case FightUtils::YunHe:
        this->currentPlayer = YunHe::createPlayer();
        break;
    case FightUtils::HaoQing:
        this->currentPlayer = HaoQing::createPlayer();
        break;
    case FightUtils::SanYue:
        this->currentPlayer = SanYue::createPlayer();
        break;
    case FightUtils::ShunDe:
        this->currentPlayer = ShunDe::createPlayer();
        break;
    default:
        break;
    }
}

void FightScene::initAI()
{
    AI = PolarBear::createAI();

    this->addChild(AI);

    this->schedule(CC_SCHEDULE_SELECTOR(FightScene::createAI), 0.5f);// 0.5秒执行一次schedule AI会0.5秒更新一次目的地，追着你跑
}

void FightScene::initUI()
{

}

/***********************************瓦片地图初始化（毒烟、草坪、障碍物）**********************************************/

// OpenGL坐标转成格子坐标
Vec2 FightScene::tileCoordFormPosition(const Vec2& position)
{
    Size mapSize = _tileMap->getMapSize();      // 获取以tiles数量为单位的地图尺寸
    Size tileSize = _tileMap->getTileSize();    // 获取以像素点为单位的tile尺寸属性
    
    int x = position.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - position.y) / tileSize.height;

    return Vec2(x, y);
}

void FightScene::setPlayerPosition(Point position)
{

    Point tileCoord = this->tileCoordFormPosition(position); 

    //边界范围限制
    if (!(tileCoord.x <=62 && tileCoord.y <=62 && tileCoord.x >= 3 && tileCoord.y >= 3))
    {
        return; 
    }
    //barrier限制
    if (_collidable->getTileAt(tileCoord))
    {
        return;
    }

    currentPlayer->setPosition(position);

}

//毒烟的移动
void FightScene::smokeMove(float delta)
{

    /* 全部显示毒烟 */
    for (int X = _xSmokeMin; X <_xSmokeMax; X++)
    {
        for (int Y = _ySmokeMin; Y < _ySmokeMax; Y++)
        {
            if (_smoke->getTileAt(Vec2(X, Y))) //如果通过tile坐标能够访问指定毒烟单元格
            {
                _smokeCell = _smoke->getTileAt(Vec2(X, Y));
                _smokeCell->setVisible(true);
            }
        }
    }
    /* 毒烟移动 */
    _xSmokeMin++;
    _xSmokeMax--;
    _ySmokeMin++;
    _ySmokeMax--;

    /* 中心不显示毒烟 */
    for (int X = _xSmokeMin; X <_xSmokeMax; X++)
    {
        for (int Y = _ySmokeMin; Y <_ySmokeMax; Y++)
        {
            if (_smoke->getTileAt(Vec2(X, Y))) //如果通过tile坐标能够访问指定毒烟单元格
            {
                _smokeCell = _smoke->getTileAt(Vec2(X, Y));
                _smokeCell->setVisible(false);
            }
        }
    }

    
}
//毒烟的伤害

/***********************************ui组件初始化（剩余人数、血量、蓝量）**********************************************/



/**********************************游戏状态记录，人物是否死亡、游戏是否结束*******************************************/

void FightScene::setCamera()
{
    this->fightCamera = CameraEffect::create(this);
    if (this->fightCamera != nullptr && this->currentPlayer != nullptr)
    {
        this->fightCamera->FollowPlayer(currentPlayer, _tileMap);
    }
}