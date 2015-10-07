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
    
    cocos2d::Size visibleSize = Director::getInstance()->getWinSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
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
    
    for(int i = 1 ; i <= NUM_BESTOF ; i ++)
    {
        cocos2d::ui::CheckBox* checkbox = static_cast<cocos2d::ui::CheckBox*>(node->getChildByName(CREATE_ROOM_SCENE_CHECKBOX_PREFIX+std::to_string(i)));
        
        checkbox->addEventListener(CC_CALLBACK_2(CreateRoomScene::CheckboxSelectedChanged, this));
    }
    
    this->addChild(node);
    
    this->scheduleUpdate();
    return true;
}

void CreateRoomScene::CheckboxSelectedChanged(Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
    if(type == cocos2d::ui::CheckBox::EventType::SELECTED){
        
        if(bestOfSelected != NULL){
            static_cast<cocos2d::ui::CheckBox*>(bestOfSelected)->setSelected(false);
        }
        bestOfSelected = pSender;
        
    }
    else{
        bestOfSelected = NULL;
    }
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

void CreateRoomScene::onJoinLobbyDone()
{
    MultiplayerCallback::onJoinLobbyDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "subscribing lobby... ", 66.0f);
//    Multiplayer::subscribeLobby(this);
}

void CreateRoomScene::onSubscribeLobbyDone()
{
    MultiplayerCallback::onSubscribeLobbyDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), true, "DONE... ", 100.0f);
//    auto scene = ChooseRoomScene::createScene();
//    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



void CreateRoomScene::CreateRoom(Ref* node, ui::Widget::TouchEventType type)
{
    
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
        
        if(backgroundSelected != NULL && bestOfSelected != NULL)
        {
            std::string background = static_cast<Node*>(backgroundSelected)->getName();
            std::string bestof = static_cast<Node*>(bestOfSelected)->getChildByName<cocos2d::ui::Text*>(CREATE_ROOM_SCENE_BESTOF_LABEL)->getString();
            
            std::map<std::string, std::string> properties ={{ROOM_PROPERTY_BACKGROUND, background},{ROOM_PROPERTY_BESTOF, bestof}};
            
            PhotonMultiplayer::getInstance()->opCreateRoom(properties);
            
        }
        
    }
}

void CreateRoomScene::onCreateRoomDone(std::string roomId, std::string owner, int maxUsers, std::string name)
{
    MultiplayerCallback::onCreateRoomDone(roomId, owner, maxUsers, name);
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "joining room...", 60.0f);
    std::string background = static_cast<Node*>(backgroundSelected)->getName();
    std::string bestof = static_cast<Node*>(bestOfSelected)->getChildByName<cocos2d::ui::Text*>(CREATE_ROOM_SCENE_BESTOF_LABEL)->getString();
//    Multiplayer::getInstance()->setRoomID(roomId);
//    Multiplayer::getInstance()->setBackground(background);
//    Multiplayer::getInstance()->setBestof(std::atoi(bestof.c_str()));
}

void CreateRoomScene::onJoinRoomDone(){
    MultiplayerCallback::onJoinRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "subscribing room...", 90.0f);
    
}

void CreateRoomScene::onSubscribeRoomDone(){
    MultiplayerCallback::onSubscribeRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "DONE...", 100.0f);
//    auto scene = ChooseCharacterScene::createScene();
//    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void CreateRoomScene::update(float dt)
{
    PhotonMultiplayer::getInstance()->service();
}



