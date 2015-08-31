//
//  ChooseCharactorScene.h
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#ifndef __KOF__ChooseCharactorScene__
#define __KOF__ChooseCharactorScene__

#include <stdio.h>
#include "cocos2d.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "ChooseRoomScene.h"


class ChooseCharactorScene : public cocos2d::Layer
{
public:
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(ChooseCharactorScene);
    
private:
    
    void GotoChooseRoomSceneScene(Ref*);
    void CountDownTask(float);
    
    
};

#endif /* defined(__KOF__ChooseCharactorScene__) */
