/**
* @file Player.cpp
* @author wukef
*/

#include "Player.h"

Player* Player::create(const std::string& filename) 
{
    auto player = new(std::nothrow) Player;

    if (!player)
    {
        return nullptr;
    }

    auto chosenHero = Sprite::create(filename);

    if (chosenHero)
    {
        player->setPosition(player->x, player->y);// player初始坐标(x,y)根据窗口大小在Player类的protected里面改

        player->changeHeroTo(chosenHero);// 包含了sprite_=chosenHero和addchilid(chosenHero)

        player->autorelease();

        return player;
    }
    
    return nullptr;
}

void Player::listenToKeyPresses(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    using K = cocos2d::EventKeyboard::KeyCode;

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
}

void Player::listenToKeyReleases(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    using K = cocos2d::EventKeyboard::KeyCode;

    if (keyCode == K::KEY_D)
    {
        keyPressed[D] = false;
    }
    if (keyCode == K::KEY_A)
    {
        keyPressed[A] = false;
    }
    if (keyCode == K::KEY_W)
    {
        keyPressed[W] = false;
    }
    if (keyCode == K::KEY_S)
    {
        keyPressed[S] = false;
    }
}


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

    setPosition(x, y);
}
