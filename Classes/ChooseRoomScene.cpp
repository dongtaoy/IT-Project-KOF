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
    //    node->setPosition(origin);
    ui::Button* buttonBack =  static_cast<ui::Button*>(node->getChildByName("buttonBack"));
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoMainMenuScene, this));
    
    ui::TextField* textSearch =  static_cast<ui::TextField*>(node->getChildByName("textSearch"));
    assert(textSearch);
//    textSearch->setPlaceHolder("Room ID");
//    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseRoomScene::GotoMainMenuScene, this));
//    textSearch->setTouchAreaEnabled(true);
//    textSearch->attachWithIME();
//    textSearch->addEventListener(CC_CALLBACK_2(ChooseRoomScene::UpdateTextSearch, this));
    
    this->addChild(node);
        
    
    return true;
}

void ChooseRoomScene::GotoMainMenuScene(Ref* pSender, ui::Widget::TouchEventType type)
{
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void ChooseRoomScene::UpdateTextSearch(Ref* pSender, ui::TextField::EventType type)
{
    switch (type)
    {
        case ui::TextField::EventType::ATTACH_WITH_IME:
        {
            CCLOG("Clicked");
            break;
        }
        case ui::TextField::EventType::DETACH_WITH_IME:
        {
//            enteredData = textSearch->getString();
            break;
        }
    }
}

void ChooseRoomScene::connectToAppWarp()
{
    AppWarp::Client *warpClientRef;
    AppWarp::Client::initialize(APPWARP_APP_KEY,APPWARP_SECRET_KEY);
    warpClientRef = AppWarp::Client::getInstance();
    warpClientRef->setConnectionRequestListener(this);
    warpClientRef->setZoneRequestListener(this);
    warpClientRef->setRoomRequestListener(this);
    warpClientRef->connect("test");
    
    
    
    CCLOG("%s / %s", APPWARP_SECRET_KEY, APPWARP_APP_KEY);
    
    
}

void ChooseRoomScene::onConnectDone(int result, int code)
{
    CCLOG("%d / %d \n", result, code);
    if (result==AppWarp::ResultCode::success)
    {
        CCLOG("onConnectDone .. SUCCESS..session=%d\n", AppWarp::AppWarpSessionID);
        AppWarp::Client *warpClientRef;
        warpClientRef = AppWarp::Client::getInstance();
        warpClientRef->getAllRooms();
        //        warpClientRef->joinRoom(ROOM_ID);
    }
    else if (result==AppWarp::ResultCode::success_recovered)
    {
        CCLOG("onConnectDone .. SUCCESS with success_recovered..session=%d\n", AppWarp::AppWarpSessionID);
    }
    else if (result==AppWarp::ResultCode::connection_error_recoverable)
    {
        CCLOG("onConnectDone .. FAILED..connection_error_recoverable..session=%d\n", AppWarp::AppWarpSessionID);
    }
    else if (result==AppWarp::ResultCode::bad_request)
    {
        CCLOG("onConnectDone .. FAILED with bad request..session=%d\n", AppWarp::AppWarpSessionID);
    }
    else
    {
        CCLOG("onConnectDone .. FAILED with reasonCode=%d..session=%d\n", code, AppWarp::AppWarpSessionID);
    }
}


void ChooseRoomScene::onGetAllRoomsDone(AppWarp::liveresult result)
{
    AppWarp::Client *warpClientRef;
    warpClientRef = AppWarp::Client::getInstance();
    CCLOG("onGetAllRoomsDone : %d", result.result);
    for(std::vector<int>::size_type i = 0; i != result.list.size(); i++){
        std::cout << result.list[i] << std::endl;
        warpClientRef->getLiveRoomInfo(result.list[i]);
    }
}

void ChooseRoomScene::onGetLiveRoomInfoDone(AppWarp::liveroom result)
{
    std::cout << result.rm.name << std::endl;
//    CCLOG("%s", result.rm.name);
}



