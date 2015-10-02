//
//  MainMenuScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#include "MainMenuScene.h"

USING_NS_CC;
using namespace ui;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto node = CSLoader::createNode("MainMenu.csb");
    ui::Button* buttonMultiplayer =  static_cast<ui::Button*>(node->getChildByName("buttonMultiplayer"));
    buttonMultiplayer->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GoToChooseRoomScene, this));
    
    ui::Button* buttonHelp =  static_cast<ui::Button*>(node->getChildByName("buttonHelp"));
    buttonHelp->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GoToHelpScene, this));

    ui::Button* buttonSetting =  static_cast<ui::Button*>(node->getChildByName("buttonSetting"));
    buttonSetting->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GoToSettingScene, this));
    
    ui::Button* buttonLeaderboard =  static_cast<ui::Button*>(node->getChildByName("buttonLeaderboard"));
    buttonLeaderboard->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GotoLeaderBoardScene, this));
    
    Multiplayer::initialize(GameHelper::randomString(5));
    
    this->addChild(node);

    return true;
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenuScene::GoToChooseRoomScene(Ref* pSender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        
        GKHWrapperCpp gkh;
        if(gkh.isLocalPlayerAuthenticated()){
            // Initialize Multiplayer
            if(Multiplayer::getInstance()->isConnected()){
                auto scene = ChooseRoomScene::createScene();
                Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene));
            }else{
                LoadingLayer::AddLoadingLayer(static_cast<Node*>(this));
                Multiplayer::getInstance()->connect(this);
                LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "connecting to Server...", 30.0f);
            }
        }else{
            MessageBox("Player is not signed in", "Game Center Unavailable");
        }
    }
}


void MainMenuScene::GoToHelpScene(Ref* pSender, Widget::TouchEventType type)
{
    auto scene = HelpScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}


void MainMenuScene::GoToSettingScene(Ref* pSender, ui::Widget::TouchEventType type)
{
    auto scene = SettingScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void MainMenuScene::GotoLeaderBoardScene(Ref* pSender, ui::Widget::TouchEventType type)
{
    GKHWrapperCpp gkh;
    gkh.showLeaderBoard();

}

void MainMenuScene::onConnectDone()
{
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "Joining lobby...", 33.3f);
    Multiplayer::joinLobby(this);
}

void MainMenuScene::onJoinLobbyDone()
{
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), false, "Subscribing lobby...", 66.7f);
    Multiplayer::subscribeLobby(this);
}

void MainMenuScene::onSubscribeLobbyDone()
{
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), true, "Done", 100.0f);
    auto scene = ChooseRoomScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene));
}

