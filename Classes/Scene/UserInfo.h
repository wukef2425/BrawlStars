#pragma once
#ifndef __USER_INFO_H__
#define __USER_INFO_H__

#include "cocos2d.h"

class UserInfo : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void initDecoration();

    void initReturnMenu();//·µ»ØÖ÷Ò³Ãæ

    void menuReturnCallback(Ref* pSender);

    CREATE_FUNC(UserInfo);

protected:

    cocos2d::Menu* returnButton_;

};

#endif // #define __USER_INFO_H__
