#include "SanYue.h"
#include "Consts.h"

SanYue* SanYue::createPlayer()
{
    auto player = new(std::nothrow) SanYue;

    if (!player)
    {
        return nullptr;
    }
    player->dieTag_ = PlayerDieTag;

    player->health_ = SanYueHealthInit;//当前生命

    player->healthInit_ = SanYueHealthInit;//最大生命

    player->attack_ = SanYueAttack;//攻击值

    player->defend_ = SanYueDefend;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/SanYue.png");

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

Hero* SanYue::createAI()
{
    auto player = new(std::nothrow) SanYue;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = SanYueHealthInit;//当前生命

    player->healthInit_ = SanYueHealthInit;//最大生命

    player->attack_ = SanYueAttack;//攻击值

    player->defend_ = SanYueDefend;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/SanYue.png");

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

void SanYue::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/SanYue-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// 大招释放完毕confirm_复原
}