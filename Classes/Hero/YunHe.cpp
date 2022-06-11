#include "YunHe.h"
#include "Consts.h"

YunHe* YunHe::createPlayer()
{
    auto player = new(std::nothrow) YunHe;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = YunHeHealthInit;//当前生命

    player->healthInit_ = YunHeHealthInit;//最大生命

    player->attack_ = YunHeAttack;//攻击值

    player->defend_ = YunHeDefend;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/YunHe.png");

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

Hero* YunHe::createAI()
{
    auto player = new(std::nothrow) YunHe;

    if (!player)
    {
        return nullptr;
    }

    player->health_ = YunHeHealthInit;//当前生命

    player->healthInit_ = YunHeHealthInit;//最大生命

    player->attack_ = YunHeAttack;//攻击值

    player->defend_ = YunHeDefend;//防御值

    auto chosenHero = Sprite::create("Hero/FightHero/YunHe.png");

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

void YunHe::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/YunHe-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    auto physicsBody = PhysicsBody::createBox(useSkill->getContentSize(), PhysicsMaterial(0.f, 0.f, 0.f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(PlayerBulletAndEnemyBitmask);// bitmask是碰撞的body种类 这一句是设置种类
    physicsBody->setContactTestBitmask(PlayerBulletAndEnemyBitmask);// 这一句是在这个种类碰撞的时候通知
    useSkill->setPhysicsBody(physicsBody);
    useSkill->setTag(YunHeUtimateSkillTag);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// 大招释放完毕confirm_复原
}