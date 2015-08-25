//
//  SettingScene.h
//  KOF
//
//  Created by Dongtao Yu on 15/08/2015.
//
//

#ifndef __KOF__SettingScene__
#define __KOF__SettingScene__

#include <stdio.h>
#include "cocos2d.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"

class SettingScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SettingScene);
    
private:
    void GotoMainMenuScene(Ref* pSender, ui::Widget::TouchEventType type);
    
    
};


#endif /* defined(__KOF__SettingScene__) */
