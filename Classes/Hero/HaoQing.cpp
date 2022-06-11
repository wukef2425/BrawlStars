#include "HaoQing.h"
#include "Consts.h"

HaoQing* HaoQing::createPlayer()
{
    auto player = new(std::nothrow) HaoQing;

    if (!player)
    {
        return nullptr;
    }
    player->dieTag_ = PlayerDieTag;

    player->health_ = HaoQingHealthInit;//当前生命

    player->healthInit_ = HaoQingHealthInit;//最大生命

    player->attack_ = HaoQingAttack;//攻击值

    player->defend_ = HaoQingDefend;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/HaoQing.png");

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

Hero* HaoQing::createAI()
{
    auto player = new(std::nothrow) HaoQing;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = HaoQingHealthInit;//当前生命

    player->healthInit_ = HaoQingHealthInit;//最大生命

    player->attack_ = HaoQingAttack;//攻击值

    player->defend_ = HaoQingDefend;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/HaoQing.png");

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

void HaoQing::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/HaoQing-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// 大招释放完毕confirm_复原
}