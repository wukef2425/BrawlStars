/**
* @file PolarBear.cpp
* @author wukef
*/

#include "PolarBear.h"
#include "Consts.h"

PolarBear* PolarBear::createPlayer()
{
    auto player = new(std::nothrow) PolarBear;

    if (!player)
    {
        return nullptr;
    }

    player->isAlive_ = true;//是否存活

    player->health_ = 100;//当前生命

    player->bullet_ = 3;//当前弹药

    player->maxHealth_ = 100;//最大生命

    player->attack_ = 35;//攻击值

    player->defend_ = 10;//防御值

    player->energy_ = 1;//死了以后掉落多少能量

    auto chosenHero = Sprite::create("Hero/polar-bear.png");

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

    if (!player)
    {
        return nullptr;
    }

    player->isAlive_ = true;//是否存活

    player->health_ = 100;//当前生命

    player->bullet_ = 3;//当前弹药

    player->maxHealth_ = 100;//最大生命

    player->attack_ = 35;//攻击值

    player->defend_ = 0;//防御值

    player->energy_ = 1;//死了以后掉落多少能量

    auto chosenHero = Sprite::create("Hero/polar-bear.png");

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