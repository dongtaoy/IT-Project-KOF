//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseRoomScene.h"

Scene* ChooseRoomScene::createScene()
{
//    Multiplayer::getInstance()->resetAllListener();
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChooseRoomScene::create();
    
    layer->onRoomListUpdate();
    
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
    
    
    
    cocos2d::Size visibleSize = Director::getInstance()->getWinSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto node = CSLoader::createNode(CHOOSE_ROOM_SCENE_FILE);
    node->setName(CHOOSE_ROOM_SCENE);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BACKGROUND_PLIST);
    
    // back button
    cocos2d::ui::Button* buttonBack = static_cast<cocos2d::ui::Button*>(node->getChildByName(BACK_BUTTON));
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoMainMenuScene, this));
    
    // create room button
    cocos2d::ui::Button* buttonCreate = static_cast<cocos2d::ui::Button*>(node->getChildByName(CREATE_BUTTON));
    buttonCreate->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoCreateRoomScene, this));
    
    // search button
    cocos2d::ui::Button* buttonSearch = static_cast<cocos2d::ui::Button*>(node->getChildByName(SEARCH_BUTTON));
    buttonSearch->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::SearchRoom, this));
    
    
    cocos2d::ui::ListView* listRoom = static_cast<cocos2d::ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    cocos2d::Vector<cocos2d::ui::Widget*> items = listRoom->getItems();
    static_cast<cocos2d::ui::ImageView*>(items.front())->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::OnSelectedItem, this));
    listRoom->setItemModel(items.front());
    listRoom->removeItem(0);
    
    
    
    this->addChild(node);
    
    PhotonMultiplayer::getInstance()->setListener(this);
    this->scheduleUpdate();
    
    return true;
}

void ChooseRoomScene::update(float dt)
{
    PhotonMultiplayer::getInstance()->service();
}

void ChooseRoomScene::GotoMainMenuScene(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        auto scene = MainMenuScene::createScene();
    
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}


void ChooseRoomScene::GotoCreateRoomScene(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        auto scene = CreateRoomScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}



void ChooseRoomScene::OnSelectedItem(Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
        std::string roomID = static_cast<cocos2d::ui::ImageView*>(pSender)->getChildByName<cocos2d::ui::Text*>(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID)->getString();
//        
//        std::string bestof = static_cast<cocos2d::ui::ImageView*>(pSender)->getChildByName<cocos2d::ui::Text*>(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BESTOF)->getString();
//        
//        std::string background = *(std::string*)((static_cast<cocos2d::ui::ImageView*>(pSender)->getChildByName<cocos2d::ui::ImageView*>(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND)->getUserData()));
//        
////        PhotonMultiplayer::getInstance()->setBestof(std::atoi(bestof.c_str()));
////        PhotonMultiplayer::getInstance()->setBackground(background);
////        PhotonMultiplayer::getInstance()->setRoomID(roomID);
        PhotonMultiplayer::getInstance()->opJoinRoom(roomID);
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "joining room...", 50.0f);
    }
}


void ChooseRoomScene::onJoinRoomDone(){
    MultiplayerCallback::onJoinRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), true, "DONE", 100.0f);
    auto scene = ChooseCharacterScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

// RoomRequestListner

void ChooseRoomScene::onRoomListUpdate()
{
    auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
    cocos2d::ui::ListView* list = static_cast<cocos2d::ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    list->removeAllItems();
    std::vector<std::tuple<std::string, int, int, std::map<std::string, std::string>>> roomList = PhotonMultiplayer::getInstance()->getRoomList();
    for (int i = 0; i < roomList.size(); i++)
    {
        if (std::get<1>(roomList.at(i)) != 0 && std::get<1>(roomList.at(i)) != 2)
            createRoomListEntry(std::get<0>(roomList.at(i)), std::get<1>(roomList.at(i)), std::get<2>(roomList.at(i)), std::get<3>(roomList.at(i)));
    }
}

void ChooseRoomScene::createRoomListEntry(std::string roomId,
                                            int nonUsers,
                                            int maxUsers,
                                            std::map<std::string, std::string> properties)
{
    
    auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
    assert(node);
    cocos2d::ui::ListView* list = static_cast<cocos2d::ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    list->pushBackDefaultItem();
    auto item = list->getItems().back();
    // add room id
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID))->setString(roomId);
    // BEST OF
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BESTOF))->setString(properties.find(ROOM_PROPERTY_BESTOF)->second);
    // status
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_STATUS))->setString(std::to_string(nonUsers) + "/" + std::to_string(maxUsers));
    // image
    std::string filename = fmt::format(BACKGROUND_ICON_PATH, properties.find(ROOM_PROPERTY_BACKGROUND)->second);
    static_cast<ui::ImageView*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND))->loadTexture(filename, ui::Widget::TextureResType::PLIST);
    std::string* background = new std::string(properties.find(ROOM_PROPERTY_BACKGROUND)->second);
    static_cast<ui::ImageView*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND))->setUserData(background);
    
}

void ChooseRoomScene::SearchRoom(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
        

//        auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
//        auto sprite = static_cast<ui::ImageView*>(node->getChildByName(CHOOSE_ROOM_SCENE_SPRITE_SEARCH));
//	    auto textSearch = static_cast<ui::TextField*>(sprite->getChildByName(CHOOSE_ROOM_SCENE_TEXT_SEARCH));
//	    
//	    ui::ListView* list = static_cast<ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
//	    for (int i =0 ; i < list->getItems().size(); i++ ){
//	        auto item = list->getItem(i);
//	        std::string id = static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID))->getString();
//	        if(!(id.compare(textSearch->getString()))){
//	            OnSelectedItem(item, cocos2d::ui::Widget::TouchEventType::ENDED);
//	            return;
//	        }
//	    }
//	    MessageBox("", "Room ID does not exist!");
//	    
//	    CCLOG("%s",textSearch->getString().c_str());
    }
}





