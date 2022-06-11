#include "EnergyBox.h"
#include "Consts.h"

Hero* EnergyBox::createBox(Vec2 position)
{
    auto player = new(std::nothrow) EnergyBox;

    if (!player)
    {
        return nullptr;
    }

    player->dieTag_ = EnergyBoxDieTag;

    player->health_ = EnergyBoxHealthInit;//当前生命

    player->healthInit_ = EnergyBoxHealthInit;//最大生命

    player->defend_ = EnergyBoxDefend;//防御值

    auto chosenHero = Sprite::create("Hero/energy-box.png");

    if (chosenHero)
    {
        player->setPosition(position);

        player->bindPhysicsBodyAndTag(chosenHero, PlayerBulletAndEnemyBitmask, EnemyTag);

        player->addChild(chosenHero);

        player->autorelease();

        return player;
    }

    return nullptr;
}