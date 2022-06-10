#include "ChangYi.h"
#include "Consts.h"

/*人物中要包括的基础内容有，人物的攻击方式，人物的各种属性，人物的大招*/
ChangYi* ChangYi::createPlayer()
{
    auto player = new(std::nothrow) ChangYi;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = 100;//当前生命

    player->healthInit_ = 100;//最大生命

    player->attack_ = 15;//攻击值

    player->defend_ = 10;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/ChangYi.png");

    if (chosenHero)
    {
        player->setPosition(player->x, player->y);// player初始坐标(x,y)根据窗口大小 在protected里面改

        player->bindPhysicsBodyAndTag(chosenHero, EnemyBulletAndPlayerBitmask, PlayerTag);

        player->addChild(chosenHero);

        player->autorelease();

        return player;
    }

    return nullptr;
}

Hero* ChangYi::createAI()
{
    auto player = new(std::nothrow) ChangYi;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = 100;//当前生命

    player->healthInit_ = 100;//最大生命

    player->attack_ = 15;//攻击值

    player->defend_ = 10;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/ChangYi.png");

    if (chosenHero)
    {
        player->setPosition(0, 0);

        player->bindPhysicsBodyAndTag(chosenHero, PlayerBulletAndEnemyBitmask, EnemyTag);

        player->addChild(chosenHero);

        player->autorelease();

        return player;
    }

    return nullptr;
}