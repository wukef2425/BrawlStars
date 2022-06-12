#pragma once
#ifndef __USER_INFO_H__
#define __USER_INFO_H__

#include "cocos2d.h"

USING_NS_CC;

class UserInfo : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void initDecoration();

    void UserInfo::initTrophy();

    void initReturnMenu();//·µ»ØÖ÷Ò³Ãæ

    void menuReturnCallback(Ref* pSender);

    void UserInfo::initHero();
    CREATE_FUNC(UserInfo);

protected:

    cocos2d::Menu* pMenu;

    Size visibleSize;
    Vec2 origin;

};

#endif // #define __USER_INFO_H__
