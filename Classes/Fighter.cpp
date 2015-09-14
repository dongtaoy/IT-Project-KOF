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
    this->sprite->setSpriteFrame((boost::format("characters/%s/Animation/stand/00.png") % name).str());
    this->stand();
}


void Fighter::update(float)
{
    auto visibleSize = Director::getInstance()->getWinSize();
    auto playerBox = this->getBoundingBox();
    auto opponentBox = opponent->getBoundingBox();
    auto backgroundbox = this->getSprite()->getParent()->getContentSize();
    

    if ((std::abs(this->getPosition().x - opponent->getPosition().x) + playerBox.size.width / 2 + opponentBox.size.width / 2 + 2 * CAMERA_FIGHTER_OFFSET ) * this->sprite->getParent()->getScaleX() > visibleSize.width)
    {
        if (this->getPosition().x > opponent->getPosition().x)
        {
            auto x = visibleSize.width / this->getParent()->getScaleX() + opponent->getPosition().x - playerBox.size.width / 2 - opponentBox.size.width / 2 - 2 * CAMERA_FIGHTER_OFFSET;
            this->setPosition(Vec2(x-5, this->getPosition().y));
        }
        else
        {
            auto x = visibleSize.width / this->getParent()->getScaleX() - opponent->getPosition().x - playerBox.size.width / 2 - opponentBox.size.width / 2 - 2 * CAMERA_FIGHTER_OFFSET;
            this->setPosition(Vec2(-x+5, this->getPosition().y));
        }
    }
    
//    CCLOG("%f %f ", visibleSize.width - opponent->getScreenPosition().x - (opponentBox.size.width/2 + playerBox.size.width/2) * this->getParent()->getScaleX() - 2 * CAMERA_FIGHTER_OFFSET, this->getScreenPosition().x);
//    
//    if (std::abs(this->getScreenPosition().x - opponent->getScreenPosition().x) + (opponentBox.size.width/2 + playerBox.size.width/2) * this->getParent()->getScaleX() + 2 * CAMERA_FIGHTER_OFFSET > visibleSize.width )
//    {
//        CCLOG("in");
//        if (this->getPosition().x > opponent->getPosition().x)
//        {
//            auto x = visibleSize.width + opponent->getScreenPosition().x - (opponentBox.size.width/2 + playerBox.size.width/2) * this->getParent()->getScaleX() - 2 * CAMERA_FIGHTER_OFFSET;
//            this->setPosition(this->getParent()->convertToNodeSpace(Vec2(x, this->getScreenPosition().y)));
//        }
//        else
//        {
//            auto x = visibleSize.width - opponent->getScreenPosition().x - (opponentBox.size.width/2 + playerBox.size.width/2) * this->getParent()->getScaleX() - 2 * CAMERA_FIGHTER_OFFSET;
//            this->setPosition(this->getParent()->convertToNodeSpace(Vec2(-x, this->getScreenPosition().y)));
//        }
//        
//    }
    
    if (this->getPosition().x - (playerBox.size.width / 2) - CAMERA_FIGHTER_OFFSET < 0)
    {
        this->setPosition(Vec2((playerBox.size.width / 2) + CAMERA_FIGHTER_OFFSET , this->getPosition().y));
    }
    
    if (this->getPosition().x + (playerBox.size.width / 2) + CAMERA_FIGHTER_OFFSET > backgroundbox.width)
    {
        this->setPosition(Vec2(backgroundbox.width - (playerBox.size.width / 2) - CAMERA_FIGHTER_OFFSET, this->getPosition().y));
    }
    
    
}


Vec2 Fighter::getPosition()
{
    return this->sprite->getPosition();
}

void Fighter::setPosition(Vec2 pos)
{
    this->sprite->setPosition(pos);
}

Rect Fighter::getBoundingBox()
{
    return this->sprite->getBoundingBox();
}

Vec2 Fighter::getScreenPosition()
{
    return this->sprite->getParent()->convertToWorldSpace(this->getPosition());
}

Node* Fighter::getParent()
{
    return this->sprite->getParent();
}


bool Fighter::canMove(Vec2 displacement)
{
//    auto visibleSize = Director::getInstance()->getWinSize();
//    auto opponentBox = opponent->getSprite()->getBoundingBox();
//    auto playerBox = this->getSprite()->getBoundingBox();
//    auto backgroundbox = this->getSprite()->getParent()->getContentSize();
//    
//    if (displacement.x < 0){
//        if (this->getPosition().x - playerBox.size.width / 2 - CAMERA_FIGHTER_OFFSET + displacement.x   < 0)
//        {
//            return true;
//        }
//    }else{
//        if (this->getPosition().x + playerBox.size.width / 2 + CAMERA_FIGHTER_OFFSET + displacement.x  > backgroundbox.width)
//        {
//            return true;
//        }
//    }
//    
    return true;
}


void Fighter::stand()
{
    if (!isStand() && (this->sprite->getNumberOfRunningActions() < 1 || isActionStoppable()))
    {
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
    if(!canMove(Vec2(CAMERA_FIGHTER_OFFSET,0))){
        this->stand();
        return;
    }
    
    if(!(this->sprite->getActionByTag(ACTION_1_MOVE_FORWARD)) && isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("movefoward");
        auto animate = Animate::create(animation);
        
//        animate->setDuration(ACTION_1_MOVE_DURATION);
        auto animateForever = RepeatForever::create(animate);
        animateForever->setTag(ACTION_1_MOVE_FORWARD);
        auto moveby = MoveBy::create(animate->getDuration(), Vec2(ACTION_MOVE_SPEED, 0));
        auto movebyForever = RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->sprite->runAction(movebyForever);
    }
}

void Fighter::moveBack()
{
//    Vec2 displacement = ;
    
    if(!canMove(Vec2(-CAMERA_FIGHTER_OFFSET,0)))
    {
        this->stand();
        return;
        //displacement = Vec2::ZERO;
    }
    
    if(!(this->sprite->getActionByTag(ACTION_1_MOVE_BACK)) && isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("moveback");
        auto animate = Animate::create(animation);
//        animate->setDuration(ACTION_1_MOVE_DURATION);
        auto animateForever = RepeatForever::create(animate);
        animateForever->setTag(ACTION_1_MOVE_BACK);
        auto moveby = MoveBy::create(animate->getDuration(), Vec2(-ACTION_MOVE_SPEED, 0));
        auto movebyForever = RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->sprite->runAction(movebyForever);
    }
}

void Fighter::jump(Vec2 direction)
{
    Vec2 dispalcement = Vec2(direction.x * ACTION_MOVE_SPEED, 0);
    if(!canMove(dispalcement))
    {
        dispalcement = Vec2::ZERO;
//        return;
    }
    
    if(isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation("jump");
        auto animate = Animate::create(animation);
//        animate->setDuration(.85f);
        auto jumpBy = JumpBy::create(animate->getDuration(), dispalcement, 250.0f, 1);
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
//        animate->setDuration(.5f);
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
//        animate->setDuration(.5f);
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
//        animate->setDuration(.5f);
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
//        animate->setDuration(.5f);
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




