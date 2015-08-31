//
//  SplashScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#include "SplashScene.h"


USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto node = CSLoader::createNode("SplashScreen.csb");
    node->setName("SplashScreen");
    this->addChild(node);
    this->schedule(schedule_selector(SplashScene::updateLoadingBar), 0.025f);
    
    // Initialize Multiplayer
    Multiplayer::initialize("test");
    
    return true;
}

void SplashScene::updateLoadingBar( float dt )
{
    ui::LoadingBar* loadingBar = static_cast<ui::LoadingBar*>(this->getChildByName("SplashScreen")->getChildByName("loadingBar"));
    float percent = loadingBar->getPercent() + 1;
    loadingBar->setPercent(percent);
    if(percent >= 100){
        this->unschedule(schedule_selector(SplashScene::updateLoadingBar));
        this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);
    }
}

void SplashScene::GoToMainMenuScene( float dt )
{
    
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}
