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
    Multiplayer::getInstance()->setNotificationListener(this);
    
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
    this->background = node->getChildByName<Sprite*>("background");
    this->addChild(node);
    
    
    // TODO: Change it
    //    if(Multiplayer::getInstance()->getUsername().compare(Multiplayer::getInstance()->getOpponentUsername()) < 0)
    if(true)
    {
        this->player = new Fighter(background->getChildByName<Sprite*>("left"), "character1");
        this->opponent = new Fighter(background->getChildByName<Sprite*>("right"), "character1");
    }
//    else
//    {
//        player = new Fighter(background->getChildByName<Sprite*>("left"), "character1");
//        opponent = new Fighter(background->getChildByName<Sprite*>("right"), "character1");
//    }
    player->setOpponent(opponent);
    opponent->setOpponent(player);
//
    this->camera = new Camera2d(player, opponent, background);
//
//    
    this->createBackgroundAnimation();
    this->createJoystick();
    this->buttonA = createButtons(GAME_PLAY_SCENE_BUTTON_A_NORMAL, GAME_PLAY_SCENE_BUTTON_A_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_A_X, GAME_PLAY_SCENE_BUTTON_A_Y));
    this->buttonB = createButtons(GAME_PLAY_SCENE_BUTTON_B_NORMAL, GAME_PLAY_SCENE_BUTTON_B_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_B_X, GAME_PLAY_SCENE_BUTTON_B_Y));
    this->buttonC = createButtons(GAME_PLAY_SCENE_BUTTON_C_NORMAL, GAME_PLAY_SCENE_BUTTON_C_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_C_X, GAME_PLAY_SCENE_BUTTON_C_Y));
    this->buttonD = createButtons(GAME_PLAY_SCENE_BUTTON_D_NORMAL, GAME_PLAY_SCENE_BUTTON_D_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_D_X, GAME_PLAY_SCENE_BUTTON_D_Y));
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
    
    if (buttonA->getIsActive())
    {
        player->punch1();
    }
    
    if (buttonB->getIsActive())
    {
        player->punch2();
    }
    
    if (buttonC->getIsActive())
    {
        player->kick1();
    }
    
    if (buttonD->getIsActive())
    {
        player->kick2();
    }
    
    if(velocity != Point(0,0))
    {
        // stand move forward
        if (velocity.y > -0.38268f && velocity.y < 0.38268f && velocity.x > 0.92387f)
        {
            player->stand_moveforward();
        }
        // stand move back
        if (velocity.y > -0.38268f && velocity.y < 0.38268f && velocity.x < -0.92387f)
        {
            player->stand_moveback();
        }
        // stand jump
        if (velocity.y > 0.38268f && velocity.x < 0.92387f && velocity.x > -0.92387f)
        {
            player->stand_jump(velocity);
        }
        
        if (velocity.y < -0.38268f && velocity.y > -0.92387f && velocity.x > 0.38268f && velocity.x < 0.92387f)
        {
            player->squat_moveforward();
        }
        
        if (velocity.y < -0.38268f && velocity.y > -0.92387f && velocity.x < -0.38268f && velocity.x > -0.92387f)
        {
            player->squat_moveback();
        }
        
        if (velocity.y < -0.92387f && velocity.x > -0.38268f && velocity.x < 0.38268f)
        {
            player->squat_down();
        }
        
        
        
    }
    else{
        player->stand();
    }
    
    player->update(dt);
    camera->update(dt);
    
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
    joystckbase->setBackgroundSprite(Sprite::create(GAME_PLAY_SCENE_JOYSTICK_BASE));
    joystckbase->setThumbSprite(Sprite::create(GAME_PLAY_SCENE_JOYSTICK));
    joystckbase->setJoystick(joystick);
    joystckbase->setPosition(joystickBasePosition);
    this->addChild(joystckbase);

}

SneakyButton* GamePlayScene::createButtons(std::string normal, std::string pressed, Vec2 pos)
{
    Size visibleSize = Director::getInstance()->getWinSize();
    // button A
    auto buttonBase = SneakyButtonSkinnedBase::create();
    auto button = new SneakyButton();
    
    auto buttonRect = Rect(0, 0, 30.f, 30.f);
    auto buttonPos = Point(visibleSize.width * pos.x, visibleSize.height * pos.y);
    
    button->initWithRect(buttonRect);
    button->setIsHoldable(true);
    buttonBase->setPosition(buttonPos);
    buttonBase->setDefaultSprite(CCSprite::create(normal));
    buttonBase->setActivatedSprite(CCSprite::create(normal));
    buttonBase->setPressSprite(CCSprite::create(pressed));
    buttonBase->setButton(button);
    this->addChild(buttonBase);
    return button;
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
