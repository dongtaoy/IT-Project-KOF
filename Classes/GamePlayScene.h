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
#include "Multiplayer.h"

class GamePlayScene : public cocos2d::Layer, public AppWarp::NotificationListener
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlayScene);
    
    void onChatReceived(AppWarp::chat);
    
};


#endif /* defined(__KOF__GamePlayScene__) */
