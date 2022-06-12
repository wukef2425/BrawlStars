/**
*@file StartScene.cpp
* @author wyf
*/
#include "StartScene.h"
#include "audio/include/AudioEngine.h"
#include "StartLoginScene.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    initTermLabel();//Animation of entrance

    preLoadingResources();

    scheduleOnce(SEL_SCHEDULE(&StartScene::ChangeScene), 2.0f);//switch scene

    return true;
}

void StartScene::initTermLabel()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //The entry animation shows the name of our group
    auto label = Label::createWithTTF("COOL\nWZW\nTEAM", "fonts/Marker Felt.ttf", 60);

    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height / 2 + label->getContentSize().height / 2));

        this->addChild(label, 0);
    }

    //and some weird hints
}

//switch to loginScene
void StartScene::ChangeScene(float dt)
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, StartLoginScene::createScene()));
}

//preloading something
void StartScene::preLoadingResources()
{
    /* ±≥æ∞Õº∆¨ */
    Director::getInstance()->getTextureCache()->addImage("Scene/GameOverScene.png");
    Director::getInstance()->getTextureCache()->addImage("Scene/HeroChooseScene.jpg");
    Director::getInstance()->getTextureCache()->addImage("Scene/introductionScene.png");
    Director::getInstance()->getTextureCache()->addImage("Scene/MenuScene.jpg");
    Director::getInstance()->getTextureCache()->addImage("Scene/MyLoginScene.jpg");
    Director::getInstance()->getTextureCache()->addImage("Scene/SetScene.jpg");
    Director::getInstance()->getTextureCache()->addImage("Scene/VolumeScene.png");
    Director::getInstance()->getTextureCache()->addImage("Scene/UserScene.png");
    /* ”¢–€Œ‰∆˜¿‡ */
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/ChangYi-bullet.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/enemy-bullet.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/enemy-spiky-eclipse.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/HaoQing-bullet.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/nobullet.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/SanYue-bullet.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/ShunDe-bullet.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/spiky-eclipse.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/YunHe-bullet.png");

    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/ChangYi-bullet-usual.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/HaoQing-bullet-usual.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/SanYue-bullet-usual.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/ShunDe-bullet-usual.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/Bullet/YunHe-bullet-usual.png");
    /* ”¢–€µƒ¥ÛÕ∑œÒ */
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/ChangYiAfter.jpg");
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/ChangYiBefore.jpg");
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/HaoQingAfter.jpg");
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/HaoQingBefore.jpg");
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/SanYueAfter.jpg");
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/SanYueBefore.jpg");
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/ShunDeAfter.jpg");
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/ShunDeBefore.jpg");
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/YunHeAfter.jpg");
    Director::getInstance()->getTextureCache()->addImage("Hero/ChooseHero/YunHeBefore.jpg");
    /* ”¢–€µƒ¥ÛÕ∑œÒ2 */
    Director::getInstance()->getTextureCache()->addImage("Hero/EndHero/ChangYi.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/EndHero/HaoQing.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/EndHero/SanYue.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/EndHero/ShunDe.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/EndHero/YunHe.png");
    /* ’Ω∂∑–°”¢–€ */
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/bloodBg.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/bloodHp.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/bulletMp.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/heroSp.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/sliderThumb.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/ChangYi.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/HaoQing.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/YunHe.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/SanYue.png");
    Director::getInstance()->getTextureCache()->addImage("Hero/FightHero/ShunDe.png");
    /* ¬“∆ﬂ∞À‘„µƒ–°∞¥≈• */
    Director::getInstance()->getTextureCache()->addImage("Button/Leave.png");
    Director::getInstance()->getTextureCache()->addImage("Button/OnlineStart.png");
    Director::getInstance()->getTextureCache()->addImage("Button/pause_background.png");
    Director::getInstance()->getTextureCache()->addImage("Button/pause_continue.png");
    Director::getInstance()->getTextureCache()->addImage("Button/pause_login.png");
    Director::getInstance()->getTextureCache()->addImage("Button/pause_restart.png");
    Director::getInstance()->getTextureCache()->addImage("Button/PauseNormal.png");
    Director::getInstance()->getTextureCache()->addImage("Button/PauseSelected.png");
    Director::getInstance()->getTextureCache()->addImage("Button/Return.png");
    Director::getInstance()->getTextureCache()->addImage("Button/RuleBooks.png");
    Director::getInstance()->getTextureCache()->addImage("Button/SetReturn.png");
    Director::getInstance()->getTextureCache()->addImage("Button/Start.png");
    Director::getInstance()->getTextureCache()->addImage("Button/VolumeSound.png");
    /* “Ù¿÷ */
    AudioEngine::preload("BGM.mp3");
}
