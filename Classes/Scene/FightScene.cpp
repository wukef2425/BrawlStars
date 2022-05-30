/*Fight界面主要要加载的内容有
1.UI部件，包括游戏时间/人物血量及蓝/生存人数/雾/雾的警告，他们是动态可变化的
2.监听器，通过鼠标/键盘/触摸检测来对人物动作进行改变
3.每一个元素所在的层：地图 0；障碍物、武器 1；设置层 5；结束层
4.分界线，就是外围的两个格子

*/
#include "cocos2d.h"
#include "FightScene.h"

USING_NS_CC;

Scene* FightScene::createScene()
{
    return FightScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool FightScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
   //不知道为什么加入tmx的时候老是加载错误，太气人了
	//auto* SnowMap = TMXTiledMap::create("Map/SnowMap.tmx");
	//addChild(SnowMap, 0);

    return true;
}

