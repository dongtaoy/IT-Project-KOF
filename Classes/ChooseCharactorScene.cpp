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
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CHOOSE_CHARACTOR_SCENE_CHARACTOR_PLIST);
    
    auto node = CSLoader::createNode(CHOOSE_CHARACTOR_SCENE_FILE);
    node->setName(CHOOSE_CHARACTOR_SCENE);
    
    ui::Button* buttonBack = static_cast<ui::Button*>(node->getChildByName(BACK_BUTTON));
    
    buttonBack->addTouchEventListener(CC_CALLBACK_1(ChooseCharactorScene::GotoChooseRoomScene, this));
    //    node->setPosition(origin);
    
    for(int i = 1 ; i <= 6 ; i ++)
    {
        ImageView* image = static_cast<ImageView*>(node->getChildByName(CHOOSE_CHARACTOR_SCENE_CHARACTOR_PREFIX+std::to_string(i)));
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
    std::string place = left ? CHOOSE_CHARACTOR_SCENE_PLAYER_ICON_HOLDER : CHOOSE_CHARACTOR_SCENE_OPPONENT_ICON_HOLDER;
    Sprite* sprite = static_cast<Sprite*>(this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(place));
    sprite->setSpriteFrame(std::string(CHARACTOR_RESOURCE_DIR) + "/" + name + "/" + std::string(CHARACTOR_ICON_BIG));
    sprite->setScale(1);
    sprite->setScale(CHOOSE_CHARACTOR_SCENE_CHARACTOR_WIDTH / sprite->getBoundingBox().size.width,
                      CHOOSE_CHARACTOR_SCENE_CHARACTOR_HEIGHT / sprite->getBoundingBox().size.height);
}

void ChooseCharactorScene::ShowSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName(BORDER_UNSELECTED)->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName(BORDER_SELECTED)->setVisible(true);
}

void ChooseCharactorScene::RemoveSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName(BORDER_SELECTED)->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName(BORDER_UNSELECTED)->setVisible(true);
}


void ChooseCharactorScene::GotoChooseRoomScene(Ref* pSender)
{
    auto scene = ChooseRoomScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void ChooseCharactorScene::CountDownTask(float dt)
{
    auto node = this->getChildByName(CHOOSE_CHARACTOR_SCENE);
    ui::Text* labelCountDown = static_cast<ui::Text*>(node->getChildByName(CHOOSE_CHARACTOR_SCENE_COUNT_DOWN_LABEL));
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
