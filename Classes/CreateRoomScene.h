//
//  CreateRoomScene.h
//  KOF
//
//  Created by Dongtao Yu on 25/08/2015.
//
//

#ifndef __KOF__CreateRoomScene__
#define __KOF__CreateRoomScene__

#include <stdio.h>
#include "ChooseRoomScene.h"
#include "Definitions.h"
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocostudio/CCObjectExtensionData.h"
#include "Multiplayer.h"

class CreateRoomScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CreateRoomScene);
private:
    Ref* backgroundSelected;
    Ref* bestOfSelected;
    void CheckboxSelectedChanged(Ref*, cocos2d::ui::CheckBox::EventType);
    void GotoChooseRoomScene(Ref*, ui::Widget::TouchEventType);
    void RemoveSelectedBorder(Ref*);
    void ShowSelectedBorder(Ref*);
    void CreateRoom(Ref*, ui::Widget::TouchEventType);
    void BackgroundSelectedChanged(Ref*, ui::Widget::TouchEventType);
    
};

#endif /* defined(__KOF__CreateRoomScene__) */
