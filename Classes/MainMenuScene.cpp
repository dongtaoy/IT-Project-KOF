//
//  MainMenuScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#include "MainMenuScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    LabelTTF *startMultiplayerLabel = LabelTTF::create("Multiplayer", "Marker Felt", 30);
    startMultiplayerLabel->setColor(Color3B::BLACK);
    
//    MenuItemLabel *startMultiplayerButton = MenuItemLabel::create(startMultiplayerLabel, CC_CALLBACK_3(MainMenuScene::,
//    
//    

    
    
    return true;
}

