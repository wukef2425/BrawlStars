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
#include "Scene/GameOverScene.h"
#include "Hero/EnergyBox.h"

USING_NS_CC;


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/* 预先加载地图函数 */
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

    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    initMap();//初始化地图

    initHero();//初始化英雄

    initAI();//初始化AI

    initUI();// 加入ui组件

    gamePause();

    initSmoke();

    listenToUserOperation();

    setCamera();

    this->scheduleUpdate();

    return true;
}

/* 需要添加的信息有：镜头的跟随、人物的移动、草坪的状态、人物移动要注意是否有障碍物 */
void FightScene::update(float dt)
{
    //更新玩家的位置
    Vec2 playerPosition = currentPlayer->getPosition();
    this->setPlayerPosition(playerPosition);

    this->grassCover(playerPosition);//草丛的变化也应该加到这里,但目前有点bug先注释掉

    updateCharacterUI(AI);

    updateCharacterUI(currentPlayer);

    if (true == energyBox->isAlive())
    {
        energyBox->update_hp();
    }

    HeroCount();//记录英雄人数

    smokeHurt(currentPlayer->getPosition());
}

void FightScene::updateCharacterUI(Hero* hero)
{
    if (true == hero->isAlive())
    {
        hero->update_hp();
        hero->update_sp();
        hero->update_mp();
        hero->recoverHealth();
        hero->recoverBullet();
    }
}

/*****************************人物移动**************************************************/
// OpenGL坐标转成瓦片地图坐标
Vec2 FightScene::tilePosition(const Vec2& position)
{ 
    Size mapSize = _tileMap->getMapSize();      // 获取以tiles数量为单位的地图尺寸
    Size tileSize = _tileMap->getTileSize();    // 获取以像素点为单位的tile尺寸属性
    int x = position.x / tileSize.width;
    int y = (mapSize.height * tileSize.height - position.y) / tileSize.height;

    return Vec2(x + 32, y - 32);//校准坐标
}

void FightScene::setPlayerPosition(Vec2 position)
{
    Point tileCoord = this->tilePosition(position);
    
    //边界范围限制
    if (!(tileCoord.x < 64 && tileCoord.y < 64 && tileCoord.x > 0 && tileCoord.y > 0))
    {
        this->currentPlayer->ChangePosition(false);
        return;
    }
    //barrier限制
    if (_collidable->getTileAt(tileCoord))
    {
        this->currentPlayer->ChangePosition(false);
        return;
    }

    this->currentPlayer->ChangePosition(true);

}

/*****************************************战斗所需函数************************************************/
void FightScene::listenToUserOperation()
{
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
    float bulletRemain = currentPlayer->currentBullet();

    /* touch转世界坐标 */
    cocos2d::Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 touchWorldPosition = touch->getLocation() + currentPlayer->getPosition() - Vec2(winSize.width * 0.5f, winSize.height * 0.5f);


    if (0 < bulletRemain && false == currentPlayer->isReleaseConfirmed())
    {
        /* 创造currentBullet并设置初始位置 */
        auto currentBullet = Sprite::create("Hero/Bullet/polar-bear-bullet.png");// 因为子弹是打一个删一个的，所以只能放在onTouchBegan内部
        currentBullet->setPosition(this->currentPlayer->getPosition());// 初始位置是从currentPlayer出发

        /* 给currentBullet绑定物理躯干 */
        bindPhysicsBodyAndTag(currentBullet, PlayerBulletAndEnemyBitmask, PlayerBulletTag);

        /* 加入渲染树 */
        this->addChild(currentBullet);

        Vec2 offset = touchWorldPosition - this->currentPlayer->getPosition();
        offset.normalize();// currentPlayer位置指向鼠标touch位置的单位向量

        /* 定义一些动作 */
        auto actionMove = MoveBy::create(1.5f, offset * ShootSpeed);// 1.5秒到达目的地
        auto actionRemove = RemoveSelf::create();// 删掉自身

        /* 让currentBullet完成上面的一系列动作 */
        currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));
    }
    else if (0 < bulletRemain && true == currentPlayer->isReleaseConfirmed())
    {
        currentPlayer->ultimateSkill(touchWorldPosition);
    }
    else if (0 >= bulletRemain)
    {
        auto noBullet = Sprite::create("Hero/Bullet/nobullet.png");
        noBullet->setPosition(touchWorldPosition);
        this->addChild(noBullet);
        auto scaleTo = ScaleTo::create(0.5f, 1.5f, 1.5f);
        auto actionRemove = RemoveSelf::create();
        noBullet->runAction(Sequence::create(scaleTo, actionRemove, nullptr));
    }

    unusedEvent->stopPropagation();// 执行了以上任意一个分支后，停止事件传播，避免按下去抬起来执行两次

    return false;// 不把事件向下层分发
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
        //auto currentBox = dynamic_cast<Hero*>(energyBox1);
        /* player打AI */
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
        /* player打box */
        else if (nodeA->getTag() == PlayerBulletTag && nodeB->getTag() == EnergyBoxTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeA);
            energyBox->receiveDamage(currentPlayer->dealDamage(), energyBox, currentHero);
        }
        else if (nodeB->getTag() == PlayerBulletTag && nodeA->getTag() == EnergyBoxTag)
        {
            showSpark("Hero/Bullet/spiky-eclipse.png", nodeB);
            energyBox->receiveDamage(currentPlayer->dealDamage(), energyBox, currentHero);
        }
        /* AI打player */
        else if (nodeA->getTag() == EnemyBulletTag && nodeB->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeA);
            currentPlayer->receiveDamage(AI->dealDamage(), currentHero, AI);
        }
        else if (nodeB->getTag() == EnemyBulletTag && nodeA->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/enemy-spiky-eclipse.png", nodeB);
            currentPlayer->receiveDamage(AI->dealDamage(), currentHero, AI);
        }
        /* YunHe大招 */
        else if (nodeA->getTag() == YunHeUtimateSkillTag && nodeB->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/YunHe-bullet.png", nodeA);
            AI->receiveDamage(currentPlayer->dealDamage() * 2, AI, currentHero);// YunHe大招直接造成两倍攻击的伤害
        }
        else if (nodeB->getTag() == YunHeUtimateSkillTag && nodeA->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/YunHe-bullet.png", nodeB);
            AI->receiveDamage(currentPlayer->dealDamage() * 2, AI, currentHero);// YunHe大招直接造成两倍攻击的伤害
        }
        /* ChangYi大招 */
        else if (nodeA->getTag() == ChangYiUtimateSkillTag && nodeB->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/ChangYi-bullet.png", nodeA);
            currentPlayer->recoverHealth(currentHero, 50.f);// ChangYi大招为友方恢复50点生命
        }
        else if (nodeB->getTag() == ChangYiUtimateSkillTag && nodeA->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/ChangYi-bullet.png", nodeB);
            currentPlayer->recoverHealth(currentHero, 50.f);// ChangYi大招为友方恢复50点生命
        }
        /* SanYue大招 */
        else if (nodeA->getTag() == SanYueUtimateSkillTag && nodeB->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/SanYue-bullet.png", nodeA);
            currentPlayer->recoverHealth(currentHero, 30.f);// SanYue大招为友方恢复30点生命
        }
        else if (nodeB->getTag() == SanYueUtimateSkillTag && nodeA->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/SanYue-bullet.png", nodeB);
            currentPlayer->recoverHealth(currentHero, 30.f);// SanYue大招为友方恢复30点生命
        }
        else if (nodeA->getTag() == SanYueUtimateSkillTag && nodeB->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/SanYue-bullet.png", nodeA);
            AI->receiveDamage(20.f, AI, currentHero);// 或者对敌方直接造成20点伤害
        }
        else if (nodeB->getTag() == SanYueUtimateSkillTag && nodeA->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/SanYue-bullet.png", nodeB);
            AI->receiveDamage(20.f, AI, currentHero);// 或者对敌方造成20点伤害
        }
        /* HaoQing大招 */
        else if (nodeA->getTag() == HaoQingUtimateSkillTag && nodeB->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/HaoQing-bullet.png", nodeA);
            currentPlayer->recoverBulletAndUpgrade(currentHero,1.f,20.f);// 升级充能50%概率加1.f的攻击，大招充能20%
        }
        else if (nodeB->getTag() == HaoQingUtimateSkillTag && nodeA->getTag() == PlayerTag)
        {
            showSpark("Hero/Bullet/HaoQing-bullet.png", nodeB);
            currentPlayer->recoverBulletAndUpgrade(currentHero, 5.f, 1.f);// 升级充能50%概率加5.f的攻击，大招充能1%
        }
        /* ShunDe大招 */
        else if (nodeA->getTag() == ShunDeUtimateSkillTag && nodeB->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/ShunDe-bullet.png", nodeA);
            AI->receiveDamage(15.f, AI, currentHero);// ShunDe大招为对敌方直接造成15点伤害
            currentPlayer->recoverHealth(currentHero, 15.f);// 同时吸血
        }
        else if (nodeB->getTag() == ShunDeUtimateSkillTag && nodeA->getTag() == EnemyTag)
        {
            showSpark("Hero/Bullet/ShunDe-bullet.png", nodeB);
            AI->receiveDamage(15.f, AI, currentHero);// ShunDe大招为对敌方直接造成15点伤害
            currentPlayer->recoverHealth(currentHero, 15.f);// 同时吸血
        }
    }

    return true;

}

void FightScene::showSpark(const std::string& filename, cocos2d::Node*& node)// 创造图片为filename的火花，删除节点node
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

    this->addChild(_tileMap, 0);//map是已经预加载好的

    //分属性添加内容

    _background = _tileMap->getLayer("Basic");//基础背景

    _barrier = _tileMap->getLayer("Barrier");//障碍物,考虑砖块与小河是否要分开，因为砖块可摧毁

    _collidable = _tileMap->getLayer("Collision");//碰撞图层
    _collidable->setVisible(false);

    _grass = _tileMap->getLayer("Grass");//草丛

    energyBox = EnergyBox::createBox(Vec2(100, 100));//添加宝箱
    this->addChild(energyBox);
}
//绑定指定人物
void FightScene::initHero()
{
    //通过选择的人物来调用不同的createPlayer函数进行
    int chooseHeroNumber = GameData::getChooseHero();
    switch (chooseHeroNumber)
    {
    case ChangYiNumber:
        this->currentPlayer = ChangYi::createPlayer();
        break;

    case YunHeNumber:
        this->currentPlayer = YunHe::createPlayer();
        break;

    case HaoQingNumber:
        this->currentPlayer = HaoQing::createPlayer();
        break;

    case SanYueNumber:
        this->currentPlayer = SanYue::createPlayer();
        break;

    case ShunDeNumber:
        this->currentPlayer = ShunDe::createPlayer();
        break;

    default:
        break;
    }

    this->addChild(this->currentPlayer);
}

void FightScene::initAI()
{
    AI = PolarBear::createAI();



    this->addChild(AI);

    this->schedule(CC_SCHEDULE_SELECTOR(FightScene::createAI), AIShootCycle);// AIShootCycle秒执行一次schedule AI会AIShootCycle秒更新一次目的地，追着你跑
}

void FightScene::initUI()
{
    currentPlayer->initHpSlider();
    currentPlayer->initMpSlider();
    currentPlayer->initSpSlider();

    AI->initHpSlider();
    AI->initMpSlider();
    AI->initSpSlider();

    energyBox->initHpSlider();
}

/***********************************瓦片地图初始化（毒烟、草坪、障碍物）**********************************************/
void FightScene::initSmoke()
{

    _smoke = _tileMap->getLayer("Smoke");//毒烟
    _xSmokeMin = 0,
        _xSmokeMax = _tileMap->getMapSize().width,
        _ySmokeMin = 0,
        _ySmokeMax = _tileMap->getMapSize().height;
    this->smokeMove();

    for (int X = _xSmokeMin; X < _xSmokeMax; X++)
    {
        for (int Y = _ySmokeMin; Y < _ySmokeMax; Y++)
        {
            if (_smoke->getTileAt(Vec2(X, Y))) 
            {
                _smokeCell = _smoke->getTileAt(Vec2(X, Y));
                _smokeCell->setVisible(false);
            }
        }
    }

    this->schedule([=](float dt) {				
        smokeMove();
        }, SmokeSpeed, "smoke move");

}
//毒烟的移动
void FightScene::smokeMove()
{
    for (int X = _xSmokeMin; X < _xSmokeMax; X++)
    {
        if (_smoke->getTileAt(Vec2(X, _ySmokeMin)))
        {
            _smokeCell = _smoke->getTileAt(Vec2(X, _ySmokeMin));
            _smokeCell->setVisible(true);
        }
        if (_smoke->getTileAt(Vec2(X, _ySmokeMax - 1)))
        {
            _smokeCell = _smoke->getTileAt(Vec2(X, _ySmokeMax - 1));
            _smokeCell->setVisible(true);
        }
    }
    for (int Y = _ySmokeMin; Y < _ySmokeMax; Y++)
    {
        if (_smoke->getTileAt(Vec2(_xSmokeMin, Y)))//如果通过tile坐标能够访问指定毒烟单元格
        {
            _smokeCell = _smoke->getTileAt(Vec2(_xSmokeMin, Y));
            _smokeCell->setVisible(true);
        }
        if (_smoke->getTileAt(Vec2(_xSmokeMax - 1, Y)))
        {
            _smokeCell = _smoke->getTileAt(Vec2(_xSmokeMax - 1, Y));
            _smokeCell->setVisible(true);
        }
    }

    _xSmokeMin++;
    _xSmokeMax--;
    _ySmokeMin++;
    _ySmokeMax--;


}
//毒烟的伤害
void FightScene::smokeHurt(Vec2 position)
{
    Vec2 _tileCoord = this->tilePosition(position); //转化为瓦片地图坐标
    if (_smoke->getTileAt(_tileCoord))
    {
        _smokeCell = _smoke->getTileAt(_tileCoord);
        if (_smokeCell->isVisible()) //如果毒烟可见
        {
            auto currentHero = dynamic_cast<Hero*>(currentPlayer);
            currentPlayer->receiveDamage(SmokeDamage, currentHero);
            AI->receiveDamage(SmokeDamage, AI);
        }
    }
}
void FightScene::grassCover(Vec2 position)
{
    static vector<Vec2> grassChange = {};

    int i;
    for (i = 0; i < grassChange.size(); i++)
    {
        Point tileCoord = this->tilePosition(grassChange[i]);
        if (_grass->getTileAt(tileCoord))
        {
            _grassCell = _grass->getTileAt(tileCoord);
            _grassCell->setOpacity(255);
        }
    }

    Vec2 tileSize = _tileMap->getTileSize(); //获得单个瓦片尺寸
    position.x = position.x - tileSize.x;
    //将玩家及其周围所在草丛变透明
    grassChange =
    {
        position,
        Vec2(position.x + tileSize.x, position.y),
        Vec2(position.x - tileSize.x, position.y),
        Vec2(position.x, position.y + tileSize.y),
        Vec2(position.x, position.y - tileSize.y)
    };

    for (i = 0; i < grassChange.size(); i++)
    {
        Vec2 tileCoord = this->tilePosition(grassChange[i]);
        Vec2 hero_tileCoord = this->tilePosition(grassChange[1]);
        if (_grass->getTileAt(tileCoord) && _grass->getTileAt(hero_tileCoord))
        {
            _grassCell = _grass->getTileAt(tileCoord);
            _grassCell->setOpacity(100);
        }
    }

}
/***********************************ui组件初始化（剩余人数、时间）**********************************************/

void FightScene::HeroCount()//计分板
{
    //给计分板加个框框
    auto* scoreBoard = Sprite::create("Scene/ScoreBoard.png");
    scoreBoard->setAnchorPoint(Vec2(0, 1));
    scoreBoard->setScale(0.8f);
    scoreBoard->setPosition(Vec2(_origin.x, _visibleSize.height + _origin.y));
    this->addChild(scoreBoard);
    scoreBoard->setCameraMask(2, true);
    //分数
    heroNumber = Label::createWithTTF(StringUtils::format("Brawler Left: %d", GameData::getRemainingPlayer()).c_str(), "fonts/arial.ttf", 40);
    heroNumber->setAnchorPoint(Vec2(0, 1));
    heroNumber->setPosition(Vec2(_origin.x + (heroNumber->getContentSize().width / 5), _visibleSize.height + _origin.y - (heroNumber->getContentSize().height)));

    this->addChild(heroNumber);
    heroNumber->setCameraMask(2, true);
}
//游戏暂停
void FightScene::gamePause()
{
    //初始化gamepause的按钮，当点击的时候，执行转换函数，注意场景应该是pop
    //注意时间的暂停！！！
    auto pauseItem = cocos2d::MenuItemImage::create(
        "Button/PauseNormal.png",
        "Button/PauseSelected.png",
        CC_CALLBACK_1(FightScene::GamePauseCallback, this));

    pauseItem->setPosition(Vec2(_visibleSize.width - pauseItem->getContentSize().width / 2,
        _visibleSize.height - pauseItem->getContentSize().height / 2));

    pauseButton_ = cocos2d::Menu::create(pauseItem, nullptr);
    pauseButton_->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(pauseButton_, 2);
    pauseButton_->setCameraMask(2, true);

}

void FightScene::GamePauseCallback(Ref* pSender)
{

    Director::getInstance()->pushScene(Gamepause::scene());
}

/*****************************游戏状态记录，人物是否死亡、游戏是否结束**********************************************/

void FightScene::setCamera()
{
    this->fightCamera = CameraEffect::create(this);
    if (this->fightCamera != nullptr && this->currentPlayer != nullptr)
    {
        this->fightCamera->FollowPlayer(currentPlayer);
    }
}

void FightScene::GameOver(Hero* hero)
{

    if (GameData::getRemainingPlayer() == 1 || (!hero->isAlive() && hero->getDieTag() == PlayerDieTag))
    {
        //本来想高级点，但是静态成员函数里不能用取消计时器，所以就算了
        Director::getInstance()->replaceScene(GameOverScene::createScene());//转到结算界面
    }
}

