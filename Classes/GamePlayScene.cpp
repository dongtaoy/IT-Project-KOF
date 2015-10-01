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
    scene->getPhysicsWorld()->setGravity( Vec2(0.0f, -200.0f));
    //    scene->getPhysicsWorld()->setAutoStep(true);
    //
    //
    //    sceneWorld->set
    
    
    
    
    // 'layer' is an autorelease object
    auto layer = GamePlayScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    
    
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
    
    
////     TODO: WITH MULTIPLAYER
//    if(Multiplayer::getInstance()->getUsername().compare(Multiplayer::getInstance()->getOpponentUsername()) < 0)
//    {
//        CCLOG("123");
//        this->player = new Fighter(background->getChildByName<Sprite*>("right"), Multiplayer::getInstance()->getUserCharacter());
//        node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % Multiplayer::getInstance()->getUserCharacter()).str(), Widget::TextureResType::PLIST);
//        
//        this->opponent = new Fighter(background->getChildByName<Sprite*>("left"), Multiplayer::getInstance()->getOpponentCharacter());
//        node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % Multiplayer::getInstance()->getOpponentCharacter()).str(), Widget::TextureResType::PLIST);
//    
//    }
//    else
//    {
//        CCLOG("456");
//        this->player = new Fighter(background->getChildByName<Sprite*>("left"), Multiplayer::getInstance()->getUserCharacter());
//        node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % Multiplayer::getInstance()->getUserCharacter()).str(), Widget::TextureResType::PLIST);
//        
//        this->opponent = new Fighter(background->getChildByName<Sprite*>("right"), Multiplayer::getInstance()->getOpponentCharacter());
//        node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % Multiplayer::getInstance()->getOpponentCharacter()).str(), Widget::TextureResType::PLIST);
//    }
    

     //TODO: WITHOUT MULTIPLAYER
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(BACKGROUND_SPRITE_PATH) % "background1" ).str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(BACKGROUND_ANIMATION_PATH) % "background1" ).str());

    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTER_SPRITE_PATH) % "character1").str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTER_ANIMATION_PATH) % "character1").str());
    this->player = new Fighter(background->getChildByName<Sprite*>("left"), "character1");
    node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % "character1").str(), Widget::TextureResType::PLIST);
    this->opponent = new Fighter(background->getChildByName<Sprite*>("right"), "character1");
    node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % "character1").str(), Widget::TextureResType::PLIST);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTER_SPRITE_PATH) % "character5").str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTER_ANIMATION_PATH) % "character5").str());
    this->player = new Fighter(background->getChildByName<Sprite*>("left"), "character5");
    node->getChildByName<ImageView*>("playerLeft")->loadTexture((boost::format("characters/%s/icon_game_left.png") % "character5").str(), Widget::TextureResType::PLIST);
    this->opponent = new Fighter(background->getChildByName<Sprite*>("right"), "character5");
    node->getChildByName<ImageView*>("playerRight")->loadTexture((boost::format("characters/%s/icon_game_right.png") % "character5").str(), Widget::TextureResType::PLIST);


    
    
    
    player->setOpponent(opponent);
    opponent->setOpponent(player);

    /////////////////////////////////////////////////////////////////
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    
    auto edgeNode = Node::create();
    edgeNode ->setPosition( Point( visibleSize.width / 2 + origin.x,  float( player->getSprite()->getPosition().y)+ visibleSize.height-350.00));
    edgeNode->setPhysicsBody( edgeBody );
    
    this->addChild( edgeNode );
    /////////////////////////////////////////////////////////////////
    
    float x1 = player->getSprite()->getBoundingBox().size.width;
    float y1 = player->getSprite()->getBoundingBox().size.height;
    float x2 = opponent->getSprite()->getBoundingBox().size.width;
    float y2 = opponent->getSprite()->getBoundingBox().size.height;
    
    //    float y1 = player->getSprite()->getScaleY();
    //
    //    float x2 = opponent->getSprite()->getScaleX();
    //    float y2 = opponent->getSprite()->getScaleY();
    
    //    Size characterSize2 = opponent->getSprite()->getContentSize();
    addNewSpriteAtPosition(player->getSprite(),x1,y1,1);
    addNewSpriteAtPosition(opponent->getSprite(),x2,y2,2);
    
    ////character1
    //    {
    //    auto sprite1 = background->getChildByName("left");
    ////    sprite1->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    //
    //    auto spriteBody = PhysicsBody::createBox( Size(180.0f, 440.0f), PhysicsMaterial( 0, 1, 0 ) );
    //    spriteBody->setCollisionBitmask(1);
    //    spriteBody->setContactTestBitmask(true);
    //    sprite1->setPhysicsBody( spriteBody );
    //
    ////    this->addChild(sprite1);
    //    }
    //
    //
    //
    /////character 2
    //    {
    //    auto sprite2 = background->getChildByName("right");
    //    //    sprite1->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    //
    //    auto spriteBody2 = PhysicsBody::createBox( Size(180.0f, 440.0f), PhysicsMaterial( 0, 1, 0 ) );
    //    spriteBody2->setCollisionBitmask(2);
    //    spriteBody2->setContactTestBitmask(true);
    //    sprite2->setPhysicsBody( spriteBody2 );
    //    
    //    //////////////////////
    //    }
    //   
    
    
    
    
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

void GamePlayScene::update(float dt)
{
    auto point = joystick->getVelocity();
    auto angle = GameHelper::vectorToDegree(point);
    
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
    
    // stand move forward
    if (angle > 337.5f || angle <  22.5f)
    {
        player->stand_moveforward();
    }
    
    // jump
    if (angle >  22.5f && angle < 157.5f)
    {
        player->stand_jump(point);
    }
    
    // stand move back
    if (angle > 157.5f && angle < 202.5f)
    {
        player->stand_moveback();
    }
    
    
    // squat moveback
    if (angle > 202.5f && angle < 247.5f)
    {
        player->squat_moveback();
    }
    
    // squat
    if (angle > 247.5f && angle < 292.5f)
    {
        player->squat_down();
    }
    
    if (angle > 292.5f && angle < 337.5f)
    {
        player->squat_moveforward();
    }
    
    if (std::isnan(angle))
    {
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
    
}


void GamePlayScene::addNewSpriteAtPosition(Node* sprite, float x, float y, int bitmask)
{
    
    //    sprite->setTag(1);
    auto body = PhysicsBody::createBox(Size(x-100.0f, y), PhysicsMaterial(1.0f, 0.0f, 0.3f));
    //    auto body = PhysicsBody::createBo(100,PhysicsMaterial(1.0f, 1.0f, 1.0f));
    //    body->setDynamic(false);
    sprite->setPhysicsBody(body);
    //    this->addChild(sprite);
    body->setCollisionBitmask(bitmask);
    body->setContactTestBitmask(true);
    body->setRotationEnable(false);
    //    body->applyForce(0);
    body->setGravityEnable(true);
    
    
}

bool GamePlayScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    // check if the bodies have collided
    if ( ( 1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) || ( 2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {
        CCLOG( "COLLISION HAS OCCURED" );
    }
    
    return true;
}


