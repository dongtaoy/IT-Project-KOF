//
//  Fighter.cpp
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#include "Fighter.h"

USING_NS_CC;

Fighter::Fighter(cocos2d::Sprite* sprite, std::string name)
{
    this->sprite = sprite;
    this->sprite->setSpriteFrame((boost::format("charactors/%s/Animation/stand/00.png") % name).str());
    stand();
}

void Fighter::stand()
{
    auto animation = AnimationCache::getInstance()->getAnimation("stand");
    auto animate = Animate::create(animation);
    auto repeat = RepeatForever::create(animate);
    repeat->setTag(10);
    this->sprite->runAction(repeat);
}


void Fighter::moveForward()
{
    if(isStand())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("movefoward");
        auto animate = Animate::create(animation);
        animate->setDuration(1.0f);
        auto sequence = Sequence::create(animate, CallFunc::create([&]{this->stand();}), NULL);
        auto moveby = MoveBy::create(1.0f, Vec2(200,0));
        auto spawn = Spawn::create(sequence, moveby, NULL);
        spawn->setTag(11);
        this->sprite->runAction(spawn);
    }
}

void Fighter::moveBack()
{
    if(isStand())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("moveback");
        auto animate = Animate::create(animation);
        animate->setDuration(1.0f);
        auto sequence = Sequence::create(animate, CallFunc::create([&]{this->stand();}), NULL);
        auto moveby = MoveBy::create(1.0f, Vec2(-200,0));
        
        auto spawn = Spawn::create(sequence, moveby, NULL);
        spawn->setTag(12);
        this->sprite->runAction(spawn);
    }
}

void Fighter::jumpUp()
{
    if(isStand())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("jump");
        auto animate = Animate::create(animation);
        animate->setDuration(1.0f);
        auto sequence = Sequence::create(animate, CallFunc::create([&]{this->stand();}), NULL);
        auto jumpBy = JumpBy::create(1.0f, Vec2(0,0), 250.0f, 1);
//        auto moveby = MoveBy::create(0.5f, Vec2(-100,0));
        auto spawn = Spawn::create(sequence, jumpBy, NULL);
        spawn->setTag(13);
        this->sprite->runAction(spawn);
    }
    
}

void Fighter::jumpForward()
{
    if(isStand())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("jump");
        auto animate = Animate::create(animation);
        animate->setDuration(1.0f);
        auto sequence = Sequence::create(animate, CallFunc::create([&]{this->stand();}), NULL);
        auto jumpBy = JumpBy::create(1.0f, Vec2(200,0), 250.0f, 1);
        auto spawn = Spawn::create(sequence, jumpBy, NULL);
        spawn->setTag(14);
        this->sprite->runAction(spawn);
    }
}

void Fighter::jumpBack()
{
    if(isStand())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("jump");
        auto animate = Animate::create(animation);
        animate->setDuration(1.0f);
        auto sequence = Sequence::create(animate, CallFunc::create([&]{this->stand();}), NULL);
        auto jumpBy = JumpBy::create(1.0f, Vec2(-200,0), 250.0f, 1);
        auto spawn = Spawn::create(sequence, jumpBy, NULL);
        spawn->setTag(15);
        this->sprite->runAction(spawn);
    }
}

void Fighter::kick1()
{
    if(isStand())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("kick1");
        auto animate = Animate::create(animation);
        animate->setDuration(.5f);
        auto sequence = Sequence::create(animate, CallFunc::create([&]{this->stand();}), NULL);
        sequence->setTag(16);
        this->sprite->runAction(sequence);
    }
}

void Fighter::kick2()
{
    if(isStand())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("kick2");
        auto animate = Animate::create(animation);
        animate->setDuration(.5f);
        auto sequence = Sequence::create(animate, CallFunc::create([&]{this->stand();}), NULL);
        sequence->setTag(17);
        this->sprite->runAction(sequence);
    }
}

void Fighter::punch1()
{
    if(isStand())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("punch1");
        auto animate = Animate::create(animation);
        animate->setDuration(.5f);
        auto sequence = Sequence::create(animate, CallFunc::create([&]{this->stand();}), NULL);
        sequence->setTag(18);
        this->sprite->runAction(sequence);
    }
}

void Fighter::punch2()
{
    if(isStand())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("punch2");
        auto animate = Animate::create(animation);
        animate->setDuration(.5f);
        auto sequence = Sequence::create(animate, CallFunc::create([&]{this->stand();}), NULL);
        sequence->setTag(19);
        this->sprite->runAction(sequence);
    }
}


bool Fighter::isStand()
{
    if(this->sprite->getActionByTag(10))
        return true;
    return false;
}

