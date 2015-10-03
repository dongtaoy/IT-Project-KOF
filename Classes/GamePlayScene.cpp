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

    
    auto node = CSLoader::createNode("GamePlay.csb");
    node->getChildByName<Button*>("pause")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::PauseClicked, this));
    this->background = node->getChildByName<Sprite*>("background");
    this->addChild(node);
    
//    auto tempNode = this->getChildByName(GAME_PLAY_SCENE);
//    auto countDown = tempNode->getChildByName<Text*>("countDown");
//    countDown->setString(std::to_string(10));
    
    
//     TODO: WITH MULTIPLAYER
    if(Multiplayer::getInstance()->getUsername().compare(Multiplayer::getInstance()->getOpponentUsername()) < 0)
    {
        this->player = new Fighter(background->getChildByName<Sprite*>("right"), Multiplayer::getInstance()->getUserCharacter());
        node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % Multiplayer::getInstance()->getUserCharacter()).str(), Widget::TextureResType::PLIST);
        
        this->opponent = new Fighter(background->getChildByName<Sprite*>("left"), Multiplayer::getInstance()->getOpponentCharacter());
        node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % Multiplayer::getInstance()->getOpponentCharacter()).str(), Widget::TextureResType::PLIST);
    
    }
    else
    {
        this->player = new Fighter(background->getChildByName<Sprite*>("left"), Multiplayer::getInstance()->getUserCharacter());
        node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % Multiplayer::getInstance()->getUserCharacter()).str(), Widget::TextureResType::PLIST);
        
        this->opponent = new Fighter(background->getChildByName<Sprite*>("right"), Multiplayer::getInstance()->getOpponentCharacter());
        node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % Multiplayer::getInstance()->getOpponentCharacter()).str(), Widget::TextureResType::PLIST);
    }
    

    // TODO: WITHOUT MULTIPLAYER
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(BACKGROUND_SPRITE_PATH) % "background1" ).str());
//    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(BACKGROUND_ANIMATION_PATH) % "background1" ).str());
//
//    
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTER_SPRITE_PATH) % "character1").str());
//    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTER_ANIMATION_PATH) % "character1").str());
//    this->player = new Fighter(background->getChildByName<Sprite*>("left"), "character1");
//    node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % "character1").str(), Widget::TextureResType::PLIST);
//    this->opponent = new Fighter(background->getChildByName<Sprite*>("right"), "character1");
//    node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % "character1").str(), Widget::TextureResType::PLIST);
//
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTER_SPRITE_PATH) % "character5").str());
//    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTER_ANIMATION_PATH) % "character5").str());
//    this->player = new Fighter(background->getChildByName<Sprite*>("left"), "character5");
//    node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % "character5").str(), Widget::TextureResType::PLIST);
//    this->opponent = new Fighter(background->getChildByName<Sprite*>("right"), "character5");
//    node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % "character5").str(), Widget::TextureResType::PLIST);
//
//
//    
    
    
    player->setOpponent(opponent);
    opponent->setOpponent(player);

    
    
    
    
    
    this->camera = new Camera2d(player, opponent, background);
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
//    this->startCountDown();
}

void GamePlayScene::startCountDown()
{
    if (!isCountDownStart){
        isCountDownStart = true;
        this->schedule(schedule_selector(GamePlayScene::countDownTask), 1.0f);
    }
}

void GamePlayScene::countDownTask(float dt){
    auto node = this->getChildByName(GAME_PLAY_SCENE);
    auto countDown = node->getChildByName<Text*>("countDown");
    int value = std::atoi(countDown->getString().c_str()) - 1;
    
    if (value > 0){
        countDown->setString(std::to_string(value));
    }else{
        endCountDown();
        this->player->win();
        this->opponent->die();
    }
}

void GamePlayScene::endCountDown(){
    if (isCountDownStart){
        isCountDownStart = false;
        this->unschedule(schedule_selector(GamePlayScene::countDownTask));
    }
}

void GamePlayScene::processCommand(command_t cmd)
{
    if(Multiplayer::isCommandValid(MP_GAME_PLAY_SCNE, cmd))
    {
        switch (cmd.operation) {
            case OP_GPS_ACTION_2_STAND_PUNCH1:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->punch1();
                else
                    opponent->punch1();
                break;
            case OP_GPS_ACTION_2_STAND_PUNCH2:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->punch2();
                else
                    opponent->punch2();
                break;
                
            case OP_GPS_ACTION_2_STAND_KICK1:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->kick1();
                else
                    opponent->kick1();
                break;
                
            case OP_GPS_ACTION_2_STAND_KICK2:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->kick2();
                else
                    opponent->kick2();
                break;
            case OP_GPS_ACTION_1_STAND:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->stand();
                else
                    opponent->stand();
                break;
                
            case OP_GPS_ACTION_1_STAND_MOVEFORWARD:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->stand_moveforward(atoi(cmd.properties.c_str()));
                else
                    opponent->stand_moveforward(atoi(cmd.properties.c_str()));
                break;
                
            case OP_GPS_ACTION_1_STAND_MOVEBACK:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->stand_moveback(atoi(cmd.properties.c_str()));
                else
                    opponent->stand_moveback(atoi(cmd.properties.c_str()));
                break;
                
            case OP_GPS_ACTION_2_STAND_JUMP:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->stand_jump(atoi(cmd.properties.c_str()));
                else
                    opponent->stand_jump(atoi(cmd.properties.c_str()));
                break;
                
            case OP_GPS_ACTION_1_SQUAT_DOWN:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->squat_down();
                else
                    opponent->squat_down();
                break;
            
            case OP_GPS_ACTION_1_SQUAT_MOVEFORWARD:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->squat_moveforward();
                else
                    opponent->squat_moveforward();
                break;
                
            case OP_GPS_ACTION_1_SQUAT_MOVEBACK:
                if (Multiplayer::isPlayer(cmd.sender))
                    player->squat_moveback();
                else
                    opponent->squat_moveback();
                break;
                
            default:
                break;
        }
    }
}


void GamePlayScene::update(float dt)
{
    auto point = joystick->getVelocity();
    auto angle = GameHelper::vectorToDegree(point);
    
    if (!Multiplayer::getInstance()->isCommandsEmpty())
    {
        processCommand(Multiplayer::getInstance()->popCommands());
    }
//
    
    
    int operation = 0;
    std::string properties;
    
    // stand move forward
    if (angle > 337.5f || angle <  22.5f)
    {
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_STAND_MOVEFORWARD);
        operation = OP_GPS_ACTION_1_STAND_MOVEFORWARD;
        properties = std::to_string(int(player->getPosition().x + ACTION_MOVE_SPEED));
//        player->stand_moveforward();
    }
    
    // jump
    if (angle >  22.5f && angle < 157.5f)
    {
        int distance = point.x * 200;
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_JUMP, std::to_string(distance));
        
        operation = OP_GPS_ACTION_2_STAND_JUMP;
        properties = std::to_string(distance);
//        player->stand_jump(point.x * 200);
    }
    
    // stand move back
    if (angle > 157.5f && angle < 202.5f)
    {
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_STAND_MOVEBACK);
        
        operation = OP_GPS_ACTION_1_STAND_MOVEBACK;
        properties = std::to_string(int(player->getPosition().x - ACTION_MOVE_SPEED));
//        player->stand_moveback();
    }
    
    
    
    // squat moveback
    if (angle > 202.5f && angle < 247.5f)
    {
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_MOVEBACK);
        
        operation = OP_GPS_ACTION_1_SQUAT_MOVEBACK;
//        player->squat_moveback();
    }
    
    // squat
    if (angle > 247.5f && angle < 292.5f)
    {
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_DOWN);

        operation = OP_GPS_ACTION_1_SQUAT_DOWN;
//        player->squat_down();
    }
    
    if (angle > 292.5f && angle < 337.5f)
    {
        operation = OP_GPS_ACTION_1_SQUAT_MOVEFORWARD;
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_MOVEFORWARD);s
//        player->squat_moveforward();
    }
//    
    if (std::isnan(angle))
    {
        operation = OP_GPS_ACTION_1_STAND;
//        player->stand();
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_STAND);
    }
    
    
    if (buttonA->getIsActive())
    {
        operation = OP_GPS_ACTION_2_STAND_PUNCH1;
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_PUNCH1);
//                player->punch1();
    }
    
    if (buttonB->getIsActive())
    {
        operation = OP_GPS_ACTION_2_STAND_PUNCH2;
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_PUNCH2);
//                player->punch2();
    }
    
    if (buttonC->getIsActive())
    {
        operation = OP_GPS_ACTION_2_STAND_KICK1;
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_KICK1);
//                player->kick1();
    }
    
    if (buttonD->getIsActive())
    {
        operation = OP_GPS_ACTION_2_STAND_KICK2;
//        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_KICK2);
//                player->kick2();
    }
    
    
    accumilatedTime = accumilatedTime + dt * 1000;
    if (accumilatedTime > GAME_FRAME_DELAY) {
        if (operation && player->isActionStoppable())
        {
            
            std::string message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, operation, properties);
            if (!(operation == prevOperation && prevOperation == OP_GPS_ACTION_1_STAND))
            {
                prevOperation = operation;
                Multiplayer::sendChat(message);
            }
        }
        accumilatedTime = accumilatedTime - GAME_FRAME_DELAY;
    }
//    CCLOG("player %f OPPONENT %f diff %f",  player->getPosition().x, opponent->getPosition().x, std::abs(player->getPosition().x-opponent->getPosition().x));
//    player->update(dt);
//    opponent->update(dt);
//    player->stand();
//    opponent->stand();
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
    buttonBase->setDefaultSprite(Sprite::create(normal));
    buttonBase->setActivatedSprite(Sprite::create(normal));
    buttonBase->setPressSprite(Sprite::create(pressed));
    buttonBase->setButton(button);
    this->addChild(buttonBase);
    return button;
}

void GamePlayScene::createBackgroundAnimation()
{
    auto background = this->getChildByName("GamePlayScene")->getChildByName("background");
    CCLOG("%f %f", background->getBoundingBox().size.width, background->getBoundingBox().size.height);
    
//     TODO: WITH MULTIPLAYER
    auto animation = AnimationCache::getInstance()->getAnimation(Multiplayer::getInstance()->getBackground());
    // TODO: WITHOUT MULTIPLAYER
//    auto animation = AnimationCache::getInstance()->getAnimation("background1");
    
    Size targetSize = Size( 2305.0f, 750.0f );
    Size backgroundSize = background->getContentSize();
    background->setScale( ( targetSize.width / backgroundSize.width ), ( targetSize.height / backgroundSize.height ) );
    
    
    
    background->runAction(RepeatForever::create(Animate::create(animation)));

}




void GamePlayScene::onUnsubscribeRoomDone()
{
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "leaving room...", 60.0f);
}

void GamePlayScene::onLeaveRoomDone()
{
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "DONE...", 100.0f);
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

