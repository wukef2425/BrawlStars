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

    player->health_ = 100;//当前生命

    player->healthInit_ = 100;//最大生命

    player->attack_ = 25;//攻击值

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
    auto player = new(std::nothrow) PolarBear;

    if (player == nullptr)
    {
        return nullptr;
    }

    player->health_ = 100;//当前生命

    player->healthInit_ = 100;//最大生命

    player->attack_ = 20;//攻击值

    player->defend_ = 10;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/polar-bear.png");

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