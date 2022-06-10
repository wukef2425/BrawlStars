#include "cocos2d.h"
#include "Utils/CameraEffect.h"

CameraEffect * CameraEffect::create(cocos2d::Scene * scene)
{
	auto cameraEffect = new(std::nothrow) CameraEffect;

	if (cameraEffect == nullptr)
	{
		return nullptr;
	}

	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	cocos2d::Camera* newCamera;

	if (scene->getCameras().empty())
	{
		newCamera = Camera::createOrthographic(winSize.width, winSize.height, 0, 1);// 控制窗口大小
	}
	else
	{
		newCamera = scene->getCameras().front();
	}

	newCamera->setCameraFlag(cocos2d::CameraFlag::DEFAULT);
	newCamera->setPosition(cocos2d::Vec2(-winSize.width * 0.5f, -winSize.height * 0.5f)); // 控制镜头位置
	newCamera->setDepth(1);// 控制在那一层

	cameraEffect->addChild(newCamera);

	cameraEffect->retain();
	cameraEffect->autorelease();

	return cameraEffect;

}

void CameraEffect::FollowPlayer(Player* player)
{
	if (player != nullptr)
	{
		player->addChild(this);
	}
}