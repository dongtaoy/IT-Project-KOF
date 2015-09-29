//
//  ChooseCharacterScene.h
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#ifndef __KOF__ChooseCharacterScene__
#define __KOF__ChooseCharacterScene__

#include <stdio.h>
#include "cocos2d.h"
#include "Definitions.h"
#include "ChooseRoomScene.h"
#include "cocostudio/CocoStudio.h"
#include "GameHelper.h"
#include "GamePlayScene.h"
#include "Multiplayer.h"
#include "MultiplayerCallback.h"
#include <boost/format.hpp>
#include <boost/lockfree/queue.hpp>


class ChooseCharacterScene : public cocos2d::Layer, public MultiplayerCallback
{
public:
#pragma mark init
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(ChooseCharacterScene);
    
private:
#pragma mark varibles
    std::string playerSelected;
    std::string opponentSelected;
    bool playerReady;
    bool opponentReady;
    bool isCountdownStart;
    
#pragma mark getter/setter
    void setPlayerSelected(std::string);
    void setOpponentSelected(std::string);
    void setPlayerReady(bool);
    void setOpponentReady(bool);
    
#pragma mark go/ready buttons
    void ResetGoReadyButton();
    void CheckBothReady();
    void SetReadyButtonVisible(bool, bool);
    void SetGoButtonVisible(bool, bool);
    
#pragma mark select charactor
    void ShowSelectedBorder(std::string);
    void RemoveSelectedBorder(std::string);
    void ShowSelectedCharacter(std::string, bool);
    
#pragma mark listeners
    void ButtonReadyClicked(Ref*, ui::Widget::TouchEventType);
    void ButtonGoClicked(Ref*, ui::Widget::TouchEventType);
    void CharacterClicked(Ref*, ui::Widget::TouchEventType);
    void ButtonBackClicked(Ref*, ui::Widget::TouchEventType);

#pragma mark command
    void StartGame();
    void update(float);
    void processCommand(command_t);
    
#pragma mark listeners
    void onLeaveRoomDone();
    void onUnsubscribeRoomDone();
};

#endif /* defined(__KOF__ChooseCharacterScene__) */
