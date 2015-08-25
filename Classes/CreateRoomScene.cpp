//
//  CreateRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 25/08/2015.
//
//

#include "CreateRoomScene.h"

using namespace ui;
USING_NS_CC;

Scene* CreateRoomScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CreateRoomScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CreateRoomScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto node = CSLoader::createNode("CreateRoom.csb");
//    Button* buttonBack =  static_cast<Button*>(node->getChildByName("button"));
    this->addChild(node);
    
    return true;
}