//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseCharactorScene.h"

USING_NS_CC;
using namespace ui;

Scene* ChooseCharactorScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChooseCharactorScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChooseCharactorScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto node = CSLoader::createNode("ChooseCharactor.csb");
    node->setName("ChooseCharactorScene");
    
    
    
    
    this->schedule(schedule_selector(ChooseCharactorScene::CountDownTask), 1.0f);
    
    
    this->addChild(node);
        
    
    return true;
}

void ChooseCharactorScene::GotoChooseRoomSceneScene(Ref* pSender)
{
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void ChooseCharactorScene::CountDownTask(float dt)
{
    auto node = this->getChildByName("ChooseCharactorScene");
    ui::Text* labelCountDown = static_cast<ui::Text*>(node->getChildByName("labelCountDown"));
    int value = std::atoi(labelCountDown->getString().c_str()) - 1;
    labelCountDown->setText(std::to_string(value));
}
