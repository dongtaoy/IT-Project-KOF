//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseRoomScene.h"

USING_NS_CC;

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
    
    
    //TODO: help text
    
    
    Label *label = Label::createWithTTF("ChooseRoomScene", "fonts/Marker Felt.ttf", 10);
    label->setColor(Color3B::WHITE);
    label->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label, 1);
    
    // Back Button
    Label *backLabel = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 15);
    backLabel->setColor(Color3B::WHITE);
    MenuItemLabel *backButton = MenuItemLabel::create(backLabel, CC_CALLBACK_1(ChooseRoomScene::GotoMainMenuScene, this));
    backButton->setPosition(origin.x + visibleSize.width * 1 / 10, origin.y + visibleSize.height * 3 / 4);
    Menu *backMenu = Menu::create(backButton, NULL);
    backMenu->setPosition(Point::ZERO);
    this->addChild(backMenu, 1);
    
    
    connectToAppWarp();
    
    cocos2d::ui::ListView *listview=cocos2d::ui::ListView::create();
    
    
    return true;
}

void ChooseRoomScene::GotoMainMenuScene(Ref* pSender)
{
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
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



