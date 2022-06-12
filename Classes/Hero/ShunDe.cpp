#include "ShunDe.h"
#include "Consts.h"
#include "Entity/AI.h"

Hero* ShunDe::createAI()
{
    auto player = AI::create("Hero/FightHero/ShunDe.png");

    player->health_ = ShunDeHealthInit;//当前生命

    player->healthInit_ = ShunDeHealthInit;//最大生命

    player->attack_ = ShunDeAttack;//攻击值

    player->defend_ = ShunDeDefend;//防御值

    return player;
}

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

void ShunDe::ultimateSkill(Vec2 touchWorldPosition)
{
    auto useSkill = Sprite::create("Hero/Bullet/ShunDe-bullet.png");

    useSkill->setPosition(touchWorldPosition);

    Hero::bindPhysicsBodyAndTag(useSkill, PlayerBulletAndEnemyBitmask, ShunDeUtimateSkillTag);

    this->getParent()->addChild(useSkill);

    this->confirm_ = false;// 大招释放完毕confirm_复原
}

void ShunDe::attackHero(Vec2 playerPosition, Vec2 touchWorldPosition)
{
    /* 创造currentBullet并设置初始位置 */
    auto currentBullet = Sprite::create("Hero/Bullet/polar-bear-bullet.png");// 因为子弹是打一个删一个的，所以只能放在onTouchBegan内部
    currentBullet->setPosition(playerPosition);// 初始位置是从currentPlayer出发

    /* 给currentBullet绑定物理躯干 */
    Hero::bindPhysicsBodyAndTag(currentBullet, PlayerBulletAndEnemyBitmask, PlayerBulletTag);

    /* 加入渲染树 */
    this->getParent()->addChild(currentBullet);

    Vec2 offset = touchWorldPosition - playerPosition;
    offset.normalize();// currentPlayer位置指向鼠标touch位置的单位向量

    /* 定义一些动作 */
    auto actionMove = MoveBy::create(1.5f, offset * ShootSpeed);// 1.5秒到达目的地
    auto actionRemove = RemoveSelf::create();// 删掉自身
    
    /* 让currentBullet完成上面的一系列动作 */
    currentBullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}