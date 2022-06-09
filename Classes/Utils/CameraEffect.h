/**
* @file CameraEffect.h
* @author wukef
*/

#ifndef __CAMERA_EFFECT_H__
#define __CAMERA_EFFECT_H__

#include "cocos2d.h"
#include "Hero/Player.h"

class CameraEffect :public cocos2d::Camera
{
private:

	Player* TargetPlayer;

public:

	static CameraEffect* create(cocos2d::Scene* scene);

	void FollowPlayer(Player* player, cocos2d::TMXTiledMap* map);
};

#endif