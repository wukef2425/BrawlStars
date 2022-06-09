#ifndef __CAMERA_EFFECT_H__
#define __CAMERA_EFFECT_H__

#include "cocos2d.h"
#include "Entity/Player.h"

class CameraEffect :public cocos2d::Camera
{
private:

	Player* TargetPlayer;

public:

	static CameraEffect* create(cocos2d::Scene* scene);

	void FollowPlayer(Player* player);
};

#endif