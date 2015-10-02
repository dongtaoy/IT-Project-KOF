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
    Multiplayer::getInstance()->resetAllListener();
    
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
    
    // search button
    ui::Button* buttonSearch = static_cast<ui::Button*>(node->getChildByName(SEARCH_BUTTON));
    buttonSearch->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::SearchRoom, this));
    
    
    ui::ListView* listRoom = static_cast<ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    Vector<Widget *> items = listRoom->getItems();
    assert(items.front());
    static_cast<ImageView*>(items.front())->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::OnSelectedItem, this));
    listRoom->setItemModel(items.front());
    listRoom->removeItem(0);

    
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


void ChooseRoomScene::OnSelectedItem(Ref* pSender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED){
        std::string roomID = static_cast<ImageView*>(pSender)->getChildByName<Text*>(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID)->getString();
        
        std::string bestof = static_cast<ImageView*>(pSender)->getChildByName<Text*>(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BESTOF)->getString();
        
        std::string background = *(std::string*)((static_cast<ImageView*>(pSender)->getChildByName<ImageView*>(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND)->getUserData()));
        
        Multiplayer::getInstance()->setBestof(std::atoi(bestof.c_str()));
        Multiplayer::getInstance()->setBackground(background);
        Multiplayer::getInstance()->setRoomID(roomID);
        Multiplayer::joinRoom(this);
        CCLOG("###########%s", this->getName().c_str());
        LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "joining room...", 30.0f);

    }
}


void ChooseRoomScene::onJoinRoomDone(){
    MultiplayerCallback::onJoinRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "subscribing room...", 60.0f);
}

void ChooseRoomScene::onSubscribeRoomDone(){
    MultiplayerCallback::onSubscribeRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "DONE...", 100.0f);
    auto scene = ChooseCharacterScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


// RoomRequestListner
void ChooseRoomScene::onGetLiveRoomInfoDone(std::string roomId,
                                            std::string owner,
                                            int maxUsers,
                                            std::string name,
                                            std::string customData,
                                            std::vector<std::string> users,
                                            std::map<std::string, std::string> properties)
{
    
    auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
    ui::ListView* list = static_cast<ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    list->pushBackDefaultItem();
    auto item = list->getItems().back();
    // add room id
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID))->setString(roomId);
    // BEST OF
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BESTOF))->setString(properties.find(ROOM_PROPERTY_BESTOF)->second);
    // status
    static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_STATUS))->setString(std::to_string(users.size()) + "/" + std::to_string(maxUsers));
    // image
    std::string filename = (boost::format(BACKGROUND_ICON_PATH) % properties.find(ROOM_PROPERTY_BACKGROUND)->second).str();
    static_cast<ui::ImageView*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND))->loadTexture(filename, ui::Widget::TextureResType::PLIST);
    
    std::string* background = new std::string(properties.find(ROOM_PROPERTY_BACKGROUND)->second);
    
    static_cast<ui::ImageView*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_BACKGROUND))->setUserData(background);
    
}

void ChooseRoomScene::SearchRoom(Ref* pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED){
        auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
        auto sprite = static_cast<ui::ImageView*>(node->getChildByName(CHOOSE_ROOM_SCENE_SPRITE_SEARCH));
	    auto textSearch = static_cast<ui::TextField*>(sprite->getChildByName(CHOOSE_ROOM_SCENE_TEXT_SEARCH));
	    
	    ui::ListView* list = static_cast<ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
	    for (int i =0 ; i < list->getItems().size(); i++ ){
	        auto item = list->getItem(i);
	        std::string id = static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID))->getString();
	        if(!(id.compare(textSearch->getString()))){
	            OnSelectedItem(item, Widget::TouchEventType::ENDED);
	            return;
	        }
	    }
	    MessageBox("", "Room ID does not exist!");
	    
	    CCLOG("%s",textSearch->getString().c_str());
    }
}

void ChooseRoomScene::onRoomDestroyed(std::string roomID){
    auto node = this->getChildByName(CHOOSE_ROOM_SCENE);
    ui::ListView* list = static_cast<ui::ListView*>(node->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST));
    for (int i =0 ; i < list->getItems().size(); i++ ){
        auto item = list->getItem(i);
        std::string id = static_cast<ui::Text*>(item->getChildByName(CHOOSE_ROOM_SCENE_ROOM_LIST_ITEM_ID))->getString();
        if(!(id.compare(roomID))){
            list->removeItem(i);
            return;
        }
    }
}






