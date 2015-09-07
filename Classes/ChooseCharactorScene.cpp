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

Scene* ChooseCharactorScene::createScene()
{
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
    
    Multiplayer::getInstance()->setNotificationListener(this);
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CHOOSE_CHARACTOR_SCENE_CHARACTOR_PLIST);
    
    auto node = CSLoader::createNode(CHOOSE_CHARACTOR_SCENE_FILE);
    node->setName(CHOOSE_CHARACTOR_SCENE);
    
    ui::Button* buttonBack = static_cast<ui::Button*>(node->getChildByName(BACK_BUTTON));
    
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::GotoChooseRoomScene, this));
    
    node->getChildByName<Text*>(CHOOSE_CHARACTOR_SCENE_ROOMID)->setString(Multiplayer::getInstance()->getRoomID());
    
    for(int i = 1 ; i <= 6 ; i ++)
    {
        ImageView* image = static_cast<ImageView*>(node->getChildByName(CHOOSE_CHARACTOR_SCENE_CHARACTOR_PREFIX+std::to_string(i)));
        image->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::CharactorSelectedChanged, this));
    }
    
    node->getChildByName<ui::Button*>(CHOOSE_CHARACTOR_SCENE_READY_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::ButtonReadyClicked, this));
    node->getChildByName<ui::Button*>(CHOOSE_CHARACTOR_SCENE_GO_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::ButtonGoClicked, this));
    this->addChild(node);
    return true;
}

void ChooseCharactorScene::ButtonGoClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        ChangeReadyState(false, true);
    }
}

void ChooseCharactorScene::ButtonReadyClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        ChangeReadyState(true, true);
    }
}

void ChooseCharactorScene::ChangeReadyState(bool ready, bool left)
{
    if(ready)
    {
        if(left)
        {
            if(playerSelected.compare(""))
            {
                SetReadyButtonVisible(false, true);
                SetGoButtonVisible(true, true);
                std::string message = Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, OP_CCS_READY, "");
                Multiplayer::getInstance()->sendChat(message);
                playerReady = true;
            }
            else
            {
                MessageBox("", "Please Select a Charactor First");
            }
        }
        else
        {
            SetReadyButtonVisible(false, false);
            SetGoButtonVisible(true, false);
            opponentReady = true;
        }
        
    }else{
        if(left)
        {
            SetGoButtonVisible(false, true);
            SetReadyButtonVisible(true, true);
            std::string message = Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, OP_CCS_NOTREADY, "");
            Multiplayer::getInstance()->sendChat(message);
            playerReady = false;
        }
        else
        {
            SetGoButtonVisible(false, false);
            SetReadyButtonVisible(true, false);
            opponentReady = false;
        }
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

void ChooseCharactorScene::ResetGoReadyButton(bool left)
{
    std::string go = left ? CHOOSE_CHARACTOR_SCENE_GO_L : CHOOSE_CHARACTOR_SCENE_GO_R;
    std::string ready = left ? CHOOSE_CHARACTOR_SCENE_READY_L : CHOOSE_CHARACTOR_SCENE_READY_R;
    this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(go)->setVisible(false);
    this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(ready)->setVisible(true);
}


void ChooseCharactorScene::CharactorSelectedChanged(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        SelectCharactor(static_cast<Node*>(pSender)->getName(), true);
    }
}

void ChooseCharactorScene::SelectCharactor(std::string name, bool left)
{
    if(left){
        if(playerSelected.compare("")){
            RemoveSelectedBorder(playerSelected);
        }
        playerSelected = name;
        ShowSelectedBorder(playerSelected);
        ShowSelectedCharactor(playerSelected, true);
        std::string message = Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, OP_CCS_CHARACTOR_CHANGED, playerSelected);
        Multiplayer::getInstance()->sendChat(message);
    }else{
        opponentSelected = name;
        ShowSelectedCharactor(opponentSelected, false);
    }
}


void ChooseCharactorScene::ShowSelectedCharactor(std::string name, bool left)
{
    std::string place = left ? CHOOSE_CHARACTOR_SCENE_PLAYER_ICON_HOLDER : CHOOSE_CHARACTOR_SCENE_OPPONENT_ICON_HOLDER;
    ImageView* image = static_cast<ImageView*>(this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(place));
    assert(image);
    image->setVisible(true);
    std::string filename = std::string(CHARACTOR_RESOURCE_DIR) + "/" + name + "/" + std::string(CHARACTOR_ICON_BIG);
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



void ChooseCharactorScene::GotoChooseRoomScene(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "unsubsribing room...", 30.0f);
        Multiplayer::getInstance()->unsubsribeRoom(this);
    }
}


void ChooseCharactorScene::CountDownTask(float dt)
{
    auto node = this->getChildByName(CHOOSE_CHARACTOR_SCENE);
    ui::Text* labelCountDown = static_cast<ui::Text*>(node->getChildByName(CHOOSE_CHARACTOR_SCENE_COUNT_DOWN_LABEL));
    int value = std::atoi(labelCountDown->getString().c_str()) - 1;
    if(value > 0)
    {
        
        labelCountDown->setString(std::to_string(value));
    }
    else
    {
        this->unschedule(schedule_selector(ChooseCharactorScene::CountDownTask));
        Multiplayer::getInstance()->unsubsribeRoom(this);
    }
}

void ChooseCharactorScene::ResetCountDown()
{
    EndCountDown();
    ui::Text* labelCountDown = static_cast<ui::Text*>(this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(CHOOSE_CHARACTOR_SCENE_COUNT_DOWN_LABEL));
    labelCountDown->setString("60");
}

void ChooseCharactorScene::StartCountDown()
{
    this->schedule(schedule_selector(ChooseCharactorScene::CountDownTask), 1.0);
}

void ChooseCharactorScene::EndCountDown()
{
    this->unschedule(schedule_selector(ChooseCharactorScene::CountDownTask));
}



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
        this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(CHOOSE_CHARACTOR_SCENE_WAITING)->setVisible(false);
        if(playerSelected.compare(""))
        {
            std::string message = Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, OP_CCS_CHARACTOR_CHANGED, playerSelected);
            this->scheduleOnce(
                               [&](float){Multiplayer::getInstance()->sendChat(message);},
                               1.5, "initial message");
            
        }
        std::string command = Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, OP_CCS_START_COUNTDOWN, "");
        this->scheduleOnce(
                           [&](float){Multiplayer::getInstance()->sendChat(command);StartCountDown();}, 1.0, "start countdown");
        
    }
}

void ChooseCharactorScene::onUserLeftRoom(AppWarp::room, std::string name)
{
    if(Multiplayer::getInstance()->getUsername().compare(name)){
        CCLOG("someone left");
        ResetCountDown();
        ResetGoReadyButton(true);
        ResetGoReadyButton(false);
        this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName("waiting")->setVisible(true);
        this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName(CHOOSE_CHARACTOR_SCENE_OPPONENT_ICON_HOLDER)->setVisible(false);
    }
}

void ChooseCharactorScene::onChatReceived(AppWarp::chat event)
{
    CCLOG("message: %s", event.chat.c_str());
    if(event.sender.compare(Multiplayer::getInstance()->getUsername())){
        auto node = this->getChildByName(CHOOSE_CHARACTOR_SCENE);
        node->getChildByName("waiting")->setVisible(false);
        
        std::vector<std::string> command = Multiplayer::exractMessage(event.chat);
        
        switch (atoi(command.at(1).c_str())) {
            case OP_CCS_CHARACTOR_CHANGED:
                SelectCharactor(command.at(2), false);
                break;
                
            case OP_CCS_READY:
                ChangeReadyState(true, false);
                
                break;
                
            case OP_CCS_NOTREADY:
                ChangeReadyState(false, false);
                break;
                
            case OP_CCS_START_COUNTDOWN:
                StartCountDown();
                break;
                
            default:
                break;
        }
    }
}





