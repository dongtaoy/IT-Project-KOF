//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseRoomScene.h"

USING_NS_CC;

Scene* ChooseRoomScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChooseRoomScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChooseRoomScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    //TODO: help text
    
    
    Label *label = Label::createWithTTF("ChooseRoomScene", "fonts/Marker Felt.ttf", 10);
    label->setColor(Color3B::WHITE);
    label->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label, 1);
    
    // Back Button
    Label *backLabel = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 15);
    backLabel->setColor(Color3B::WHITE);
    MenuItemLabel *backButton = MenuItemLabel::create(backLabel, CC_CALLBACK_1(ChooseRoomScene::GotoMainMenuScene, this));
    backButton->setPosition(origin.x + visibleSize.width * 1 / 10, origin.y + visibleSize.height * 3 / 4);
    Menu *backMenu = Menu::create(backButton, NULL);
    backMenu->setPosition(Point::ZERO);
    this->addChild(backMenu, 1);
    
    
    return true;
}

void ChooseRoomScene::GotoMainMenuScene(Ref* pSender)
{
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}