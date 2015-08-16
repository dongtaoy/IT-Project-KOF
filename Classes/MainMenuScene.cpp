//
//  MainMenuScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#include "MainMenuScene.h"

USING_NS_CC;

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // Multiplayer Button
    Label *multiLabel = Label::createWithTTF("MULTIPLE PLAYER", "fonts/Marker Felt.ttf", 20);
    multiLabel->setColor(Color3B::WHITE);
    MenuItemLabel *multiButton = MenuItemLabel::create(multiLabel, CC_CALLBACK_1(MainMenuScene::GoToChooseRoomScene, this));
    multiButton->setPosition(visibleSize.width / 5 + origin.x, visibleSize.height * 5 / 6 + origin.y);
    Menu *multiMenu = Menu::create(multiButton, NULL);
    multiMenu->setPosition(Point::ZERO);
    this->addChild(multiMenu, 1);
    
    
    // Help Button
    Label *helpLabel = Label::createWithTTF("HELP", "fonts/Marker Felt.ttf", 20);
    helpLabel->setColor(Color3B::WHITE);
    MenuItemLabel *helpButton = MenuItemLabel::create(helpLabel, CC_CALLBACK_1(MainMenuScene::GoToHelpScene, this));
    helpButton->setPosition(visibleSize.width / 5 + origin.x, visibleSize.height * 4 / 6 + origin.y);
    Menu *helpMenu = Menu::create(helpButton, NULL);
    helpMenu->setPosition(Point::ZERO);
    this->addChild(helpMenu, 1);
    
    //Leader Border Button
    Label *leaderBoardLabel = Label::createWithTTF("LEADERBOARD", "fonts/Marker Felt.ttf", 20);
    leaderBoardLabel->setColor(Color3B::WHITE);
    MenuItemLabel *leaderBoardButton = MenuItemLabel::create(leaderBoardLabel, CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    leaderBoardButton->setPosition(visibleSize.width / 5 + origin.x, visibleSize.height * 3 / 6 + origin.y);
    Menu *leaderBoardMenu = Menu::create(leaderBoardButton, NULL);
    leaderBoardMenu->setPosition(Point::ZERO);
    this->addChild(leaderBoardMenu, 1);
    
    // Setting Button
    Label *settingLabel = Label::createWithTTF("SETTING", "fonts/Marker Felt.ttf", 20);
    settingLabel->setColor(Color3B::WHITE);
    MenuItemLabel *settingButton = MenuItemLabel::create(settingLabel, CC_CALLBACK_1(MainMenuScene::GoToSettingScene, this));
    settingButton->setPosition(visibleSize.width / 5 + origin.x, visibleSize.height * 2 / 6 + origin.y);
    Menu *settingMenu = Menu::create(settingButton, NULL);
    settingMenu->setPosition(Point::ZERO);
    this->addChild(settingMenu, 1);
    

    return true;
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenuScene::GoToChooseRoomScene(cocos2d::Ref* pSender)
{
    auto scene = ChooseRoomScene::createScene();
    
    Director::getInstance()->replaceScene( TransitionFade::create( TRANSITION_TIME, scene) );
}


void MainMenuScene::GoToHelpScene(Ref* pSender)
{
    auto scene = HelpScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}


void MainMenuScene::GoToSettingScene(Ref* pSender)
{
    auto scene = SettingScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

