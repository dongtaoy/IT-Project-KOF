//
//  ChooseRoomScene.h
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#ifndef __KOF__ChooseRoomScene__
#define __KOF__ChooseRoomScene__

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "CocosGUI.h"

#include "Definitions.h"
#include "MainMenuScene.h"
#include "CreateRoomScene.h"
#include "ChooseCharacterScene.h"
#include "Multiplayer.h"

#include "appwarp.h"


class ChooseRoomScene : public Layer, public MultiplayerCallback
{
public:
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ChooseRoomScene);
    
private:
//    void test(MainMenuScene*);
    
    bool isFirstTimeLaunch;
    
    void GotoMainMenuScene(Ref*, ui::Widget::TouchEventType);
    
    void GotoCreateRoomScene(Ref*, ui::Widget::TouchEventType);
    
    void OnSelectedItem(Ref* pSender, ui::Widget::TouchEventType);
    
    
    void onUnsubscribeLobbyDone();
    void onLeaveLobbyDone();
//    
    // RoomRequestListner
    void onGetLiveRoomInfoDone(std::string roomId,
                               std::string owner,
                               int maxUsers,
                               std::string name,
                               std::string customData,
                               std::vector<std::string> users,
                               std::map<std::string, std::string> properties);
    
    void onJoinRoomDone();
    void onSubscribeRoomDone();
    void onRoomDestroyed(std::string);
    
    // Search Roomt
    void SearchRoom(Ref*, ui::Widget::TouchEventType);
    
    

};

#endif /* defined(__KOF__ChooseRoomScene__) */
