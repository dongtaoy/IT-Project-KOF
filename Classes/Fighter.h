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
#include <boost/format.hpp>

class Fighter
{
    
public:
    Fighter(cocos2d::Sprite*, std::string);
    CC_SYNTHESIZE(cocos2d::Sprite*, sprite, Sprite);
    
    void stand();
    void moveForward();
    void moveBack();
    void jumpUp();
    void jumpForward();
    void jumpBack();
    void kick1();
    void kick2();
    void punch1();
    void punch2();
    
    bool isStand();
//private:
    
    
    
    
    
};


#endif /* defined(__KOF__Fighter__) */
