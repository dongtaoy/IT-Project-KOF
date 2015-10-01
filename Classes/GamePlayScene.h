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
#include <math.h>
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
#include "MultiplayerCallback.h"

class GamePlayScene : public cocos2d::Layer, public MultiplayerCallback
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
    Camera2d* camera;
    bool isCountDownStart;
    
    
    SneakyJoystick* joystick;
    
    void startGame();
    void PauseClicked(Ref*, ui::Widget::TouchEventType);
    void ResumeClicked(Ref*, ui::Widget::TouchEventType);
    void MenuClicked(Ref*, ui::Widget::TouchEventType);
    
    void createJoystick();
    
    SneakyButton* createButtons(std::string, std::string, Vec2);
    
    void createBackgroundAnimation();
    
    void startCountDown();
    
    void countDownTask(float);
    
    void endCountDown();
    
    
    void update(float);
    
    
    void onUnsubscribeRoomDone();
    void onLeaveRoomDone();
    
    cocos2d::PhysicsWorld *sceneWorld;
    
    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
    
    bool onContactBegin( cocos2d::PhysicsContact &contact);
    void addEdgeBoxForCharacter(Node* sprite, float x, float y, int bitmask);
    void updatePlayerHp();
    void characterTooClose(float characterDistance, float closeDistance);
    
};


#endif /* defined(__KOF__GamePlayScene__) */
