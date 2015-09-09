//
//  GamePlayScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 6/09/2015.
//
//

#include "GamePlayScene.h"
USING_NS_CC;
using namespace ui;

Scene* GamePlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Multiplayer::getInstance()->resetConnectionRequestListener();
    
    auto node = CSLoader::createNode("GamePlay.csb");
    node->getChildByName<Button*>("pause")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::PauseClicked, this));
    
    
    
    this->addChild(node);
    
    
    createJoystick();
    this->scheduleUpdate();
    return true;
}


void GamePlayScene::update(float dt)
{
    if(joystick->getVelocity() != Point(0,0))
        CCLOG("%f %f", joystick->getVelocity().x, joystick->getVelocity().y);
    
//    CCLOG("%f", dt);
}

void GamePlayScene::PauseClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        Multiplayer::getInstance()->unsubsribeRoom(this);
    }
}

void GamePlayScene::createJoystick()
{
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    int joystickOffsetX = 160;
    int joystickOffsetY = 140;
    
    Rect joystickBaseDimensions = Rect(0, 0, 30.0f, 30.0f);
    Point joystickBasePosition  = Point(origin.x + (joystickBaseDimensions.size.width / 2) + joystickOffsetX, origin.y + (joystickBaseDimensions.size.height / 2) + joystickOffsetY);
    
    SneakyJoystickSkinnedBase* joystckbase = SneakyJoystickSkinnedBase::create();
    joystick = new SneakyJoystick();
    joystick->initWithRect(joystickBaseDimensions);
    joystckbase->setBackgroundSprite(Sprite::create("Resources/joystick.png"));
    joystckbase->setThumbSprite(Sprite::create("Resources/joystick_button.png"));
    joystckbase->setJoystick(joystick);
    joystckbase->setPosition(joystickBasePosition);
    this->addChild(joystckbase);

}


void GamePlayScene::onChatReceived(AppWarp::chat message)
{
    CCLOG("in game play %s", message.chat.c_str());
}


void GamePlayScene::onUnsubscribeRoomDone(AppWarp::room event)
{
    if(event.result == AppWarp::ResultCode::success)
    {
        Multiplayer::getInstance()->leaveRoom(this);
    }
}

void GamePlayScene::onLeaveRoomDone(AppWarp::room event)
{
    if(event.result == AppWarp::ResultCode::success)
    {
        
    }
}
