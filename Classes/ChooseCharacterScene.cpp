//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseCharacterScene.h"

USING_NS_CC;
using namespace ui;

#pragma mark init
Scene* ChooseCharacterScene::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChooseCharacterScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChooseCharacterScene::init()
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
    
    auto node = CSLoader::createNode(CHOOSE_CHARACTER_SCENE_FILE);
    node->setName(CHOOSE_CHARACTER_SCENE);
    
    Button* buttonBack = static_cast<Button*>(node->getChildByName(BACK_BUTTON));
    
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::ButtonBackClicked, this));
    
    node->getChildByName<Text*>(CHOOSE_CHARACTER_SCENE_ROOMID)->setString(Multiplayer::getInstance()->getRoomID());
    
    for(int i = 1 ; i <= 6 ; i ++)
    {
        ImageView* image = static_cast<ImageView*>(node->getChildByName(CHOOSE_CHARACTER_SCENE_CHARACTER_PREFIX+std::to_string(i)));
        image->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::CharacterClicked, this));
    }
    
    node->getChildByName<Button*>(CHOOSE_CHARACTER_SCENE_READY_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::ButtonReadyClicked, this));
    node->getChildByName<Button*>(CHOOSE_CHARACTER_SCENE_GO_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::ButtonGoClicked, this));
    this->addChild(node);
    this->scheduleUpdate();
    return true;
}






#pragma mark getters / setters
void ChooseCharacterScene::setOpponentSelected(std::string name)
{
    this->opponentSelected = name;
    ShowSelectedCharacter(opponentSelected, false);
}


void ChooseCharacterScene::setPlayerSelected(std::string name)
{
    if(!name.compare(""))
    {
        return;
    }
    if(playerSelected.compare("")){
        RemoveSelectedBorder(playerSelected);
    }
    playerSelected = name;
    ShowSelectedBorder(playerSelected);
    ShowSelectedCharacter(playerSelected, true);
    
}


void ChooseCharacterScene::setPlayerReady(bool value)
{
    if (value) {
        if(playerSelected.compare(""))
        {
            SetReadyButtonVisible(false, true);
            SetGoButtonVisible(true, true);
            playerReady = true;
        }else{
            MessageBox("", "Please Select a Character First");
        }
    }else{
        SetGoButtonVisible(false, true);
        SetReadyButtonVisible(true, true);
        playerReady = false;
    }
    CheckBothReady();
}

void ChooseCharacterScene::setOpponentReady(bool value)
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
void ChooseCharacterScene::CharacterClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        Multiplayer::sendChat(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_CHARACTER_CHANGED, static_cast<Node*>(pSender)->getName());
        Multiplayer::sendChat(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_NOTREADY);
    }
}

void ChooseCharacterScene::ButtonBackClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "unsubsribing room...", 30.0f);
        Multiplayer::getInstance()->unsubsribeRoom(this);
    }
}

void ChooseCharacterScene::ButtonGoClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
    {
        Multiplayer::sendChat(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_NOTREADY, playerSelected);
    }
}

void ChooseCharacterScene::ButtonReadyClicked(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED)
        Multiplayer::sendChat(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_READY, playerSelected);
    
}


#pragma mark ready / go buttons
void ChooseCharacterScene::CheckBothReady()
{
    if(opponentReady && playerReady)
        Multiplayer::sendChat(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_START_GAME);
}


void ChooseCharacterScene::SetGoButtonVisible(bool visible, bool left)
{
    std::string name = left ? CHOOSE_CHARACTER_SCENE_GO_L : CHOOSE_CHARACTER_SCENE_GO_R;
    auto node = this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName<Button*>(name);
    node->setTouchEnabled(visible);
    node->setVisible(visible);
    
}

void ChooseCharacterScene::SetReadyButtonVisible(bool visible, bool left)
{
    std::string name = left ? CHOOSE_CHARACTER_SCENE_READY_L : CHOOSE_CHARACTER_SCENE_READY_R;
    auto node = this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName<Button*>(name);
    node->setTouchEnabled(visible);
    node->setVisible(visible);
}


void ChooseCharacterScene::ResetGoReadyButton()
{
    setPlayerReady(false);
    setOpponentReady(false);
}





#pragma mark select character
void ChooseCharacterScene::ShowSelectedCharacter(std::string name, bool left)
{
    std::string place = left ? CHOOSE_CHARACTER_SCENE_PLAYER_ICON_HOLDER : CHOOSE_CHARACTER_SCENE_OPPONENT_ICON_HOLDER;
    ImageView* image = static_cast<ImageView*>(this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(place));
    assert(image);
    image->setVisible(true);
    std::string filename = (boost::format(CHARACTER_ICON_BIG_PATH) % name).str();
    image->loadTexture(filename, Widget::TextureResType::PLIST);
}


void ChooseCharacterScene::ShowSelectedBorder(std::string name)
{
    
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(name)->getChildByName(BORDER_UNSELECTED)->setVisible(false);
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(name)->getChildByName(BORDER_SELECTED)->setVisible(true);
}


void ChooseCharacterScene::RemoveSelectedBorder(std::string name)
{
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(name)->getChildByName(BORDER_SELECTED)->setVisible(false);
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(name)->getChildByName(BORDER_UNSELECTED)->setVisible(true);
}



#pragma mark callbacks
void ChooseCharacterScene::onUnsubscribeRoomDone()
{
    MultiplayerCallback::onUnsubscribeRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "leaving room...", 60.0f);
}


void ChooseCharacterScene::onLeaveRoomDone()
{
    MultiplayerCallback::onLeaveRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "DONE...", 100.0f);
    auto scene = ChooseRoomScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


#pragma mark loop
void ChooseCharacterScene::update(float dt)
{
    
    if (!Multiplayer::getInstance()->isCommandsEmpty())
    {
        processCommand(Multiplayer::getInstance()->popCommands());
    }
    
}

void ChooseCharacterScene::processCommand(command_t command)
{
    if (!Multiplayer::isCommandValid(MP_CHOOSE_CHARACTER_SCENE, command))
        return;
        
    if(command.sender.compare(Multiplayer::getInstance()->getUsername()))
    {
        this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_WAITING)->setVisible(false);
        Multiplayer::getInstance()->setOpponentUsername(command.sender);
    }
    
    switch (command.operation) {
        case OP_CCS_CHARACTER_CHANGED:
            if (!command.sender.compare(Multiplayer::getInstance()->getUsername()))
                setPlayerSelected(command.properties);
            else
                setOpponentSelected(command.properties);
            break;
            
        case OP_CCS_READY:
            if (!command.sender.compare(Multiplayer::getInstance()->getUsername()))
            {
                setPlayerSelected(command.properties);
                setPlayerReady(true);
            }
            else
            {
                setOpponentSelected(command.properties);
                setOpponentReady(true);
            }
            break;
            
        case OP_CCS_NOTREADY:
            if (!command.sender.compare(Multiplayer::getInstance()->getUsername()))
            {
                setPlayerSelected(command.properties);
                setPlayerReady(false);
            }
            else
            {
                setPlayerSelected(command.properties);
                setOpponentReady(false);
            }
            break;
        
        case OP_GB_USER_JOINED:
            if (command.sender.compare(Multiplayer::getInstance()->getUsername()))
            {
                ResetGoReadyButton();
                this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_WAITING)->setVisible(false);
                Multiplayer::getInstance()->setOpponentUsername(command.sender);
            }
            
            break;
            
        case OP_GB_USER_LEFT:
            if (command.sender.compare(Multiplayer::getInstance()->getUsername()))
            {
                Multiplayer::getInstance()->setOpponentUsername("");
                ResetGoReadyButton();
                this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_WAITING)->setVisible(true);
                this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_OPPONENT_ICON_HOLDER)->setVisible(false);
            }
            break;
        
        case OP_CCS_START_GAME:
            if (!isGameStart) {
                StartGame();
            }
            break;
            
        default:
            break;
    }
}


#pragma mark start game
void ChooseCharacterScene::StartGame()
{
    isGameStart = true;
    LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
    
    
    Multiplayer::getInstance()->setUserCharacter(playerSelected);
    Multiplayer::getInstance()->setOpponentCharacter(opponentSelected);
    
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "suiting up characters...", 35.0f);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTER_SPRITE_PATH) % playerSelected ).str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTER_ANIMATION_PATH) % playerSelected).str());
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(CHARACTER_SPRITE_PATH) % opponentSelected ).str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(CHARACTER_ANIMATION_PATH) % opponentSelected).str());
    
    
    // TODO: CHANGE IT AFTER FINISH ANIMATIONS
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "loading bacground...", 70.0f);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile((boost::format(BACKGROUND_SPRITE_PATH) % Multiplayer::getInstance()->getBackground() ).str());
    AnimationCache::getInstance()->addAnimationsWithFile((boost::format(BACKGROUND_ANIMATION_PATH) % Multiplayer::getInstance()->getBackground() ).str());
    
    
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "Done...", 100.0f);
    auto scene = GamePlayScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}


//#pragma mark coutdown
//void ChooseCharacterScene::CountDownTask(float dt)
//{
//    auto node = this->getChildByName(CHOOSE_CHARACTER_SCENE);
//    Text* labelCountDown = static_cast<Text*>(node->getChildByName(CHOOSE_CHARACTER_SCENE_COUNT_DOWN_LABEL));
//    int value = std::atoi(labelCountDown->getString().c_str()) - 1;
//    if(value > 0)
//    {
//        labelCountDown->setString(std::to_string(value));
//    }
//    else
//    {
//        EndCountDown();
//        this->unschedule(schedule_selector(ChooseCharacterScene::sendStatusMessage));
//        LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
//        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "unsubsribing room...", 30.0f);
//        Multiplayer::getInstance()->unsubsribeRoom(this);
//    }
//}
//
//
//void ChooseCharacterScene::ResetCountDown()
//{
//    EndCountDown();
//    Text* labelCountDown = static_cast<Text*>(this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_COUNT_DOWN_LABEL));
//    labelCountDown->setString("20");
//}
//
//void ChooseCharacterScene::StartCountDown()
//{
//    if (!isCountdownStart){
//        auto node = this->getChildByName(CHOOSE_CHARACTER_SCENE);
//        node->getChildByName(CHOOSE_CHARACTER_SCENE_WAITING)->setVisible(false);
//        isCountdownStart = true;
//        this->schedule(schedule_selector(ChooseCharacterScene::CountDownTask), 1.0);
//    }
//}
//
//void ChooseCharacterScene::EndCountDown()
//{
//    if(isCountdownStart){
//        isCountdownStart = false;
//        this->unschedule(schedule_selector(ChooseCharacterScene::CountDownTask));
//    }
//}
//







