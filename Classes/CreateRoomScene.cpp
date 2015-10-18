//
//  CreateRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 25/08/2015.
//
//

#include "CreateRoomScene.h"

Scene* CreateRoomScene::createScene()
{
//    Multiplayer::getInstance()->resetAllListener();
    
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
    
    
    
    
    auto node = CSLoader::createNode(CREATE_ROOM_SCENE_FILE);
    cocos2d::ui::Button* buttonBack =  static_cast<cocos2d::ui::Button*>(node->getChildByName(BACK_BUTTON));
    assert(buttonBack);
    
    cocos2d::ui::Button* buttonCreate = static_cast<cocos2d::ui::Button*>(node->getChildByName(CREATE_BUTTON));
    assert(buttonCreate);
    
    buttonCreate->addTouchEventListener(CC_CALLBACK_2(CreateRoomScene::CreateRoom, this));
    buttonBack->addTouchEventListener(CC_CALLBACK_2(CreateRoomScene::GotoChooseRoomScene, this));
    

    for(int i = 1 ; i <= NUM_BACKGROUNDS ; i ++)
    {
        cocos2d::ui::Widget* image = static_cast<cocos2d::ui::Widget*>(node->getChildByName(CREATE_ROOM_SCENE_BACKGROUND_PREFIX+std::to_string(i)));
        image->addTouchEventListener(CC_CALLBACK_2(CreateRoomScene::BackgroundSelectedChanged, this));
    }
    
    
    this->addChild(node);
    
    PhotonMultiplayer::getInstance()->setListener(this);
    this->scheduleUpdate();
    return true;
}



void CreateRoomScene::BackgroundSelectedChanged(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        if(backgroundSelected != NULL)
        {
            RemoveSelectedBorder(backgroundSelected);
        }
        backgroundSelected = pSender;
        ShowSelectedBorder(backgroundSelected);
    }
}


void CreateRoomScene::ShowSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName(BORDER_UNSELECTED)->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName(BORDER_SELECTED)->setVisible(true);
}

void CreateRoomScene::RemoveSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName(BORDER_SELECTED)->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName(BORDER_UNSELECTED)->setVisible(true);
}


void CreateRoomScene::GotoChooseRoomScene(Ref*, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        auto scene = ChooseRoomScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}


void CreateRoomScene::CreateRoom(Ref* node, ui::Widget::TouchEventType type)
{
    
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
        
        if(backgroundSelected != NULL )
        {
            std::string background = static_cast<Node*>(backgroundSelected)->getName();
            
            std::map<std::string, std::string> properties ={{ROOM_PROPERTY_BACKGROUND, background}};
            
            auto isVisible = !this->getChildByName(CREATE_ROOM_SCENE)->getChildByName<cocos2d::ui::CheckBox*>("privateCheckBox")->isSelected();
            
            PhotonMultiplayer::getInstance()->opCreateRoom(properties, isVisible);
            LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "creating room...", 50.0f);
            
        }
        
    }
}

void CreateRoomScene::onCreateRoomDone()
{
    MultiplayerCallback::onCreateRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), true, "Done...", 100.0f);
    auto scene = ChooseCharacterScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}


void CreateRoomScene::update(float dt)
{
    PhotonMultiplayer::getInstance()->service();
}



