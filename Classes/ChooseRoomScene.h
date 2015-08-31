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
#include "ChooseCharactorScene.h"
#include "Multiplayer.h"

#include "appwarp.h"


class ChooseRoomScene : public Layer, public AppWarp::RoomRequestListener
{
public:
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    

    // implement the "static create()" method manually
    CREATE_FUNC(ChooseRoomScene);
    
private:
    
    bool isFirstTimeLaunch;
    
    void GotoMainMenuScene(Ref*, ui::Widget::TouchEventType);
    
    void GotoCreateRoomScene(Ref*, ui::Widget::TouchEventType);
    
    void OnSelectedItem(Ref* pSender, ui::ListView::EventType);
    
    // RoomRequestListner
    void onGetLiveRoomInfoDone(AppWarp::liveroom);
};

#endif /* defined(__KOF__ChooseRoomScene__) */
