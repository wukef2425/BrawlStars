/**
* @file PolarBear.cpp
* @author wukef
*/

#include "PolarBear.h"
#include "Consts.h"

PolarBear* PolarBear::createPlayer()
{
    auto player = new(std::nothrow) PolarBear;

    if (player == nullptr)
    {
        return nullptr;
    }

    player->isAlive_ = true;//是否存活

    player->health_ = 100;//当前生命

    player->bullet_ = 3;//当前弹药

    player->maxHealth_ = 100;//最大生命

    player->attack_ = 35;//攻击值

    player->defend_ = 10;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/polar-bear.png");

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

Hero* PolarBear::createAI()
{
    auto AI = new(std::nothrow) PolarBear;

    if (AI == nullptr)
    {
        return nullptr;
    }

    AI->isAlive_ = true;//是否存活

    AI->health_ = 100;//当前生命

    AI->bullet_ = 3;//当前弹药

    AI->maxHealth_ = 100;//最大生命

    AI->attack_ = 35;//攻击值

    AI->defend_ =10;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/polar-bear.png");

    if (chosenHero)
    {
        AI->setPosition(0, 0);

        AI->bindPhysicsBodyAndTag(chosenHero, PlayerBulletAndEnemyBitmask, EnemyTag);

        AI->addChild(chosenHero);

        AI->autorelease();

        return AI;
    }

    return nullptr;
}