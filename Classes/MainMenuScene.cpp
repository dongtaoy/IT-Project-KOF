//
//  MainMenuScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#include "MainMenuScene.h"


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
    
    
    auto node = CSLoader::createNode("MainMenu.csb");
    ui::Button* buttonMultiplayer =  static_cast<ui::Button*>(node->getChildByName("buttonMultiplayer"));
    buttonMultiplayer->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GoToChooseRoomScene, this));
    
    ui::Button* buttonHelp =  static_cast<ui::Button*>(node->getChildByName("buttonHelp"));
    buttonHelp->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GoToHelpScene, this));

    ui::Button* buttonSetting =  static_cast<ui::Button*>(node->getChildByName("buttonSetting"));
    buttonSetting->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GoToSettingScene, this));
    
    ui::Button* buttonLeaderboard =  static_cast<ui::Button*>(node->getChildByName("buttonLeaderboard"));
    buttonLeaderboard->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::GotoLeaderBoardScene, this));
    
    ui::Button* buttonFacebook = node->getChildByName<ui::Button*>(FB_BUTTON);
    buttonFacebook->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::facebookClicked, this));
    
    ui::Button* buttonTwitter = node->getChildByName<ui::Button*>(TW_BUTTON);
    buttonTwitter->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::twitterClicked, this));
    
    
    PhotonMultiplayer::initialize(GameHelper::randomString(5).c_str());
    PhotonMultiplayer::getInstance()->setListener(this);
    this->scheduleUpdate();
    
    this->addChild(node);

    return true;
}


void MainMenuScene::update(float dt)
{
    PhotonMultiplayer::getInstance()->service();
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenuScene::GoToChooseRoomScene(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
        
        if (!PhotonMultiplayer::getInstance()->isConnected())
        {
            PhotonMultiplayer::getInstance()->connect();
            LoadingLayer::SetTextAndLoadingBar(this, false, "Connecting....", 50.0f);
        }
        else
        {
            auto scene = ChooseRoomScene::createScene();
            Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene));
        }
    }
}

void MainMenuScene::facebookClicked(cocos2d::Ref *, ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED) {
        SonarCocosHelper::Facebook::Share("", "", "This is a really fun game", "", "");
    }
}

void MainMenuScene::twitterClicked(cocos2d::Ref *, ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED) {
        SonarCocosHelper::Twitter::Tweet("This is a really fun game", "", "");
    }
}


void MainMenuScene::GoToHelpScene(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
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
    SonarCocosHelper::GameCenter::showLeaderboard();
}

void MainMenuScene::onConnectDone()
{
    LoadingLayer::SetTextAndLoadingBar(static_cast<Node*>(this), true, "DONE...", 100.0f);
    auto scene = ChooseRoomScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene));
}

