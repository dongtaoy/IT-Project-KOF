//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseCharactorScene.h"

USING_NS_CC;
using namespace ui;

#pragma mark init
Scene* ChooseCharactorScene::createScene()
{
    Multiplayer::getInstance()->resetAllListener();
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChooseCharactorScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChooseCharactorScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->playerSelected = "";
    this->opponentSelected = "";
    this->playerReady = false;
    this->opponentReady = false;
    
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CHOOSE_CHARACTOR_SCENE_CHARACTOR_PLIST);
    
    auto node = CSLoader::createNode(CHOOSE_CHARACTOR_SCENE_FILE);
    node->setName(CHOOSE_CHARACTOR_SCENE);
    
    Button* buttonBack = static_cast<Button*>(node->getChildByName(BACK_BUTTON));
    
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::ButtonBackClicked, this));
    
    node->getChildByName<Text*>(CHOOSE_CHARACTOR_SCENE_ROOMID)->setString(Multiplayer::getInstance()->getRoomID());
    
    for(int i = 1 ; i <= 6 ; i ++)
    {
        ImageView* image = static_cast<ImageView*>(node->getChildByName(CHOOSE_CHARACTOR_SCENE_CHARACTOR_PREFIX+std::to_string(i)));
        image->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::CharactorClicked, this));
    }
    
    node->getChildByName<Button*>(CHOOSE_CHARACTOR_SCENE_READY_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::ButtonReadyClicked, this));
    node->getChildByName<Button*>(CHOOSE_CHARACTOR_SCENE_GO_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::ButtonGoClicked, this));
    this->addChild(node);
    
    this->schedule(schedule_selector(ChooseCharactorScene::sendStatusMessage), 1.0f);
    
    Multiplayer::getInstance()->setNotificationListener(this);
    return true;
}





#pragma mark getters / setters
void ChooseCharactorScene::setOpponentSelected(std::string name)
{
    this->opponentSelected = name;
    ShowSelectedCharactor(opponentSelected, false);
}

void ChooseCharactorScene::setPlayerSelected(std::string name)
{
    if(playerSelected.compare("")){
        RemoveSelectedBorder(playerSelected);
    }
    playerSelected = name;
    ShowSelectedBorder(playerSelected);
    ShowSelectedCharactor(playerSelected, true);
}

void ChooseCharactorScene::setPlayerReady(bool value)
{
    if (value) {
        if(playerSelected.compare(""))
        {
            SetReadyButtonVisible(false, true);
            SetGoButtonVisible(true, true);
            playerReady = true;
        }else{
            MessageBox("", "Please Select a Charactor First");
        }
    }else{
        SetGoButtonVisible(false, true);
        SetReadyButtonVisible(true, true);
        playerReady = false;
    }
    CheckBothReady();
}

void ChooseCharactorScene::setOpponentReady(bool value)
{
    if (value) {
        SetReadyButtonVisible(false, false);
        SetGoButtonVisible(true, false);
        opponentReady = true;
    } else {
        SetGoButtonVisible(false, false);
        SetReadyButtonVisible(true, false);
        opponentReady = false;
    }
    CheckBothReady();
}




#pragma mark buttons / events
void ChooseCharactorScene::CharactorClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        setPlayerSelected(static_cast<Node*>(pSender)->getName());
    }
}

void ChooseCharactorScene::ButtonBackClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "unsubsribing room...", 30.0f);
        Multiplayer::getInstance()->unsubsribeRoom(this);
    }
}

void ChooseCharactorScene::ButtonGoClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        setPlayerReady(false);
    }
}

void ChooseCharactorScene::ButtonReadyClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        setPlayerReady(true);
    }
}


#pragma mark ready / go buttons
void ChooseCharactorScene::CheckBothReady()
{
    if(opponentReady && playerReady)
    {
//        Multiplayer::getInstance()->sendChat(Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, OP_CCS_START_GAME, ""));
    }
}


void ChooseCharactorScene::SetGoButtonVisible(bool visible, bool left)
{
    std::string name = left ? CHOOSE_CHARACTOR_SCENE_GO_L : CHOOSE_CHARACTOR_SCENE_GO_R;
    auto node = this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName<Button*>(name);
    node->setTouchEnabled(visible);
    node->setVisible(visible);
    
}

void ChooseCharactorScene::SetReadyButtonVisible(bool visible, bool left)
{
    std::string name = left ? CHOOSE_CHARACTOR_SCENE_READY_L : CHOOSE_CHARACTOR_SCENE_READY_R;
    auto node = this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName<Button*>(name);
    node->setTouchEnabled(visible);
    node->setVisible(visible);
}


void ChooseCharactorScene::ResetGoReadyButton()
{
    setPlayerReady(false);
    setOpponentReady(false);
}





#pragma mark select charactor
void ChooseCharactorScene::ShowSelectedCharactor(std::string name, bool left)
{
    std::string place = left ? CHOOSE_CHARACTOR_SCENE_PLAYER_ICON_HOLDER : CHOOSE_CHARACTOR_SCENE_OPPONENT_ICON_HOLDER;
    ImageView* image = static_cast<ImageView*>(this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(place));
    assert(image);
    image->setVisible(true);
    std::string filename = (boost::format(CHARACTOR_ICON_BIG_PATH) % name).str();
    image->loadTexture(filename, Widget::TextureResType::PLIST);
}


void ChooseCharactorScene::ShowSelectedBorder(std::string name)
{
    
    this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(name)->getChildByName(BORDER_UNSELECTED)->setVisible(false);
    this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(name)->getChildByName(BORDER_SELECTED)->setVisible(true);
}


void ChooseCharactorScene::RemoveSelectedBorder(std::string name)
{
    this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(name)->getChildByName(BORDER_SELECTED)->setVisible(false);
    this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(name)->getChildByName(BORDER_UNSELECTED)->setVisible(true);
}





#pragma mark coutdown
void ChooseCharactorScene::CountDownTask(float dt)
{
    auto node = this->getChildByName(CHOOSE_CHARACTOR_SCENE);
    Text* labelCountDown = static_cast<Text*>(node->getChildByName(CHOOSE_CHARACTOR_SCENE_COUNT_DOWN_LABEL));
    int value = std::atoi(labelCountDown->getString().c_str()) - 1;
    if(value > 0)
    {
        labelCountDown->setString(std::to_string(value));
    }
    else
    {
        EndCountDown();
        LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "unsubsribing room...", 30.0f);
        Multiplayer::getInstance()->unsubsribeRoom(this);
    }
}


void ChooseCharactorScene::ResetCountDown()
{
    EndCountDown();
    Text* labelCountDown = static_cast<Text*>(this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(CHOOSE_CHARACTOR_SCENE_COUNT_DOWN_LABEL));
    labelCountDown->setString("60");
}

void ChooseCharactorScene::StartCountDown()
{
    if (!isCountdownStart){
        isCountdownStart = true;
        this->schedule(schedule_selector(ChooseCharactorScene::CountDownTask), 1.0);
    }
}

void ChooseCharactorScene::EndCountDown()
{
    if(isCountdownStart){
        isCountdownStart = false;
        this->unschedule(schedule_selector(ChooseCharactorScene::CountDownTask));
    }
}


void ChooseCharactorScene::sendStatusMessage(float dt)
{
    std::string message = "";
    
    if(playerReady && opponentReady){
        StartGame();
        return;
    }
    
    if(playerSelected.compare(""))
    {
        message += Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, OP_CCS_CHARACTOR_CHANGED, playerSelected);
        if(playerReady)
            message += Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, OP_CCS_READY, playerSelected);
        else
            message += Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, OP_CCS_NOTREADY, "");
    }
    
//    if(message.compare(""))
        Multiplayer::getInstance()->sendChat(message);
}


#pragma mark listeners
void ChooseCharactorScene::onUnsubscribeRoomDone(AppWarp::room event)
{
    if(event.result == AppWarp::ResultCode::success)
    {
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "leaving room...", 60.0f);
        Multiplayer::getInstance()->leaveRoom(this);
    }else{
        MessageBox("Fail to unsubscribe Room", "Connection Error");
        auto scene = ChooseRoomScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}


void ChooseCharactorScene::onLeaveRoomDone(AppWarp::room event)
{
    if(event.result == AppWarp::ResultCode::success)
    {
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "DONE...", 100.0f);
    }else{
        MessageBox("Fail to leave Room", "Connection Error");
    }
    
    auto scene = ChooseRoomScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


void ChooseCharactorScene::onUserJoinedRoom(AppWarp::room, std::string name)
{
    if(Multiplayer::getInstance()->getUsername().compare(name)){
        CCLOG("someone joined");
        Multiplayer::getInstance()->setOpponentUsername(name);
    }
}

void ChooseCharactorScene::onUserLeftRoom(AppWarp::room, std::string name)
{
    if(Multiplayer::getInstance()->getUsername().compare(name)){
        CCLOG("someone left");
        Multiplayer::getInstance()->setOpponentUsername("");
        ResetCountDown();
        ResetGoReadyButton();
        this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(CHOOSE_CHARACTOR_SCENE_WAITING)->setVisible(true);
        this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(CHOOSE_CHARACTOR_SCENE_OPPONENT_ICON_HOLDER)->setVisible(false);
    }
}

void ChooseCharactorScene::onChatReceived(AppWarp::chat event)
{
    if(event.sender.compare(Multiplayer::getInstance()->getUsername())){
        Multiplayer::getInstance()->setOpponentUsername(event.sender);
    }
}

void ChooseCharactorScene::onPrivateChatReceived(std::string sender, std::string message)
{
    StartCountDown();
    std::vector<std::vector<std::string>> commands = Multiplayer::exractMessage(message);
    
    for(int i = 0 ; i < commands.size() ; i ++)
    {
        std::vector<std::string> command = commands.at(i);
        Multiplayer::getInstance()->setOpponentUsername(sender);
        auto node = this->getChildByName(CHOOSE_CHARACTOR_SCENE);
        node->getChildByName(CHOOSE_CHARACTOR_SCENE_WAITING)->setVisible(false);
        switch (atoi(command.at(1).c_str()))
        {
            case OP_CCS_CHARACTOR_CHANGED:
                setOpponentSelected(command.at(2));
                break;
                
            case OP_CCS_READY:
                setOpponentReady(true);
                break;
                
            case OP_CCS_NOTREADY:
                setOpponentReady(false);
                break;
                
            default:
                break;
        }
    }

}


#pragma mark start game
void ChooseCharactorScene::StartGame()
{
    ResetCountDown();
    LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
    
    // TODO: ONLY CHARACTOR1 AND CHARACTOR6 WORKS
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "suiting up charactors", 30.0f);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTOR_SPRITE_PATH) % playerSelected ).str());
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTOR_SPRITE_PATH) % opponentSelected ).str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTOR_ANIMATION_PATH) % playerSelected).str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTOR_ANIMATION_PATH) % opponentSelected).str());
    
    // TODO: CHANGE IT AFTER FINISH ANIMATIONS
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "Loading backgrounds", 60.0f);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(BACKGROUND_SPRITE_PATH) % "background1" ).str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(BACKGROUND_ANIMATION_PATH) % "background1" ).str());
    
    
    auto scene = GamePlayScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}







