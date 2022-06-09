/**
* @file Player.cpp
* @author wukef
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
}

/* 更新玩家的信息，包括所在位置，所在位置是barrier/grass，以及镜头跟随 */
void Player::update(float delta)
{
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
    if (keyPressed[E] && this->isUltimateSkillReady() == true)
    {
        this->ultimateSkill();
        this->clearUltimateSkillProgress();
    }

    setPosition(x, y);

}

Vec2 Player::returnPosition()
{
    return Vec2(x, y);
}

