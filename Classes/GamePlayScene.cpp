//
//  GamePlayScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 6/09/2015.
//
//

#include "GamePlayScene.h"
USING_NS_CC;

Scene* GamePlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Multiplayer::getInstance()->setNotificationListener(this);
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto node = CSLoader::createNode("GamePlay.csb");
    this->addChild(node);
    
    return true;
}

void GamePlayScene::onChatReceived(AppWarp::chat message)
{
    CCLOG("in game play %s", message.chat.c_str());
}

