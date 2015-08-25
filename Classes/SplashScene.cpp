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
    this->addChild(node);
    
    this->scheduleOnce( schedule_selector( SplashScene::GoToMainMenuScene ), DISPLAY_TIME_SPLASH_SCENE );
    
    
    return true;
}

void SplashScene::GoToMainMenuScene( float dt )
{
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}
