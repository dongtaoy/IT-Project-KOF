//
//  Fighter.cpp
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#include "Fighter.h"


Fighter::Fighter(cocos2d::Sprite* sprite, std::string name)
{
    this->sprite = sprite;
    this->sprite->setSpriteFrame((boost::format("charactors/%s/Animation/stand/00.png") % name).str());
//    this->sprite->runAction(AnimationC);
}
