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
    this->name = name;
    this->sprite = sprite;
    this->sprite->setSpriteFrame((boost::format(CHARACTER_INITIAL_FRAME) % name).str());
    this->start();
   
}


void Fighter::update(float)
{
    auto visibleSize = Director::getInstance()->getWinSize();
    auto playerBox = this->getBoundingBox();
    auto opponentBox = opponent->getBoundingBox();
    auto backgroundbox = this->getSprite()->getParent()->getContentSize();
    
//    if (getPosition().x)
//    CCLOG("PLAYER")
    
//    if ((std::abs(this->getPosition().x - opponent->getPosition().x) + playerBox.size.width / 2 + opponentBox.size.width / 2 + 2 * CAMERA_FIGHTER_OFFSET ) * this->sprite->getParent()->getScaleX() > visibleSize.width)
//    {
//        if (this->getPosition().x > opponent->getPosition().x)
//        {
//            auto x = visibleSize.width / this->getParent()->getScaleX() + opponent->getPosition().x - playerBox.size.width / 2 - opponentBox.size.width / 2 - 2 * CAMERA_FIGHTER_OFFSET;
//            this->setPosition(Vec2(x-5, this->getPosition().y));
//        }
//        else
//        {
//            auto x = visibleSize.width / this->getParent()->getScaleX() - opponent->getPosition().x - playerBox.size.width / 2 - opponentBox.size.width / 2 - 2 * CAMERA_FIGHTER_OFFSET;
//            this->setPosition(Vec2(-x+5, this->getPosition().y));
//        }
//    }
    
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



void Fighter::stand()
{
    if (!isStand() && (this->sprite->getNumberOfRunningActions() < 1 || isActionStoppable()))
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND)%name).str());
        auto animate = Animate::create(animation);
        auto repeat = RepeatForever::create(animate);
        repeat->setTag(OP_GPS_ACTION_1_STAND);
        this->sprite->runAction(repeat);
    }
}

void Fighter::stand_hit()
{
    
}

void Fighter::stand_jump(int distance)
{
    if (!this->sprite->getActionByTag(ACTION_UNSTOPPABLE))
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_JUMP)%name).str());
        auto animate = Animate::create(animation);
        animate->setTag(OP_GPS_ACTION_2_STAND_JUMP);
        this->sprite->runAction(animate);
        JumpBy* jumpBy;
        if (checkBoundary(distance))
            jumpBy = JumpBy::create(animate->getDuration(), Vec2(distance, 0), 300.0f, 1);
        else
            jumpBy = JumpBy::create(animate->getDuration(), Vec2(0, 0), 300.0f, 1);
        jumpBy->setTag(ACTION_UNSTOPPABLE);
        this->sprite->runAction(jumpBy);
    }
}



void Fighter::stand_moveback(int x)
{
    if (!this->sprite->getActionByTag(ACTION_UNSTOPPABLE))
    {
        if (!this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEBACK))
        {
            this->sprite->stopAllActions();
            auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_MOVEBACK)%name).str());
            auto animate = Animate::create(animation);
            auto animateForever = RepeatForever::create(animate);
            animateForever->setTag(OP_GPS_ACTION_1_STAND_MOVEBACK);
            this->sprite->runAction(animateForever);
        }
        if (checkBoundary(-ACTION_MOVE_SPEED))
        {
            auto moveTo = MoveTo::create(0.2f, Vec2(x, getPosition().y));
            //            auto moveby = MoveBy::create(0.2f, Vec2(ACTION_?MOVE_SPEED, 0));
            //            moveby->setTag(ACTION_UNSTOPPABLE);
            this->sprite->runAction(moveTo);
        }
    }
}

void Fighter::stand_moveforward(int x)
{
    
    if (!this->sprite->getActionByTag(ACTION_UNSTOPPABLE))
    {
        if (!this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD))
        {
            this->sprite->stopAllActions();
            auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_MOVEFORWARD)%name).str());
            auto animate = Animate::create(animation);
            auto animateForever = RepeatForever::create(animate);
            animateForever->setTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD);
            this->sprite->runAction(animateForever);
        }
        if (checkBoundary(ACTION_MOVE_SPEED))
        {
            auto moveTo = MoveTo::create(0.2f, Vec2(x, getPosition().y));
//            auto moveby = MoveBy::create(0.2f, Vec2(ACTION_?MOVE_SPEED, 0));
//            moveby->setTag(ACTION_UNSTOPPABLE);
            this->sprite->runAction(moveTo);
        }
    }
}




void Fighter::squat()
{
    if (!(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT)))
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT)%name).str());
        auto animate = Animate::create(animation);
        auto repeat = RepeatForever::create(animate);
        repeat->setTag(OP_GPS_ACTION_1_SQUAT);
        this->sprite->runAction(repeat);
        
    }
}

void Fighter::squat_down()
{
    if (!(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_DOWN)) && !(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT)) && isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT_DOWN)%name).str());
        auto animate = Animate::create(animation);
        auto func = CallFunc::create([&]{this->sprite->stopAllActions();this->squat();});
        auto sequence = Sequence::create(animate, func, NULL);
        sequence->setTag(OP_GPS_ACTION_1_SQUAT_DOWN);
        this->sprite->runAction(sequence);
    }
}

void Fighter::squat_hit()
{
    
}


void Fighter::squat_moveback()
{
    if (!this->sprite->getActionByTag(ACTION_UNSTOPPABLE))
    {
        if (!this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEBACK))
        {
            this->sprite->stopAllActions();
            auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT_MOVEBACK)%name).str());
            auto animate = Animate::create(animation);
            auto animateForever = RepeatForever::create(animate);
            animateForever->setTag(OP_GPS_ACTION_1_SQUAT_MOVEBACK);
            this->sprite->runAction(animateForever);
        }
        if (checkBoundary(-ACTION_MOVE_SPEED))
        {
            auto moveby = MoveBy::create(0.2f, Vec2(-ACTION_MOVE_SPEED, 0));
            moveby->setTag(ACTION_UNSTOPPABLE);
            this->sprite->runAction(moveby);
        }
    }
}

void Fighter::squat_moveforward()
{
    if (!this->sprite->getActionByTag(ACTION_UNSTOPPABLE))
    {
        if (!this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD))
        {
            this->sprite->stopAllActions();
            auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT_MOVEFORWARD)%name).str());
            auto animate = Animate::create(animation);
            auto animateForever = RepeatForever::create(animate);
            animateForever->setTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD);
            this->sprite->runAction(animateForever);
        }
        if (checkBoundary(ACTION_MOVE_SPEED))
        {
            auto moveby = MoveBy::create(0.2f, Vec2(ACTION_MOVE_SPEED, 0));
            moveby->setTag(ACTION_UNSTOPPABLE);
            this->sprite->runAction(moveby);
        }
    }
}

void Fighter::squat_up()
{
    
}

void Fighter::start()
{
    this->sprite->stopAllActions();
    auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_START)%name).str());
    auto animate = Animate::create(animation);
    auto sequence = Sequence::create(animate, CallFunc::create([&]{ this->sprite->stopAllActions(); this->stand();}), NULL);
    this->sprite->runAction(sequence);
    
}

void Fighter::win()
{
    this->sprite->stopAllActions();
    auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_WIN)%name).str());
    auto animate = Animate::create(animation);
    this->sprite->runAction(animate);
}

void Fighter::die()
{
    this->sprite->stopAllActions();
    auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_DIE)%name).str());
    auto animate = Animate::create(animation);
    this->sprite->runAction(animate);
}

void Fighter::kick1()
{
    if(isActionStoppable())
    {
        Animation* animation = NULL;
        if (!isSquat())
            animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_KICK1) % name).str());
        else
            animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT_KICK1) % name).str());
        auto animate = Animate::create(animation);
        auto func = [&]{
            if (!this->isSquat()) {
                this->sprite->stopAllActions();
                this->stand();
                return;
            }
            this->squat();
        };
        auto sequence = Sequence::create(animate, CallFunc::create(func), NULL);
        if(!isSquat())
            sequence->setTag(OP_GPS_ACTION_2_STAND_KICK1);
        else
            sequence->setTag(OP_GPS_ACTION_2_SQUAT_KICK1);
        this->sprite->stopAllActions();
        this->sprite->runAction(sequence);
    }
}

void Fighter::kick2()
{
    if(isActionStoppable())
    {
        Animation* animation = NULL;
        if (!isSquat())
            animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_KICK2) % name).str());
        else
            animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT_KICK2) % name).str());
        auto animate = Animate::create(animation);
        auto func = [&]{
            if (!this->isSquat()) {
                this->sprite->stopAllActions();
                this->stand();
                return;
            }
            this->squat();
        };
        auto sequence = Sequence::create(animate, CallFunc::create(func), NULL);
        if(!isSquat())
            sequence->setTag(OP_GPS_ACTION_2_STAND_KICK2);
        else
            sequence->setTag(OP_GPS_ACTION_2_SQUAT_KICK2);
        this->sprite->stopAllActions();
        this->sprite->runAction(sequence);
    }
}

void Fighter::punch1()
{
    if(isActionStoppable())
    {
        Animation* animation = NULL;
        if (!isSquat())
            animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_PUNCH1) % name).str());
        else
            animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT_PUNCH1) % name).str());
        auto animate = Animate::create(animation);
        auto func = [&]{
            if (!this->isSquat()) {
                this->sprite->stopAllActions();
                this->stand();
                return;
            }
            this->squat();
        };
        auto sequence = Sequence::create(animate, CallFunc::create(func), NULL);
        if(!isSquat())
            sequence->setTag(OP_GPS_ACTION_2_STAND_PUNCH1);
        else
            sequence->setTag(OP_GPS_ACTION_2_SQUAT_PUNCH1);
        this->sprite->stopAllActions();
        this->sprite->runAction(sequence);
    }
}

void Fighter::punch2()
{
    if(isActionStoppable())
    {
        Animation* animation = NULL;
        if (!isSquat())
            animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_PUNCH2) % name).str());
        else
            animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT_PUNCH2) % name).str());
        auto animate = Animate::create(animation);
        auto func = [&]{
            if (!this->isSquat()) {
                this->sprite->stopAllActions();
                this->stand();
                return;
            }
            this->squat();
        };
        auto sequence = Sequence::create(animate, CallFunc::create(func), NULL);
        if(!isSquat())
            sequence->setTag(OP_GPS_ACTION_2_STAND_PUNCH2);
        else
            sequence->setTag(OP_GPS_ACTION_2_SQUAT_PUNCH2);
        this->sprite->stopAllActions();
        this->sprite->runAction(sequence);
    }
}


bool Fighter::isStand()
{
    if(this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND))
        return true;
    return false;
}

bool Fighter::isSquat()
{
    if (   this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_DOWN)
        || this->sprite->getActionByTag(OP_GPS_ACTION_2_SQUAT_PUNCH1)
        || this->sprite->getActionByTag(OP_GPS_ACTION_2_SQUAT_PUNCH2)
        || this->sprite->getActionByTag(OP_GPS_ACTION_2_SQUAT_KICK1)
        || this->sprite->getActionByTag(OP_GPS_ACTION_2_SQUAT_KICK2)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEBACK)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEFORWARD)
        )
        return true;
    
    return false;
}

bool Fighter::isActionStoppable()
{
    if (
        this->sprite->getNumberOfRunningActions() == 1
        && (this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEBACK)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_DOWN)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEBACK)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEFORWARD))
         )
        return true;
    return false;
}

bool Fighter::checkBoundary(int displacement)
{
    auto ox = opponent->getPosition().x;
    auto px = getPosition().x + displacement;
    auto backgroundbox = this->getSprite()->getParent()->getContentSize();
    auto playerBox = this->getBoundingBox();
    
    if (px + (playerBox.size.width / 2) + CAMERA_FIGHTER_OFFSET > backgroundbox.width)
        return false;
    
    if (px - (playerBox.size.width / 2) - CAMERA_FIGHTER_OFFSET < 0)
        return false;
    
    CCLOG("%f %f %f", ox, px, std::abs(ox - px));
    if (std::abs(ox - px) > 650)
        return false;
    return true;
}




