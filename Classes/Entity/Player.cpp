/**
* @file Player.cpp
* @author wukef & wyf
*/

#include "Player.h"
#include "Consts.h"
#include "Scene/FightScene.h"

void Player::listenToKeyPresses(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    using K = cocos2d::EventKeyboard::KeyCode;// 全if不elseif可以实现同时按两个键

    if (keyCode == K::KEY_D)
    {
        keyPressed[D] = true;
    }
    if (keyCode == K::KEY_A)
    {
        keyPressed[A] = true;
    }
    if (keyCode == K::KEY_W)
    {
        keyPressed[W] = true;
    }
    if (keyCode == K::KEY_S)
    {
        keyPressed[S] = true;
    }
    if (keyCode == K::KEY_E)
    {
        keyPressed[E] = true;
    }
    if (keyCode == K::KEY_C)
    {
        keyPressed[C] = true;
    }
}

void Player::listenToKeyReleases(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    using K = cocos2d::EventKeyboard::KeyCode;

    if (keyCode == K::KEY_W)
    {
        keyPressed[W] = false;
    }
    if (keyCode == K::KEY_A)
    {
        keyPressed[A] = false;
    }
    if (keyCode == K::KEY_S)
    {
        keyPressed[S] = false;
    }
    if (keyCode == K::KEY_D)
    {
        keyPressed[D] = false;
    }
    if (keyCode == K::KEY_E)
    {
        keyPressed[E] = false;
    }
    if (keyCode == K::KEY_C)
    {
        keyPressed[C] = false;
    }
}

/*  更新玩家的信息，包括所在位置，所在位置是barrier/grass，以及镜头跟随 */
void Player::ChangePosition(bool moveDecide)
{
    //思路是每次都要调用这个函数，如果所在位置是障碍物则实现跳回去，如果不是就正常运行    
    if (moveDecide == false)
    {
        x = initX;
        y = initY;
        setPosition(initX, initY);//返回上次正确移动记录的数据

        return;
    }
    
    if (moveDecide == true)
    {
        initX = x;
        initY = y;
        //如果所在位置不在障碍物处，会先读取坐标
        if (keyPressed[W])
        {
            y += step;
        }
        if (keyPressed[A])
        {
            x -= step;
        }
        if (keyPressed[S])
        {
            y -= step;
        }
        if (keyPressed[D])
        {
            x += step;
        }
        if (keyPressed[E] && true == this->isUltimateSkillReady())
        {
            this->confirmToReleaseUltimateSkill();
            this->clearUltimateSkillProgress();// 大招释放 清空进度条释放
        }
        if (keyPressed[C])
        {
            auto hello = Sprite::create("Hero/delighted.png");
            hello->setPosition(this->getPosition() + Vec2(0, 70));
            this->getParent()->addChild(hello);
            auto actionRemove = RemoveSelf::create();
            hello->runAction(actionRemove);
        }

        setPosition(x, y);
    }
    
}




