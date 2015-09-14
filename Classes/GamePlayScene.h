//
//  GamePlayScene.h
//  KOF
//
//  Created by Dongtao Yu on 6/09/2015.
//
//

#ifndef __KOF__GamePlayScene__
#define __KOF__GamePlayScene__

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "Definitions.h"
#include "Multiplayer.h"
#include "MainMenuScene.h"
#include "LoadingLayer.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "Fighter.h"
#include "Camera2d.h"

class GamePlayScene : public cocos2d::Layer, public AppWarp::NotificationListener, public AppWarp::RoomRequestListener
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlayScene);
    
    CC_SYNTHESIZE(std::string, playerCharacter, PlayerCharacter);
    CC_SYNTHESIZE(std::string, opponentCharacter, OpponentCharacter);
    
    CC_SYNTHESIZE(Fighter*, player, Player);
    CC_SYNTHESIZE(Fighter*, opponent, Opponent);
    CC_SYNTHESIZE(cocos2d::Sprite*, background, Background);
    
    
    CC_SYNTHESIZE(SneakyButton*, buttonA, ButtonA);
    CC_SYNTHESIZE(SneakyButton*, buttonB, ButtonB);
    CC_SYNTHESIZE(SneakyButton*, buttonC, ButtonC);
    CC_SYNTHESIZE(SneakyButton*, buttonD, ButtonD);
    
    
private:
    
//    std::string playerCharacter;
//    std::string opponentCharacter;
//
    
//    Fighter* player;
//    Fighter* opponent;
    Camera2d* camera;
    
    
    SneakyJoystick* joystick;
    
    void startGame();
    void PauseClicked(Ref*, ui::Widget::TouchEventType);
    void ResumeClicked(Ref*, ui::Widget::TouchEventType);
    void MenuClicked(Ref*, ui::Widget::TouchEventType);
    
    
//    void buttonAClicked(Ref*, ui::Widget::TouchEventType);
//    void buttonBClicked(Ref*, ui::Widget::TouchEventType);
//    void buttonCClicked(Ref*, ui::Widget::TouchEventType);
//    void buttonDClicked(Ref*, ui::Widget::TouchEventType);
    
    void createJoystick();
    SneakyButton* createButtons(std::string, std::string, Vec2);
    void createBackgroundAnimation();
    
    void update(float);
    
    // Listener
    void onChatReceived(AppWarp::chat);
    void onUserLeftRoom(AppWarp::room, std::string);
    
    
    void onUnsubscribeRoomDone(AppWarp::room);
    void onLeaveRoomDone(AppWarp::room);
};


#endif /* defined(__KOF__GamePlayScene__) */
