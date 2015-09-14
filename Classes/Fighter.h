//
//  Fighter.h
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#ifndef __KOF__Fighter__
#define __KOF__Fighter__

#include <stdio.h>
#include "cocos2d.h"
#include "Definitions.h"
#include <boost/format.hpp>


class Fighter
{
    
public:
    Fighter(cocos2d::Sprite*, std::string);
    CC_SYNTHESIZE(cocos2d::Sprite*, sprite, Sprite);
    CC_SYNTHESIZE(Fighter*, opponent, Opponent);
    CC_SYNTHESIZE(std::string, name, Name);
    
    void stand();
    void moveForward();
    void moveBack();
    void jump(cocos2d::Vec2);
    void kick1();
    void kick2();
    void punch1();
    void punch2();
    
    void update(float);
    
    cocos2d::Vec2 getPosition();
    void setPosition(cocos2d::Vec2);
    cocos2d::Vec2 getScreenPosition();
    cocos2d::Rect getBoundingBox();
    cocos2d::Node* getParent();
    
private:
    bool isStand();
    bool isActionStoppable();
    bool canMove(cocos2d::Vec2);
    
//    static cocos2d::Vec2 toBackgroundCoord(cocos2d::Sprite*, Fighter*);
//    static cocos2d::Vec2 toScreenCoord(cocos2d::Sprite*, Fighter*);
//private:
    
    
    
    
    
};


#endif /* defined(__KOF__Fighter__) */
