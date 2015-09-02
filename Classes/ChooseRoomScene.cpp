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
    
    auto node = CSLoader::createNode(CHOOSE_ROOM_SCENE_FILE);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BACKGROUND_PLIST);
    
    // back button
    ui::Button* buttonBack = static_cast<ui::Button*>(node->getChildByName(BACK_BUTTON));
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoMainMenuScene, this));
    
    // create room button
    ui::Button* buttonCreate = static_cast<ui::Button*>(node->getChildByName(CREATE_BUTTON));
    buttonCreate->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoCreateRoomScene, this));
    
    ui::ListView* listRoom = static_cast<ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    Vector<Widget *> items = listRoom->getItems();
    assert(items.front());
    listRoom->setItemModel(items.front());
    listRoom->removeItem(0);
//    listRoom->setTouchEnabled(false);
    listRoom->addEventListener(CC_CALLBACK_2(ChooseRoomScene::OnSelectedItem, this));

    
//    Multiplayer::getInstance()->fetchRooms(this);
    
    
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


void ChooseRoomScene::AddRoom(AppWarp::liveroom room)
{
    auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
    ui::ListView* list = static_cast<ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    list->pushBackDefaultItem();
    auto item = list->getItems().back();
    // add room id
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID))->setString(room.rm.roomId);
    // BEST OF
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BESTOF))->setString(room.properties.find(ROOM_PROPERTY_BESTOF)->second);
    // status
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_STATUS))->setString(std::to_string(room.users.size()) + "/" + std::to_string(room.rm.maxUsers));
    // image
    //    std::cout <<  "Backgrounds/" + room.properties.find(ROOM_PROPERTY_BACKGROUND)->second + "/icon.png" << std::endl;
    static_cast<ui::ImageView*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND))->loadTexture(std::string(BACKGROUND_RESOURCE_DIR)+ "/" + room.properties.find(ROOM_PROPERTY_BACKGROUND)->second + "/" + std::string(BACKGROUND_ICON), ui::Widget::TextureResType::PLIST);
    
}


//// RoomRequestListner
//void ChooseRoomScene::onGetLiveRoomInfoDone(AppWarp::liveroom room)
//{
//    
//    auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
//    ui::ListView* list = static_cast<ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
//    list->pushBackDefaultItem();
//    auto item = list->getItems().back();
//    // add room id
//    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID))->setString(room.rm.roomId);
//    // BEST OF
//    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BESTOF))->setString(room.properties.find(ROOM_PROPERTY_BESTOF)->second);
//    // status
//    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_STATUS))->setString(std::to_string(room.users.size()) + "/" + std::to_string(room.rm.maxUsers));
//    // image
////    std::cout <<  "Backgrounds/" + room.properties.find(ROOM_PROPERTY_BACKGROUND)->second + "/icon.png" << std::endl;
//    static_cast<ui::ImageView*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND))->loadTexture(std::string(BACKGROUND_RESOURCE_DIR)+ "/" + room.properties.find(ROOM_PROPERTY_BACKGROUND)->second + "/" + std::string(BACKGROUND_ICON), ui::Widget::TextureResType::PLIST);
//    
////    CCLOG("%lu/%d", room.users.size(), room.rm.maxUsers);
//    
//}






