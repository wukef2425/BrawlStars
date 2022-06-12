#pragma once
#ifndef __Gamepause__H__
#define __Gamepause__H__
#include "cocos2d.h"


USING_NS_CC;
class Gamepause : public cocos2d::Scene
{
public:
    virtual bool init();

    static cocos2d::Scene* scene();

    //继续游戏
    void Gamepause::menuContinueCallback(Ref* pSender);
    //重新开始游戏
    void Gamepause::menuRestartCallback(Ref* pSender);
    //回主界面
    void Gamepause::menuLoginCallback(Ref* pSender);

    CREATE_FUNC(Gamepause);


private:

    cocos2d::Menu* pMenu;

};

#endif // __Gamepause_H__