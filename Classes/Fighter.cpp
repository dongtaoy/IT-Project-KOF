//
//  Fighter.cpp
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#include "Fighter.h"

USING_NS_CC;

Fighter::Fighter(Sprite* sprite, std::string name)
{
    this->sprite = sprite;
    this->sprite->setSpriteFrame((boost::format("charactors/%s/Animation/stand/00.png") % name).str());
    
    this->stand();
}


void Fighter::update(float)
{
//    if(isStand())
//    {
//        //this->sprite->setPosition(toScreenCoord(background, this));
//    }
    
}
Vec2 Fighter::getPosition()
{
    return this->sprite->getPosition();
}


//Vec2 Fighter::toBackgroundCoord(cocos2d::Sprite* background, Fighter* fighter)
//{
//    return Vec2(background->getContentSize().width * background->getScaleX() / 2 - background->getPosition().x + fighter->getSprite()->getPosition().x,
//                background->getContentSize().height * background->getScaleY() / 2 - background->getPosition().y + fighter->getSprite()->getPosition().y);
//}
//
//Vec2 Fighter::toScreenCoord(cocos2d::Sprite* background, Fighter* fighter)
//{
//    return Vec2( fighter->getPos().x - (background->getContentSize().width * background->getScaleX() / 2 - background->getPosition().x ),
//                 fighter->getPos().y - (background->getContentSize().height * background->getScaleY() / 2 - background->getPosition().y ));
//}


void Fighter::stand()
{
    if (!isStand() && (this->sprite->getNumberOfRunningActions() < 1 || isActionStoppable()))
    {
        CCLOG("stand in");
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("stand");
        auto animate = Animate::create(animation);
        auto repeat = RepeatForever::create(animate);
        repeat->setTag(ACTION_1_STAND);
        this->sprite->runAction(repeat);
    }
}


void Fighter::moveForward()
{
    if(!(this->sprite->getActionByTag(ACTION_1_MOVE_FORWARD)) && isActionStoppable())
    {
        
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("movefoward");
        auto animate = Animate::create(animation);
        animate->setDuration(ACTION_1_MOVE_DURATION);
        auto animateForever = RepeatForever::create(animate);
        animateForever->setTag(ACTION_1_MOVE_FORWARD);
        auto moveby = MoveBy::create(ACTION_1_MOVE_DURATION, Vec2(ACTION_MOVE_SPEED, 0));
        auto movebyForever = RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->sprite->runAction(movebyForever);
    }
}

void Fighter::moveBack()
{
    if(!(this->sprite->getActionByTag(ACTION_1_MOVE_BACK)) && isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("moveback");
        auto animate = Animate::create(animation);
        animate->setDuration(ACTION_1_MOVE_DURATION);
        auto animateForever = RepeatForever::create(animate);
        animateForever->setTag(ACTION_1_MOVE_BACK);
        auto moveby = MoveBy::create(ACTION_1_MOVE_DURATION, Vec2(-ACTION_MOVE_SPEED, 0));
        auto movebyForever = RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->sprite->runAction(movebyForever);
    }
}

void Fighter::jump(Vec2 direction)
{
    if(isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("jump");
        auto animate = Animate::create(animation);
        animate->setDuration(.85f);
        auto jumpBy = JumpBy::create(.85f, Vec2(ACTION_JUMP_SPEED * direction.x ,0), 250.0f, 1);
        auto spawn = Spawn::create(animate, jumpBy, NULL);
        auto callFunc = CallFunc::create([&]{this->sprite->stopAllActions();this->stand();});
        auto sequence = Sequence::create(spawn, callFunc, NULL);
        sequence->setTag(ACTION_JUMP);
        this->sprite->runAction(sequence);
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
    if(this->sprite->getActionByTag(ACTION_1_STAND))
        return true;
    return false;
}

bool Fighter::isActionStoppable()
{
    if (this->sprite->getActionByTag(ACTION_1_MOVE_FORWARD)
        || this->sprite->getActionByTag(ACTION_1_MOVE_BACK)
        || this->sprite->getActionByTag(ACTION_1_STAND))
        return true;
    return false;
}




