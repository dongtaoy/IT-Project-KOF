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
#include <boost/format.hpp>
#include <boost/lockfree/queue.hpp>


class ChooseCharacterScene : public cocos2d::Layer, public AppWarp::RoomRequestListener, public AppWarp::NotificationListener
{
public:
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(ChooseCharacterScene);
    
private:
    
    std::string playerSelected;
    std::string opponentSelected;
    
    void setPlayerSelected(std::string);
    void setOpponentSelected(std::string);
    void setPlayerReady(bool);
    void setOpponentReady(bool);
    
    bool playerReady;
    bool opponentReady;
    bool isCountdownStart;
    
    
    void SetGoButtonVisible(bool, bool);
    void SetReadyButtonVisible(bool, bool);
    void ResetGoReadyButton();
    void CheckBothReady();
    
    
    void ShowSelectedBorder(std::string);
    void RemoveSelectedBorder(std::string);
    void ShowSelectedCharacter(std::string, bool);
    
    
    void CountDownTask(float);
    void ResetCountDown();
    void EndCountDown();
    void StartCountDown();
    
    
    void ButtonReadyClicked(Ref*, ui::Widget::TouchEventType);
    void ButtonGoClicked(Ref*, cocos2d::ui::Widget::TouchEventType);
    void CharacterClicked(Ref*, ui::Widget::TouchEventType);
    void ButtonBackClicked(Ref*, ui::Widget::TouchEventType);

    void sendStatusMessage(float);
   
    void setRequiredListener();
    void onUnsubscribeRoomDone(AppWarp::room);
    void onLeaveRoomDone(AppWarp::room);
    void onUserJoinedRoom(AppWarp::room, std::string);
    void onUserLeftRoom(AppWarp::room, std::string);
    void onChatReceived(AppWarp::chat);
    void StartGame();
    
    void update(float);
};

#endif /* defined(__KOF__ChooseCharacterScene__) */
