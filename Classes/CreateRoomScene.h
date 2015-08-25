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
#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class CreateRoomScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CreateRoomScene);
    
    
};

#endif /* defined(__KOF__CreateRoomScene__) */
