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
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CHOOSE_CHARACTOR_SCENE_CHARACTOR_PLIST);
    
    auto node = CSLoader::createNode(CHOOSE_CHARACTOR_SCENE_FILE);
    node->setName(CHOOSE_CHARACTOR_SCENE);
    
    ui::Button* buttonBack = static_cast<ui::Button*>(node->getChildByName(BACK_BUTTON));
    
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::GotoChooseRoomScene, this));
    //    node->setPosition(origin);
    
    node->getChildByName<Text*>(CHOOSE_CHARACTOR_SCENE_ROOMID)->setString(Multiplayer::getInstance()->getRoomID());
//    Multiplayer::getInstance()
    
    
    for(int i = 1 ; i <= 6 ; i ++)
    {
        ImageView* image = static_cast<ImageView*>(node->getChildByName(CHOOSE_CHARACTOR_SCENE_CHARACTOR_PREFIX+std::to_string(i)));
        image->addTouchEventListener(CC_CALLBACK_2(ChooseCharactorScene::CharactorSelectedChanged, this));
    }
    
    
    this->addChild(node);
    
    Multiplayer::getInstance()->setNotificationListener(this);
    
    
    
    
    return true;
}


void ChooseCharactorScene::CharactorSelectedChanged(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        if(playerSelected != NULL){
            RemoveSelectedBorder(playerSelected);
            
        }
        playerSelected = pSender;
        ShowSelectedBorder(playerSelected);
        std::string name = static_cast<Node*>(pSender)->getName();
        ShowSelectedCharactor(name, true);
        std::string message = Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, MP_OP_CHARACTOR_CHANGED, name);
        Multiplayer::getInstance()->sendChat(message);
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
//    sprite->setSpriteFrame(std::string(CHARACTOR_RESOURCE_DIR) + "/" + name + "/" + std::string(CHARACTOR_ICON_BIG));
//    sprite->setScale(1);
//    sprite->setScale(CHOOSE_CHARACTOR_SCENE_CHARACTOR_WIDTH / sprite->getBoundingBox().size.width,
//                      CHOOSE_CHARACTOR_SCENE_CHARACTOR_HEIGHT / sprite->getBoundingBox().size.height);
    
    
}


void ChooseCharactorScene::ShowSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName(BORDER_UNSELECTED)->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName(BORDER_SELECTED)->setVisible(true);
}


void ChooseCharactorScene::RemoveSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName(BORDER_SELECTED)->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName(BORDER_UNSELECTED)->setVisible(true);
}



void ChooseCharactorScene::GotoChooseRoomScene(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
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
        Multiplayer::getInstance()->leaveRoom(this);
    }else{
        MessageBox("Fail to unsubscribe Room", "Connection Error");
        auto scene = ChooseRoomScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}


void ChooseCharactorScene::onLeaveRoomDone(AppWarp::room event)
{
    if(event.result != AppWarp::ResultCode::success)
    {
        MessageBox("Fail to leave Room", "Connection Error");
    }
    auto scene = ChooseRoomScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


void ChooseCharactorScene::onUserJoinedRoom(AppWarp::room, std::string name)
{
    CCLOG("someone joined");
    if(Multiplayer::getInstance()->getUsername().compare(name)){
        this->getChildByName(CHOOSE_CHARACTOR_SCENE)->getChildByName("waiting")->setVisible(false);
        if(playerSelected)
        {
            std::string message = Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, MP_OP_CHARACTOR_CHANGED, static_cast<Node*>(playerSelected)->getName());
            this->scheduleOnce(
                               [&](float){Multiplayer::getInstance()->sendChat(message);},
                               1.5, "initial chat");
            
        }
        std::string command = Multiplayer::buildMessage(MP_CHOOSE_CHARACTOR_SCENE, MP_OP_START_COUNTDOWN, "");
        this->scheduleOnce(
                           [&](float){Multiplayer::getInstance()->sendChat(command);StartCountDown();}, 1.0, "start countdown");
        
    }
}

void ChooseCharactorScene::onUserLeftRoom(AppWarp::room, std::string name)
{
    CCLOG("someone left");
    if(Multiplayer::getInstance()->getUsername().compare(name)){
        ResetCountDown();
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
            case MP_OP_CHARACTOR_CHANGED:
                ShowSelectedCharactor(command.at(2), false);
                break;
            case MP_OP_READY:
                
                break;
            case MP_OP_START_COUNTDOWN:
                StartCountDown();
                break;
            default:
                break;
        }
//        std::vector<std::string> chat = GameHelper::split(event.chat, ';');
//        std::cout << chat.at(0) <<std::endl;
//        std::cout<< chat.at(1) <<std::endl;
//        std::cout << "message reveived:" << event.chat << std::endl;
        
    }
}





