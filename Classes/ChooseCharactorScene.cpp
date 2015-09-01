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
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("charactors.plist");
    
    auto node = CSLoader::createNode("ChooseCharactor.csb");
    node->setName("ChooseCharactorScene");
    ui::Button* buttonBack = static_cast<ui::Button*>(node->getChildByName("buttonBack"));
    
    buttonBack->addTouchEventListener(CC_CALLBACK_1(ChooseCharactorScene::GotoChooseRoomScene, this));
    //    node->setPosition(origin);
    
    for(int i = 1 ; i <= 6 ; i ++)
    {
        ImageView* image = static_cast<ImageView*>(node->getChildByName("charactor"+std::to_string(i)));
        image->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::CharactorSelectedChanged, this));
    }
    
    
    this->addChild(node);
    
    //this->schedule(schedule_selector(ChooseCharactorScene::CountDownTask), 1.0f);
    
    return true;
}

void ChooseCharactorScene::CharactorSelectedChanged(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        if(playerSelected != NULL){
            RemoveSelectedBorder(playerSelected);
        }
        playerSelected = pSender;
        ShowSelectedBorder(playerSelected);
        ShowSelectedCharactor(static_cast<Node*>(pSender)->getName(), true);
    }
}

void ChooseCharactorScene::ShowSelectedCharactor(std::string name, bool left)
{
    std::string place = left ? "player" : "opponent";
    Sprite* sprite = static_cast<Sprite*>(this->getChildByName("ChooseCharactorScene")->getChildByName(place));
    sprite->setSpriteFrame("Charactors/" + name + "/icon_big.png");
    sprite->setScale(1);
    sprite->setScale(CHARACTOR_WIDTH / sprite->getBoundingBox().size.width,
                      CHARACTOR_HEIGHT / sprite->getBoundingBox().size.height);
}

void ChooseCharactorScene::ShowSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName("unselected")->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName("selected")->setVisible(true);
}

void ChooseCharactorScene::RemoveSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName("selected")->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName("unselected")->setVisible(true);
}


void ChooseCharactorScene::GotoChooseRoomScene(Ref* pSender)
{
    auto scene = ChooseRoomScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void ChooseCharactorScene::CountDownTask(float dt)
{
    auto node = this->getChildByName("ChooseCharactorScene");
    ui::Text* labelCountDown = static_cast<ui::Text*>(node->getChildByName("labelCountDown"));
    int value = std::atoi(labelCountDown->getString().c_str()) - 1;
    if(value > 0)
    {
        
        labelCountDown->setText(std::to_string(value));
    }
    else
    {
        this->unschedule(schedule_selector(ChooseCharactorScene::CountDownTask));
        
        auto scene = ChooseRoomScene::createScene();
        
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
        
    }
}
