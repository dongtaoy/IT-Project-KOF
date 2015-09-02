//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseRoomScene.h"

USING_NS_CC;
using namespace ui;

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
    
    auto node = CSLoader::createNode("ChooseRoom.csb");
    // back button
    ui::Button* buttonBack = static_cast<ui::Button*>(node->getChildByName("buttonBack"));
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoMainMenuScene, this));
    
    // create room button
    ui::Button* buttonCreate = static_cast<ui::Button*>(node->getChildByName("buttonCreate"));
    buttonCreate->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoCreateRoomScene, this));
    
    ui::ListView* listRoom = static_cast<ui::ListView*>(node->getChildByName("listRoom"));
    Vector<Widget *> items = listRoom->getItems();
    assert(items.front());
    listRoom->setItemModel(items.front());
    listRoom->removeItem(0);
//    listRoom->setTouchEnabled(false);
    listRoom->addEventListener(CC_CALLBACK_2(ChooseRoomScene::OnSelectedItem, this));

    
    Multiplayer::getInstance()->fetchRooms(this);
    
    
    this->addChild(node);
    
    return true;
}

void ChooseRoomScene::GotoMainMenuScene(Ref* pSender, Widget::TouchEventType type)
{
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}


void ChooseRoomScene::GotoCreateRoomScene(Ref* pSender, Widget::TouchEventType type)
{
    auto scene = CreateRoomScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


void ChooseRoomScene::OnSelectedItem(Ref* pSender, ui::ListView::EventType type){
    if (type == ListView::EventType::ON_SELECTED_ITEM_END){
        auto scene = ChooseCharactorScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}

// RoomRequestListner
void ChooseRoomScene::onGetLiveRoomInfoDone(AppWarp::liveroom room)
{
    try {
        auto node = this->getChildByName("ChooseRoomScene");
        ui::ListView* list = static_cast<ui::ListView*>(node->getChildByName("listRoom"));
        list->pushBackDefaultItem();
        // add room id
        static_cast<ui::Text*>(list->getItems().back()->getChildByName("text"))->setText(room.rm.roomId);
        // add 0/2
        static_cast<ui::Text*>(list->getItems().back()->getChildByName("status"))->setText(std::to_string(room.users.size()) + "/" + std::to_string(room.rm.maxUsers));
        std::cout << room.rm.name << std::endl;
        CCLOG("%lu/%d", room.users.size(), room.rm.maxUsers);
    } catch (int e) {
        CCLOG("live room error");
    }
    
}






