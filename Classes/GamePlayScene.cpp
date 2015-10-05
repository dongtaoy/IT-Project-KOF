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
    
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
    //set the gravity (0.0f, -98.0f) is the default value. change to -200 for y axis is perfect value
    scene->getPhysicsWorld()->setGravity( Vec2(GRAVITY_X, GRAVITY_Y));
    //    scene->getPhysicsWorld()->setAutoStep(true);

    
    
    
    // 'layer' is an autorelease object
    auto layer = GamePlayScene::create();
    layer->setWorld(scene->getPhysicsWorld());
    
    
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
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //stop backgorund music
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    //    preload the fight background music
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/Fightmusic.mp3");
    //    play the fight background music
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/Fightmusic.mp3",true);
    
    
    auto node = CSLoader::createNode("GamePlay.csb");
    
    node->getChildByName<Button*>("pause")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::PauseClicked, this));
    this->background = node->getChildByName<Sprite*>("background");
    this->addChild(node);
    
//    auto tempNode = this->getChildByName(GAME_PLAY_SCENE);
//    auto countDown = tempNode->getChildByName<Text*>("countDown");
//    countDown->setString(std::to_string(10));
    auto leftHp = this->getChildByName("GamePlayScene")->getChildByName<LoadingBar*>("playerLeftHP");
    auto rightHp = this->getChildByName("GamePlayScene")->getChildByName<LoadingBar*>("playerRightHP");
    
    
    
    /////////////////////////////////////////////////////////////////
    
    auto size = node->getBoundingBox().size;
    auto edgeNode = Node::create();
    auto physicsBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + visibleSize.height * 0.03));
    edgeNode->setPhysicsBody(physicsBody);
    this->addChild(edgeNode);
    /////////////////////////////////////////////////////////////////

//     TODO: WITH MULTIPLAYER
    if(Multiplayer::getInstance()->getUsername().compare(Multiplayer::getInstance()->getOpponentUsername()) < 0)
    {
        this->player = new Fighter(background->getChildByName<Sprite*>("right"), rightHp, Multiplayer::getInstance()->getUserCharacter(), false);
        node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % Multiplayer::getInstance()->getUserCharacter()).str(), Widget::TextureResType::PLIST);
        
        this->opponent = new Fighter(background->getChildByName<Sprite*>("left"), leftHp, Multiplayer::getInstance()->getOpponentCharacter(), true);
        node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % Multiplayer::getInstance()->getOpponentCharacter()).str(), Widget::TextureResType::PLIST);
    
    }
    else
    {
        this->player = new Fighter(background->getChildByName<Sprite*>("left"), leftHp, Multiplayer::getInstance()->getUserCharacter(), true);
        node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % Multiplayer::getInstance()->getUserCharacter()).str(), Widget::TextureResType::PLIST);
        
        this->opponent = new Fighter(background->getChildByName<Sprite*>("right"), rightHp, Multiplayer::getInstance()->getOpponentCharacter(), false);
        node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % Multiplayer::getInstance()->getOpponentCharacter()).str(), Widget::TextureResType::PLIST);
    }
    
//     TODO: WITHOUT MULTIPLAYER
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(BACKGROUND_SPRITE_PATH) % "background1" ).str());
//    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(BACKGROUND_ANIMATION_PATH) % "background1" ).str());
//
//
//    
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTER_SPRITE_PATH) % "character3").str());
//    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTER_ANIMATION_PATH) % "character3").str());
//    this->player = new Fighter(background->getChildByName<Sprite*>("right"), rightHp, "character3", false);
//    node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % "character3").str(), Widget::TextureResType::PLIST);
//    this->opponent = new Fighter(background->getChildByName<Sprite*>("left"), leftHp, "character3", true);
//    node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % "character3").str(), Widget::TextureResType::PLIST);

    


    
    
    player->setOpponent(opponent);
    opponent->setOpponent(player);

    
    
    //get width and height for two characters
//    float x1 = player->getSprite()->getBoundingBox().size.width;
//    float y1 = player->getSprite()->getBoundingBox().size.height;
//    float x2 = opponent->getSprite()->getBoundingBox().size.width;
//    float y2 = opponent->getSprite()->getBoundingBox().size.height;
//    
//    
    //get the distance between two characters
//    float characterDistance = opponent->getSprite()->getPositionX() - player->getSprite()->getPositionX();
    //add physci edge box for characters
//    addEdgeBoxForCharacter(player->getSprite(),x1,y1,Character1_bitmask);
//    addEdgeBoxForCharacter(opponent->getSprite(),x2,y2,Character2_bitmask);
    
  
    
    
    
    
    this->camera = new Camera2d(player, opponent, background);
    this->createBackgroundAnimation();
    this->createJoystick();
    this->buttonA = createButtons(GAME_PLAY_SCENE_BUTTON_A_NORMAL, GAME_PLAY_SCENE_BUTTON_A_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_A_X, GAME_PLAY_SCENE_BUTTON_A_Y));
    this->buttonB = createButtons(GAME_PLAY_SCENE_BUTTON_B_NORMAL, GAME_PLAY_SCENE_BUTTON_B_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_B_X, GAME_PLAY_SCENE_BUTTON_B_Y));
    this->buttonC = createButtons(GAME_PLAY_SCENE_BUTTON_C_NORMAL, GAME_PLAY_SCENE_BUTTON_C_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_C_X, GAME_PLAY_SCENE_BUTTON_C_Y));
    this->buttonD = createButtons(GAME_PLAY_SCENE_BUTTON_D_NORMAL, GAME_PLAY_SCENE_BUTTON_D_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_D_X, GAME_PLAY_SCENE_BUTTON_D_Y));
    this->scheduleUpdate();
    
    
    
    //add event listener
//    auto contactListener = EventListenerPhysicsContact::create();
//    contactListener->onContactBegin = CC_CALLBACK_1(GamePlayScene::onContactBegin, this);
//    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

//    auto contactListenr1 = EventListenerCustom::create(characterTooClose, characterTooClose(characterDistance,closeDistance));
//    auto contactListener1 = EventListenerCustom::create(character, characterTooClose(characterDistance, closeDistance));
    
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
        if (!Multiplayer::isPlayer(cmd.sender))
        {
        switch (cmd.operation) {
            case OP_GPS_ACTION_2_STAND_PUNCH1:
                opponent->setPosition(Multiplayer::extractPos(cmd.properties));
                opponent->punch1();
                break;
            case OP_GPS_ACTION_2_STAND_PUNCH2:
                opponent->setPosition(Multiplayer::extractPos(cmd.properties));
                opponent->punch2();
                break;
                
            case OP_GPS_ACTION_2_STAND_KICK1:
                opponent->setPosition(Multiplayer::extractPos(cmd.properties));
                opponent->kick1();
                break;
                
            case OP_GPS_ACTION_2_STAND_KICK2:
                opponent->setPosition(Multiplayer::extractPos(cmd.properties));
                opponent->kick2();
                break;
            
            case OP_GPS_ACTION_1_STAND:
                opponent->setPosition(Multiplayer::extractPos(cmd.properties));
                opponent->stand();
                break;
                
            case OP_GPS_ACTION_1_STAND_MOVEFORWARD:
                opponent->stand_moveforward();
                break;
                
            case OP_GPS_ACTION_1_STAND_MOVEBACK:
                opponent->stand_moveback();
                break;
                
            case OP_GPS_ACTION_2_STAND_JUMP:
                opponent->stand_jump(atoi(GameHelper::split(cmd.properties, '%').at(0).c_str()));
                break;
                
            case OP_GPS_ACTION_1_SQUAT_DOWN:
                    opponent->setPosition(Multiplayer::extractPos(cmd.properties));
                    opponent->squat_down();
                break;
            
            case OP_GPS_ACTION_1_SQUAT_MOVEFORWARD:
                    opponent->squat_moveforward();
                break;
                
            case OP_GPS_ACTION_1_SQUAT_MOVEBACK:
                    opponent->squat_moveback();
                break;
                
            case OP_GPS_ACTION_3_HEALTHCHANGED:
                    opponent->setHealthPercentage(std::atof(GameHelper::split(cmd.properties, '%').at(0).c_str()));
                break;
            default:
                break;
        }
        }
    }
}


void GamePlayScene::update(float dt)
{
    auto point = joystick->getVelocity();
    auto angle = GameHelper::vectorToDegree(point);
    
    if (!Multiplayer::getInstance()->isCommandsEmpty())
    {
        if (opponent->isActionStoppable())
            processCommand(Multiplayer::getInstance()->popCommands());
    }
    
    auto pos = player->getPosition();
    std::string properties = Multiplayer::buildProperties({std::to_string(pos.x), std::to_string(pos.y)});
    
    std::string message;
    
    // stand move forward
    if (angle > 337.5f || angle <  22.5f)
    {
        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_STAND_MOVEFORWARD);
        player->stand_moveforward();
    }
    
    // stand move back
    if (angle > 157.5f && angle < 202.5f)
    {
        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_STAND_MOVEBACK);
        player->stand_moveback();
    }
    
    
    // jump
    if (angle >  22.5f && angle < 157.5f)
    {
        if (player->isActionStoppable())
        {
            int distance = point.x * ACTION_MOVE_SPEED;
            message = Multiplayer::buildMessage(
                                                MP_GAME_PLAY_SCNE,
                                                OP_GPS_ACTION_2_STAND_JUMP,
                                                Multiplayer::buildProperties({std::to_string(distance)}));
            player->stand_jump(distance);
        }
    }
    
    
    
    // squat moveback
    if (angle > 202.5f && angle < 247.5f)
    {
        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_MOVEBACK);
        player->squat_moveback();
    }
    
    // squat
    if (angle > 247.5f && angle < 292.5f)
    {
        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_DOWN, properties);
        player->squat_down();
    }
    
    if (angle > 292.5f && angle < 337.5f)
    {
        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_MOVEFORWARD);
        player->squat_moveforward();
    }
    
    
    
    
    if (buttonA->getIsActive())
    {
        if (player->isActionStoppable())
        {
            message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_PUNCH1, properties);
            player->punch1();
        }
    }
    
    if (buttonB->getIsActive())
    {
        if (player->isActionStoppable())
        {
            message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_PUNCH2, properties);
            player->punch2();
        }
    }
    
    if (buttonC->getIsActive())
    {
        if (player->isActionStoppable())
        {
            message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_KICK1, properties);
            player->kick1();
        }
    }
    
    if (buttonD->getIsActive())
    {
        if (player->isActionStoppable())
        {
            message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_KICK2, properties);
            player->kick2();
        }
    }
    if (std::isnan(angle))
    {
        if (player->isActionStoppable()) {
            message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_STAND, properties);
            player->stand();
        }
    }
    
    if (player->getIsHealthChanged())
    {
        player->setIsHealthChanged(false);
        auto p = Multiplayer::buildProperties({std::to_string(player->getHealthPercentage())});
        message = Multiplayer::buildMessage(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_3_HEALTHCHANGED,p);
    }
    
    
    if (player->getIsDie() || opponent->getIsDie())
    {
        MenuClicked(nullptr, Widget::TouchEventType::ENDED);
        this->unscheduleUpdate();
//        GKHWrapperCpp gkh;
//        gkh.submitScoreToCatagory(<#int64_t s#>, co);
        
//        LoadingLayer::ADD
    }

    
    player->update(dt);
    opponent->update(dt);
    camera->update(dt);
    if(message.compare(""))
    {
        command_t cmd = Multiplayer::exractMessage(message);
        if (cmd.operation == OP_GPS_ACTION_1_STAND && prevOperation == OP_GPS_ACTION_1_STAND)
        {
//            CCLOG("innnnnn");
            if (accumilatedTime > 2000) {
//                CCLOG("sent");
                accumilatedTime = 0;
                Multiplayer::sendChat(message);
            }
            accumilatedTime = accumilatedTime + dt * 1000;
        }
        else
        {
            accumilatedTime = 0;
            Multiplayer::sendChat(message);
        }
        prevOperation = cmd.operation;
    }
    
    
    
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
//    auto animation = AnimationCache::getInstance()->getAnimation(Multiplayer::getInstance()->getBackground());
    // TODO: WITHOUT MULTIPLAYER
    auto animation = AnimationCache::getInstance()->getAnimation("background1");
    
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
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/backgroundmusic.mp3");
}


void GamePlayScene::addEdgeBoxForCharacter(Node* sprite, float x, float y, int bitmask)
{
    
    //    sprite->setTag(1);
    //    body->setDynamic(false);
    //    this->addChild(sprite);
    
    //add physic body for characters
//    auto body = PhysicsBody::createBox(Size(x - Character_Edge_Offset, y), PhysicsMaterial(Physic_Box_Density, Physic_Box_Restitution, Physic_Box_Friction));
//    sprite->setPhysicsBody(body);
//    
//    //set colission detect
//    body->setCollisionBitmask(bitmask);
//    body->setContactTestBitmask(true);
//    
//    //keep character still
//    body->setRotationEnable(false);
//    body->setGravityEnable(true);
    
    
}

bool GamePlayScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    // check if the bodies have collided
//    if ( ( Character1_bitmask == a->getCollisionBitmask() && Character2_bitmask == b->getCollisionBitmask() ) || ( Character2_bitmask == a->getCollisionBitmask() && Character1_bitmask == b->getCollisionBitmask() ) )
//    {
//        CCLOG( "COLLISION HAS OCCURED" );
//        updatePlayerHp();
//    }
    
   
    
    
    return true;
}



void GamePlayScene::updatePlayerHp()
{
//    //get player health bar
//    ui::LoadingBar* playerHp = static_cast<ui::LoadingBar*>(this->getChildByName("GamePlayScene")->getChildByName("playerRightHP"));
//    
//    //amount of damage caused by punch1
//    if (buttonA->getIsActive())
//    {
//    
//        float percent = playerHp->getPercent();
//        playerHp->setPercent(percent - Punch1_damage);
//    }
//    
//    //amount of damage caused by punch2
//    if (buttonB->getIsActive())
//    {
//        
//        float percent = playerHp->getPercent();
//        playerHp->setPercent(percent - Punch2_damage);
//    }
//    
//    //amount of damage caused by kick1
//    if (buttonC->getIsActive())
//    {
//        
//        float percent = playerHp->getPercent();
//        playerHp->setPercent(percent - Kick1_damage);
//    }
//    
//    //amount of damage caused by kick2
//    if (buttonD->getIsActive())
//    {
//        
//        float percent = playerHp->getPercent();
//        playerHp->setPercent(percent - Kick2_damage);
//    }
//    
}

//bool GamePlayScene::opponentDie()
//{
//    if (opponent->gethealth() <= 0)
//    {
//        return true;
//    }
//}

void GamePlayScene::GoToMainMenuScene( float dt )
{
    
    auto scene = GamePlayScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}



