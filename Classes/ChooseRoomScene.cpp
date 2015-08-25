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
    
    std::vector<String>  _array;
    for (int i = 0; i < 20; i++) {
        _array.push_back( StringUtils::format("listView_item_%d",i));
    }
    
    ListView* listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setTouchEnabled(true);
    listView->setBounceEnabled(true);
    listView->setBackGroundImage("helloworld.png");
    listView->setBackGroundImageScale9Enabled(true);
    listView->setSize(Size(480, 260));
    listView->setPosition(Point(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
    
    this->addChild(listView, 1);
    
    
    
    //create model
    Button* default_button = Button::create("CloseNormal.png","CloseSelected.png");
    default_button->setName("Title Button");
    
    Layout* default_item = Layout::create();
    default_item->setTouchEnabled(true);
    default_item->setSize(default_button->getSize());
    default_button->setPosition(Point(default_item->getSize().width / 2.0f, default_item->getSize().height / 2.0f));
    default_item->addChild(default_button);
    
    listView->setItemModel(default_item);
    
    
    
    ssize_t count = _array.size();
    for (int i = 0; i < count / 4; ++i) {
        listView->pushBackDefaultItem();
    }
    
    //insert default item
    for (int i = 0; i < count / 4; ++i) {
        listView->insertDefaultItem(0);
    }
    
    //add custom item
    
    for (int i = 0; i < count / 4; ++i) {
        Button* custom_button = Button::create("CloseNormal.png","CloseSelected.png");
        custom_button->setName("Title Button");
        custom_button->setScale9Enabled(true);
        custom_button->setSize(default_button->getSize());
        
        Layout* custom_item = Layout::create();
        custom_item->setSize(custom_button->getSize());
        custom_button->setPosition(Point(custom_item->getSize().width / 2.0f, custom_item->getSize().height / 2.0f));
        custom_item->addChild(custom_button);
        listView->pushBackCustomItem(custom_item);
    }
    
    
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



