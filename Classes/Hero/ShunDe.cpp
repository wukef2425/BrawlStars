#include "ShunDe.h"
#include "Consts.h"

ShunDe* ShunDe::createPlayer()
{
    auto player = new(std::nothrow) ShunDe;

    if (!player)
    {
        return nullptr;
    }
    player->dieTag_ = PlayerDieTag;

    player->health_ = ShunDeHealthInit;//当前生命

    player->healthInit_ = ShunDeHealthInit;//最大生命

    player->attack_ = ShunDeAttack;//攻击值

    player->defend_ = ShunDeDefend;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/ShunDe.png");

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

Hero* ShunDe::createAI()
{
    auto player = new(std::nothrow) ShunDe;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = ShunDeHealthInit;//当前生命

    player->healthInit_ = ShunDeHealthInit;//最大生命

    player->attack_ = ShunDeAttack;//攻击值

    player->defend_ = ShunDeDefend;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/ShunDe.png");

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

void ShunDe::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/ShunDe-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    Hero::bindPhysicsBodyAndTag(useSkill, PlayerBulletAndEnemyBitmask, ShunDeUtimateSkillTag);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// 大招释放完毕confirm_复原
}