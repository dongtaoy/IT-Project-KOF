//
//  GamePlayScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 6/09/2015.
//
//

#include "GamePlayScene.h"

Scene* GamePlayScene::createScene()
{
//    Multiplayer::getInstance()->resetAllListener();
    
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
    //set the gravity (0.0f, -98.0f) is the default value. change to -200 for y axis is perfect value
//    scene->getPhysicsWorld()->setGravity( Vec2(GRAVITY_X, GRAVITY_Y));
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
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    auto node = CSLoader::createNode("GamePlay.csb");
    
    node->getChildByName<cocos2d::ui::Button*>("pause")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::PauseClicked, this));
    this->background = node->getChildByName<Sprite*>("background");
    this->addChild(node);
    
    
    auto leftHp = this->getChildByName("GamePlayScene")->getChildByName<cocos2d::ui::LoadingBar*>("playerLeftHP");
    auto rightHp = this->getChildByName("GamePlayScene")->getChildByName<cocos2d::ui::LoadingBar*>("playerRightHP");
    
    
    
    /////////////////////////////////////////////////////////////////
    
    
    auto size = node->getBoundingBox().size;
    auto edgeNode = Node::create();
    auto physicsBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + visibleSize.height * 0.03));
    edgeNode->setPhysicsBody(physicsBody);
    this->addChild(edgeNode);
    
    
    /////////////////////////////////////////////////////////////////

//     TODO: WITH MULTIPLAYER
    if(PhotonMultiplayer::getInstance()->getPlayerNumber() > PhotonMultiplayer::getInstance()->getOpponentNumber())
    {
        this->player = new Fighter(background->getChildByName<Sprite*>("right"), rightHp, PhotonMultiplayer::getInstance()->getPlayerCharactor(), false);
        node->getChildByName<cocos2d::ui::ImageView*>("playerRight")->loadTexture(fmt::format("characters/{0}/icon_game_right.png", PhotonMultiplayer::getInstance()->getPlayerCharactor()), cocos2d::ui::Widget::TextureResType::PLIST);
        
        this->opponent = new Fighter(background->getChildByName<Sprite*>("left"), leftHp, PhotonMultiplayer::getInstance()->getOpponentCharactor(), true);
        node->getChildByName<cocos2d::ui::ImageView*>("playerLeft")->loadTexture(fmt::format("characters/{0}/icon_game_left.png", PhotonMultiplayer::getInstance()->getOpponentCharactor()), cocos2d::ui::Widget::TextureResType::PLIST);
    
    }
    else
    {
        this->player = new Fighter(background->getChildByName<Sprite*>("left"), rightHp, PhotonMultiplayer::getInstance()->getPlayerCharactor(), true);
        node->getChildByName<cocos2d::ui::ImageView*>("playerRight")->loadTexture(fmt::format("characters/{0}/icon_game_left.png", PhotonMultiplayer::getInstance()->getPlayerCharactor()), cocos2d::ui::Widget::TextureResType::PLIST);
        
        this->opponent = new Fighter(background->getChildByName<Sprite*>("right"), leftHp, PhotonMultiplayer::getInstance()->getOpponentCharactor(), false);
        node->getChildByName<cocos2d::ui::ImageView*>("playerRight")->loadTexture(fmt::format("characters/{0}/icon_game_right.png", PhotonMultiplayer::getInstance()->getOpponentCharactor()), cocos2d::ui::Widget::TextureResType::PLIST);
    }

    
    player->setOpponent(opponent);
    opponent->setOpponent(player);

    
    this->camera = new Camera2d(player, opponent, background);
    this->createBackgroundAnimation();
    this->createJoystick();
    this->buttonA = createButtons(GAME_PLAY_SCENE_BUTTON_A_NORMAL, GAME_PLAY_SCENE_BUTTON_A_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_A_X, GAME_PLAY_SCENE_BUTTON_A_Y));
    this->buttonB = createButtons(GAME_PLAY_SCENE_BUTTON_B_NORMAL, GAME_PLAY_SCENE_BUTTON_B_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_B_X, GAME_PLAY_SCENE_BUTTON_B_Y));
    this->buttonC = createButtons(GAME_PLAY_SCENE_BUTTON_C_NORMAL, GAME_PLAY_SCENE_BUTTON_C_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_C_X, GAME_PLAY_SCENE_BUTTON_C_Y));
    this->buttonD = createButtons(GAME_PLAY_SCENE_BUTTON_D_NORMAL, GAME_PLAY_SCENE_BUTTON_D_PRESSED, Vec2(GAME_PLAY_SCENE_BUTTON_D_X, GAME_PLAY_SCENE_BUTTON_D_Y));
    
    
    lockstepId = 0;
    gameFrame = 0;
    alreadySent = false;
    PhotonMultiplayer::getInstance()->setListener(this);
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
    auto countDown = node->getChildByName<cocos2d::ui::Text*>("countDown");
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
    if (PhotonMultiplayer::getInstance()->getPlayerNumber() == cmd.sender)
    {
        player->processCommand(cmd);
    }
    else
    {
        opponent->processCommand(cmd);
    }
}


bool GamePlayScene::lockStepTurn()
{
    if (nextnextCommands.size() >= 2 || lockstepId < 2) {
        if (!player->isNextAction())
            return false;
        // send Command
        command_t c = processInput();
        nextnextCommands.push(c);
        PhotonMultiplayer::getInstance()->sendEvent(PhotonMultiplayer::buildEvent(c.scene, c.operation, c.properties));
        if (nextCommands.size() >= 2)
        {
            for (int i = 0; i < 2; i ++)
            {
                currentCommands.push(nextCommands.top());
                nextCommands.pop();
            }
        }
        if (nextnextCommands.size() >= 2) {
            for (int i = 0; i < 2; i ++)
            {
                nextCommands.push(nextnextCommands.top());
                nextnextCommands.pop();
            }
        }
        for (int i = 0; i < currentCommands.size(); i ++)
        {
            command_t c = currentCommands.top();
            if (c.sender == PhotonMultiplayer::getInstance()->getPlayerNumber()) {
                if (player->isNextAction()) {
                    processCommand(c);
                    currentCommands.pop();
                }
            }
            else
            {
                if (opponent->isNextAction()) {
                    processCommand(c);
                    currentCommands.pop();
                }
            }
        }
        return true;
    }
    return false;
}

void GamePlayScene::gameFrameTurn()
{
    if(gameFrame == 0) {
        if(lockStepTurn()) {
            gameFrame++;
        }
    } else {
        for (int i = 0; i < currentCommands.size(); i ++)
        {
            command_t c = currentCommands.top();
            if (c.sender == PhotonMultiplayer::getInstance()->getPlayerNumber()) {
                if (player->isNextAction()) {
                    processCommand(c);
                    currentCommands.pop();
                }
            }
            else
            {
                if (opponent->isNextAction()) {
                    processCommand(c);
                    currentCommands.pop();
                }
            }
        }
        
        if (gameFrame != 3)
        {
            gameFrame++;
        }
        else
        {
            if (gameFrame == 3 && currentCommands.size() == 0)
            {
                gameFrame++;
            }
        }
        
        
        if(gameFrame == GAME_FRAME_PER_LOCKSTEP) {
            gameFrame = 0;
        }
    }
    CCLOG("\t\t\t\tlockstep id: %lu, gameframe: %d", lockstepId, gameFrame);
}


command_t GamePlayScene::processInput()
{
    lockstepId++;
    auto point = joystick->getVelocity();
    auto angle = GameHelper::vectorToDegree(point);
    auto pos = player->getSprite()->getPosition();
    
    CCLOG("current player pos %f %f", pos.x, pos.y);
    
    command_t output;
    output.scene = MP_GAME_PLAY_SCNE;
    output.sender = PhotonMultiplayer::getInstance()->getPlayerNumber();
    
    // stand move forward
    if (angle > 337.5f || angle <  22.5f)
    {
        output.operation = OP_GPS_ACTION_1_STAND_MOVEFORWARD;
        output.properties = PhotonMultiplayer::buildProperties({std::to_string(pos.x + 50), std::to_string(pos.y)});
    }
    
    // stand move back
    if (angle > 157.5f && angle < 202.5f)
    {
        output.operation = OP_GPS_ACTION_1_STAND_MOVEBACK;
        output.properties = PhotonMultiplayer::buildProperties({std::to_string(pos.x - 50), std::to_string(pos.y)});
    }
    
    
    
        // jump
    if (angle >  22.5f && angle < 157.5f)
    {
        
        int distance = point.x * ACTION_MOVE_SPEED;
        output.operation = OP_GPS_ACTION_2_STAND_JUMP;
        output.properties = PhotonMultiplayer::buildProperties({std::to_string(distance)});
        
    }
    
    if (std::isnan(angle))
    {
        output.operation = OP_GPS_ACTION_1_STAND;
//        output.properties = PhotonMultiplayer::buildProperties({std::to_string(pos.x), std::to_string(pos.y)});
        
    }
    
    
    
//        // squat moveback
//        if (angle > 202.5f && angle < 247.5f)
//        {
//            message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_MOVEBACK);
//    //        player->squat_moveback();
//        }
//    
//        // squat
//        if (angle > 247.5f && angle < 292.5f)
//        {
//            message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_DOWN, properties);
//    //        player->squat_down();
//        }
//    
//        if (angle > 292.5f && angle < 337.5f)
//        {
//            message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_MOVEFORWARD);
//    //        player->squat_moveforward();
//        }
    
    return output;
}



void GamePlayScene::update(float dt)
{
    
    accumilatedTime = accumilatedTime + dt * 1000;
    
    
    while(accumilatedTime > GAME_FRAME_LENGTH) {
        CCLOG("\t\t\tnextCommands: %lu nexnextCommands", nextCommands.size(), nextnextCommands.size());
        gameFrameTurn ();
        accumilatedTime = accumilatedTime - GAME_FRAME_LENGTH;
    }
    
    
    PhotonMultiplayer::getInstance()->service();
//    auto point = joystick->getVelocity();
//    auto angle = GameHelper::vectorToDegree(point);
//    
////
////    if (!Multiplayer::getInstance()->isCommandsEmpty())
////    {
////        if (opponent->isActionStoppable())
////            processCommand(Multiplayer::getInstance()->popCommands());
////    }
//    
//    auto pos = player->getPosition();
//    std::string properties = PhotonMultiplayer::buildProperties({std::to_string(pos.x), std::to_string(pos.y)});
//    
//    std::string message;
//    
//    // stand move forward
//    if (angle > 337.5f || angle <  22.5f)
//    {
//        message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_STAND_MOVEFORWARD);
////        player->stand_moveforward();
//    }
//    
//    // stand move back
//    if (angle > 157.5f && angle < 202.5f)
//    {
//        message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_STAND_MOVEBACK);
////        player->stand_moveback();
//    }
//    
//    
//    // jump
//    if (angle >  22.5f && angle < 157.5f)
//    {
//        if (player->isActionStoppable())
//        {
//            int distance = point.x * ACTION_MOVE_SPEED;
//            message = PhotonMultiplayer::buildEvent(
//                                                MP_GAME_PLAY_SCNE,
//                                                OP_GPS_ACTION_2_STAND_JUMP,
//                                                PhotonMultiplayer::buildProperties({std::to_string(distance)}));
////            player->stand_jump(distance);
//        }
//    }
//    
//    
//
//    // squat moveback
//    if (angle > 202.5f && angle < 247.5f)
//    {
//        message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_MOVEBACK);
////        player->squat_moveback();
//    }
//    
//    // squat
//    if (angle > 247.5f && angle < 292.5f)
//    {
//        message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_DOWN, properties);
////        player->squat_down();
//    }
//    
//    if (angle > 292.5f && angle < 337.5f)
//    {
//        message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_SQUAT_MOVEFORWARD);
////        player->squat_moveforward();
//    }
//    
//    
//    
//    
//    if (buttonA->getIsActive())
//    {
//        if (player->isActionStoppable())
//        {
//            message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_PUNCH1, properties);
////            player->punch1();
//        }
//    }
//    
//    if (buttonB->getIsActive())
//    {
//        if (player->isActionStoppable())
//        {
//            message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_PUNCH2, properties);
////            player->punch2();
//        }
//    }
//    
//    if (buttonC->getIsActive())
//    {
//        if (player->isActionStoppable())
//        {
//            message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_KICK1, properties);
////            player->kick1();
//            
//        }
//    }
//    
//    if (buttonD->getIsActive())
//    {
//        if (player->isActionStoppable())
//        {
//            message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_2_STAND_KICK2, properties);
////            player->kick2();
//        }
//    }
//    if (std::isnan(angle))
//    {
//        if (player->isActionStoppable()) {
//            message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_1_STAND, properties);
////            player->stand();
//        }
//    }
//    
//    if (player->getIsHealthChanged())
//    {
//        player->setIsHealthChanged(false);
//        auto p = PhotonMultiplayer::buildProperties({std::to_string(player->getHealthPercentage())});
//        message = PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCNE, OP_GPS_ACTION_3_HEALTHCHANGED,p);
//    }
//    
////    
////    if (player->getIsDie() || opponent->getIsDie())
////    {
////        
////        MenuClicked(nullptr, cocos2d::ui::Widget::TouchEventType::ENDED);
////        this->unscheduleUpdate();
////    }
//
////    
//    player->update(dt);
//    opponent->update(dt);
    camera->update(dt);
//    if(message.compare(""))
//    {
//        PhotonMultiplayer::getInstance()->sendEvent(message);
//    }
//
//    
    
}


void GamePlayScene::PauseClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        auto node = CSLoader::createNode("PauseLayer.csb");
        this->addChild(node);
        node->getChildByName<cocos2d::ui::Button*>("buttonResume")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::ResumeClicked, this));
        node->getChildByName<cocos2d::ui::Button*>("buttonMenu")->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::MenuClicked, this));
    }
}

void GamePlayScene::ResumeClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        this->removeChildByName("PauseLayer");
    }
}

void GamePlayScene::MenuClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "leaving room...", 50.0f);
        PhotonMultiplayer::getInstance()->opLeaveRoom();
    }
}

void GamePlayScene::createJoystick()
{
    cocos2d::Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    int joystickOffsetX = 160;
    int joystickOffsetY = 140;
    
    cocos2d::Rect joystickBaseDimensions = cocos2d::Rect(0, 0, 30.0f, 30.0f);
    cocos2d::Point joystickBasePosition  = cocos2d::Point(origin.x + (joystickBaseDimensions.size.width / 2) + joystickOffsetX, origin.y + (joystickBaseDimensions.size.height / 2) + joystickOffsetY);
    
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
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getWinSize();
    // button A
    auto buttonBase = SneakyButtonSkinnedBase::create();
    auto button = new SneakyButton();
    
    auto buttonRect = cocos2d::Rect(0, 0, 30.f, 30.f);
    auto buttonPos = cocos2d::Point(visibleSize.width * pos.x, visibleSize.height * pos.y);
    
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
    
    //     TODO: WITH MULTIPLAYER
    auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(PhotonMultiplayer::getInstance()->getBackground());
//     TODO: WITHOUT MULTIPLAYER
//    auto animation = AnimationCache::getInstance()->getAnimation("background1");
    cocos2d::Size targetSize = cocos2d::Size( 2305.0f, 750.0f );
    cocos2d::Size backgroundSize = background->getContentSize();
    background->setScale( ( targetSize.width / backgroundSize.width ), ( targetSize.height / backgroundSize.height ) );
    
    
    
    background->runAction(RepeatForever::create(Animate::create(animation)));
    
}



void GamePlayScene::onLeaveRoomDone()
{
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "DONE...", 100.0f);
    auto scene = ChooseRoomScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void GamePlayScene::customEventAction(command_t cmd)
{
    if (cmd.scene == MP_GAME_PLAY_SCNE) {
        nextnextCommands.push(cmd);
//        PhotonMultiplayer::getInstance()->sendEvent(PhotonMultiplayer::buildEvent(MP_GAME_PLAY_SCENE_CONFIRM, cmd.operation));
    }
//    if (cmd.scene == MP_GAME_PLAY_SCENE_CONFIRM)
//    {
//        confirmedCommand.push(pendingCommand.top());
//        pendingCommand.pop();
//    }
    
    
    
    
    
    
//            switch (cmd.operation) {
//                case OP_GPS_ACTION_2_STAND_PUNCH1:
//                    opponent->setPosition(PhotonMultiplayer::extractPos(cmd.properties));
//                    opponent->punch1();
//                    break;
//                case OP_GPS_ACTION_2_STAND_PUNCH2:
//                    opponent->setPosition(PhotonMultiplayer::extractPos(cmd.properties));
//                    opponent->punch2();
//                    break;
//    
//                case OP_GPS_ACTION_2_STAND_KICK1:
//                    opponent->setPosition(PhotonMultiplayer::extractPos(cmd.properties));
//                    opponent->kick1();
//                    break;
//    
//                case OP_GPS_ACTION_2_STAND_KICK2:
//                    opponent->setPosition(PhotonMultiplayer::extractPos(cmd.properties));
//                    opponent->kick2();
//                    break;
//    
//                case OP_GPS_ACTION_1_STAND:
//                    opponent->setPosition(PhotonMultiplayer::extractPos(cmd.properties));
//                    opponent->stand();
//                    break;
//    
//                case OP_GPS_ACTION_1_STAND_MOVEFORWARD:
//                    opponent->stand_moveforward();
//                    break;
//    
//                case OP_GPS_ACTION_1_STAND_MOVEBACK:
//                    opponent->stand_moveback();
//                    break;
//    
//                case OP_GPS_ACTION_2_STAND_JUMP:
//                    opponent->stand_jump(atoi(GameHelper::split(cmd.properties, '%').at(0).c_str()));
//                    break;
//    
//                case OP_GPS_ACTION_1_SQUAT_DOWN:
//                        opponent->setPosition(PhotonMultiplayer::extractPos(cmd.properties));
//                        opponent->squat_down();
//                    break;
//    
//                case OP_GPS_ACTION_1_SQUAT_MOVEFORWARD:
//                        opponent->squat_moveforward();
//                    break;
//    
//                case OP_GPS_ACTION_1_SQUAT_MOVEBACK:
//                        opponent->squat_moveback();
//                    break;
//    
//                case OP_GPS_ACTION_3_HEALTHCHANGED:
//                        opponent->setHealthPercentage(std::atof(GameHelper::split(cmd.properties, '%').at(0).c_str()));
//                    break;
//                default:
//                    break;
//            }
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


void GamePlayScene::GoToMainMenuScene( float dt )
{
    
    auto scene = GamePlayScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}



