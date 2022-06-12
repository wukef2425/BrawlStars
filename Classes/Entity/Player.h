/**
* @file Player.h
* @author wukef & wyf
*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity/Hero.h"

class Player : public Hero
{
private:

    enum Key { W, A, S, D, E, C };

    bool keyPressed[6] = {};

public:

    static Player* Player::create(const std::string& filename);

    /* 用于监听键盘 使player移动 */
    void listenToKeyPresses(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void listenToKeyReleases(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void ChangePosition(bool moveDecide);
};

#endif // #define __PLAYER_H__