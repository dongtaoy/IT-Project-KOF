//
//  MainMenuScene.h
//  KOF
//
//  Created by Dongtao Yu on 12/08/2015.
//
//

#ifndef __KOF__MainMenuScene__
#define __KOF__MainMenuScene__

#include "cocos2d.h"

#include "definitions.h"
#include "Multiplayer.h"
#include "ChooseRoomScene.h"
#include "HelpScene.h"
#include "SettingScene.h"
#include "LoadingLayer.h"
#include "GKHWrapperCpp.h"
#include "GameHelper.h"



class MainMenuScene : public cocos2d::Layer, public AppWarp::ConnectionRequestListener
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
    
private:
    //TODO: comments
    void GoToChooseRoomScene(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    //TODO: comments
    void GoToHelpScene(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    //TODO: comments
    void GoToSettingScene(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    //TODO: comments
    void GotoLeaderBoardScene(cocos2d::Ref*, ui::Widget::TouchEventType type);
    
    
    // ConnectionRequestListener
    void onConnectDone(int,int);
};

#endif /* defined(__KOF__MainMenuScene__) */
