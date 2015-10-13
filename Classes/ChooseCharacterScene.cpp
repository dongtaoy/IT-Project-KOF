//
//  ChooseRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "ChooseCharacterScene.h"

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
    
    
    cocos2d::Size visibleSize = Director::getInstance()->getWinSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto node = CSLoader::createNode(CHOOSE_CHARACTER_SCENE_FILE);
    node->setName(CHOOSE_CHARACTER_SCENE);
    
    cocos2d::ui::Button* buttonBack = static_cast<cocos2d::ui::Button*>(node->getChildByName(BACK_BUTTON));
    
    buttonBack->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::ButtonBackClicked, this));
    
    node->getChildByName<cocos2d::ui::Text*>(CHOOSE_CHARACTER_SCENE_ROOMID)->setString(PhotonMultiplayer::getInstance()->getRoomID());
    
    for(int i = 1 ; i <= 6 ; i ++)
    {
        cocos2d::ui::ImageView* image = static_cast<cocos2d::ui::ImageView*>(node->getChildByName(CHOOSE_CHARACTER_SCENE_CHARACTER_PREFIX+std::to_string(i)));
        image->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::CharacterClicked, this));
    }
    
    node->getChildByName<cocos2d::ui::Button*>(CHOOSE_CHARACTER_SCENE_READY_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::ButtonReadyClicked, this));
    node->getChildByName<cocos2d::ui::Button*>(CHOOSE_CHARACTER_SCENE_GO_L)->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::ButtonGoClicked, this));
    this->addChild(node);
    
    PhotonMultiplayer::getInstance()->setListener(this);
    this->scheduleUpdate();
    return true;
}


#pragma mark getters / setters
void ChooseCharacterScene::setOpponentSelected(std::string name)
{
    if(!name.compare(""))
        return;
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
        if (!opponentSelected.compare(""))
            return;
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
void ChooseCharacterScene::CharacterClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
        
        setPlayerSelected(static_cast<Node*>(pSender)->getName());
        PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_CHARACTER_CHANGED, static_cast<Node*>(pSender)->getName());
    }
}

void ChooseCharacterScene::ButtonBackClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
//                PhotonMultiplayer::getInstance()->sendEvent(1, 1, "", true);
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "leaving room...", 50.0f);
        PhotonMultiplayer::getInstance()->opLeaveRoom();
    }
}

void ChooseCharacterScene::ButtonGoClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        setPlayerReady(false);
        PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_NOTREADY, playerSelected);
    }
}

void ChooseCharacterScene::ButtonReadyClicked(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        setPlayerReady(true);
        PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_READY, playerSelected);
    }
    
}


#pragma mark ready / go buttons
void ChooseCharacterScene::CheckBothReady()
{
    if(opponentReady && playerReady)
    {
        LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "waiting for player...", 20.0f);
        PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_START_GAME, "", true);
//        StartGame();
    }
}


void ChooseCharacterScene::SetGoButtonVisible(bool visible, bool left)
{
    std::string name = left ? CHOOSE_CHARACTER_SCENE_GO_L : CHOOSE_CHARACTER_SCENE_GO_R;
    auto node = this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName<cocos2d::ui::Button*>(name);
    node->setTouchEnabled(visible);
    node->setVisible(visible);
    
}

void ChooseCharacterScene::SetReadyButtonVisible(bool visible, bool left)
{
    std::string name = left ? CHOOSE_CHARACTER_SCENE_READY_L : CHOOSE_CHARACTER_SCENE_READY_R;
    auto node = this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName<cocos2d::ui::Button*>(name);
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
    cocos2d::ui::ImageView* image = static_cast<cocos2d::ui::ImageView*>(this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(place));
    assert(image);
    image->setVisible(true);
    std::string filename = fmt::format(CHARACTER_ICON_BIG_PATH, name);
    image->loadTexture(filename, cocos2d::ui::Widget::TextureResType::PLIST);
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

void ChooseCharacterScene::onLeaveRoomDone()
{
    MultiplayerCallback::onLeaveRoomDone();
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), true, "Done...", 100.0f);
    auto scene = ChooseRoomScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


void ChooseCharacterScene::joinRoomEventAction()
{
    MultiplayerCallback::joinRoomEventAction();
    PhotonMultiplayer::getInstance()->sendEvent(MP_CHOOSE_CHARACTER_SCENE, OP_CCS_CHARACTER_CHANGED, playerSelected);
    ResetGoReadyButton();
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_WAITING)->setVisible(false);
}

void ChooseCharacterScene::leaveRoomEventAction()
{
    MultiplayerCallback::leaveRoomEventAction();
    ResetGoReadyButton();
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_WAITING)->setVisible(true);
    this->getChildByName(CHOOSE_CHARACTER_SCENE)->getChildByName(CHOOSE_CHARACTER_SCENE_OPPONENT_ICON_HOLDER)->setVisible(false);
}

void ChooseCharacterScene::onPlayerPropertiesChange()
{
    MultiplayerCallback::onPlayerPropertiesChange();
//    StartGame();
}


void ChooseCharacterScene::customEventAction(command_t event)
{
    MultiplayerCallback::customEventAction(event);
    switch (event.operation) {
        case OP_CCS_CHARACTER_CHANGED:
                setOpponentSelected(event.properties);
            break;
        case OP_CCS_READY:
            setOpponentSelected(event.properties);
            setOpponentReady(true);
            break;
    
        case OP_CCS_NOTREADY:
                setOpponentSelected(event.properties);
                setOpponentReady(false);
            break;
    
        case OP_CCS_START_GAME:
            if (!isGameStart)
                StartGame();
            
            break;
                
        default:
            break;
    }
}

#pragma mark loop
void ChooseCharacterScene::update(float dt)
{
    PhotonMultiplayer::getInstance()->service();
    
}


#pragma mark start game
void ChooseCharacterScene::StartGame()
{
    if (isGameStart)
        return;
    
    isGameStart = true;
    
    PhotonMultiplayer::getInstance()->setPlayerCharactor(playerSelected);
    PhotonMultiplayer::getInstance()->setOpponentCharactor(opponentSelected);
    
    
    
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "Done...", 100.0f);
    auto scene = GamePlayScene::createScene();
    Director::getInstance()->replaceScene(scene);

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
