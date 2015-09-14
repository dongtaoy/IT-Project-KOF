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
//    Multiplayer::getInstance()->resetAllListener();
    
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
    LoadingLayer::StartCountDown(static_cast<Node*>(this), cocos2d::CallFunc::create(std::bind(&GamePlayScene::startGame, this)));
    // TODO: UNCOMMENT
    // Multiplayer::getInstance()->setNotificationListener(this);
    
    // TODO:: DELETE
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(BACKGROUND_SPRITE_PATH) % "background2" ).str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(BACKGROUND_ANIMATION_PATH) % "background2" ).str());
    
    // TODO:: DELETE
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTER_SPRITE_PATH) % "character1").str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTER_ANIMATION_PATH) % "character1").str());
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTER_SPRITE_PATH) % "character6").str());
//    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTER_ANIMATION_PATH) % "character6").str());
    
    auto node = CSLoader::createNode("GamePlay.csb");
    node->getChildByName<Button*>("pause")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::PauseClicked, this));
    node->getChildByName<Button*>("buttonA")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::buttonAClicked, this));
    node->getChildByName<Button*>("buttonB")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::buttonBClicked, this));
    node->getChildByName<Button*>("buttonC")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::buttonCClicked, this));
    node->getChildByName<Button*>("buttonD")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::buttonDClicked, this));
    this->background = node->getChildByName<Sprite*>("background");
    this->addChild(node);
    
    
    // TODO: Change it
    //    if(Multiplayer::getInstance()->getUsername().compare(Multiplayer::getInstance()->getOpponentUsername()) < 0)
    if(true)
    {
        player = new Fighter(background->getChildByName<Sprite*>("left"), "character1");
        opponent = new Fighter(background->getChildByName<Sprite*>("right"), "character1");
    }
//    else
//    {
//        player = new Fighter(background->getChildByName<Sprite*>("left"), "character1");
//        opponent = new Fighter(background->getChildByName<Sprite*>("right"), "character1");
//    }
    player->setOpponent(opponent);
    opponent->setOpponent(player);
//
    camera = new Camera2d(player, opponent, background);
//
//    
    createBackgroundAnimation();
    createJoystick();
//    createButtons();
    this->scheduleUpdate();
    return true;
}

void GamePlayScene::startGame()
{
    LoadingLayer::RemoveLoadingLayer(static_cast<Node*>(this));
    CCLOG("GAME STARTED");
}

void GamePlayScene::update(float dt)
{
    Point velocity = joystick->getVelocity();
    
    
    if(velocity != Point(0,0))
    {
//        CCLOG("%f %f", velocity.x, velocity.y);
        // move
        if(velocity.y > -0.38268f && velocity.y < 0.38268f && velocity.x > 0)
        {
            player->moveForward();
        }
//        // move back
        if(velocity.y > -0.38268f && velocity.y < 0.38268f && velocity.x < 0)
        {
            player->moveBack();
        }
        // jump up
        if(velocity.y > 0.38268f)
        {
            player->jump(velocity);
        }
    }
    else{
        player->stand();
    }
    
    player->update(dt);
    camera->update(dt);
    
}

void GamePlayScene::buttonAClicked(Ref*, ui::Widget::TouchEventType)
{
    player->punch1();
}

void GamePlayScene::buttonBClicked(Ref*, ui::Widget::TouchEventType)
{
    player->punch2();
}

void GamePlayScene::buttonCClicked(Ref*, ui::Widget::TouchEventType)
{
    player->kick1();
}

void GamePlayScene::buttonDClicked(Ref*, ui::Widget::TouchEventType)
{
    player->kick2();
}


void GamePlayScene::PauseClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        auto node = CSLoader::createNode("PauseLayer.csb");
        this->addChild(node);
        node->getChildByName<Button*>("buttonResume")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::ResumeClicked, this));
        node->getChildByName<Button*>("buttonMenu")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::MenuClicked, this));
    }
}

void GamePlayScene::ResumeClicked(Ref* pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        this->removeChildByName("PauseLayer");
    }
}

void GamePlayScene::MenuClicked(Ref* pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "unsubsribing room...", 30.0f);
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

void GamePlayScene::createButtons()
{
    
}

void GamePlayScene::createBackgroundAnimation()
{
    auto background = this->getChildByName("GamePlayScene")->getChildByName("background");
    auto animation = AnimationCache::getInstance()->getAnimation("background2");
    background->runAction(RepeatForever::create(Animate::create(animation)));
}


void GamePlayScene::onChatReceived(AppWarp::chat message)
{
    if (message.sender.compare(Multiplayer::getInstance()->getUsername()))
    {
        
//        std::vector<std::string> command = Multiplayer::exractMessage(message.chat);
//        
//        switch (std::atoi(command.at(1).c_str())) {
//            case OP_GPS_USER_LEAVED:
//                
//                
//                
//                
//                break;
//                
//                
//            default:
//                break;
//        }
    }
    CCLOG("in game play %s", message.chat.c_str());
}

void GamePlayScene::onUserLeftRoom(AppWarp::room, std::string name)
{
    
    if (name.compare(Multiplayer::getInstance()->getUsername()))
    {
        MessageBox("Opponent Left", "Opponent Left");
    }
}

void GamePlayScene::onUnsubscribeRoomDone(AppWarp::room event)
{
    if(event.result == AppWarp::ResultCode::success)
    {
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "leaving room...", 60.0f);
        Multiplayer::getInstance()->leaveRoom(this);
    }
}

void GamePlayScene::onLeaveRoomDone(AppWarp::room event)
{
    if(event.result == AppWarp::ResultCode::success)
    {
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "DONE...", 100.0f);
        auto scene = MainMenuScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}
