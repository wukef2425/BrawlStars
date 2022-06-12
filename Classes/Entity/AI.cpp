#include "Entity/AI.h"
#include "Consts.h"

Hero* AI::create(const std::string& filename)
{
    auto player = new(std::nothrow) Hero;

    if (!player)
    {
        return nullptr;
    }

    auto chosenHero = Sprite::create(filename);

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