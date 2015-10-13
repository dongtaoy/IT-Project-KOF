//
//  Fighter.cpp
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#include "Fighter.h"

Fighter::Fighter(cocos2d::Sprite* sprite, cocos2d::ui::LoadingBar* health , std::string name, bool isLeft)
{
    this->name = name;
    this->isLeft = isLeft;
    this->sprite = sprite;
    this->health = health;
    this->isDie = false;
    
    this->sprite->setSpriteFrame(fmt::format(CHARACTER_INITIAL_FRAME, name));
    
    auto size = cocos2d::Size(this->sprite->getContentSize().width * this->sprite->getScaleX() - 50,
                     this->sprite->getContentSize().height * this->sprite->getScaleY());
    
    this->physicsSprite = cocos2d::Sprite::create("res/Resources/Empty.png");
    this->physicsSprite->setPosition(this->sprite->getPosition().x,  this->sprite->getPosition().y + 100);
    auto body = cocos2d::PhysicsBody::createBox(size);
    body->setRotationEnable(false);
    body->setGravityEnable(false);
    this->physicsSprite->setPhysicsBody(body);
    
    this->sprite->getParent()->addChild(this->physicsSprite);
    this->start();
    
}


void Fighter::update(float)
{
    this->sprite->setPosition(this->physicsSprite->getPosition().x, this->sprite->getPosition().y);
}


cocos2d::Vec2 Fighter::getPosition()
{
    return this->physicsSprite->getPosition();
}

void Fighter::setPosition(cocos2d::Vec2 pos)
{
    if (isLeft)
    {
        if (pos.x > opponent->getPosition().x)
            return;
    }
    else
    {
        if (pos.x < opponent->getPosition().x)
            return;
    }
    this->physicsSprite->setPosition(pos);
}

cocos2d::Rect Fighter::getBoundingBox()
{
    return this->sprite->getBoundingBox();
}

cocos2d::Vec2 Fighter::getScreenPosition()
{
    return this->sprite->getParent()->convertToWorldSpace(this->getPosition());
}

cocos2d::Node* Fighter::getParent()
{
    return this->sprite->getParent();
}



void Fighter::stand()
{
    if (!isStand() && (this->sprite->getNumberOfRunningActions() < 1 || isActionStoppable()))
    {
        this->physicsSprite->stopAllActions();
        this->sprite->stopAllActions();
        auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_STAND, name));
        auto animate = cocos2d::Animate::create(animation);
        auto repeat = cocos2d::RepeatForever::create(animate);
        repeat->setTag(OP_GPS_ACTION_1_STAND);
        this->sprite->runAction(repeat);
    }
}

void Fighter::stand_hit()
{
    this->sprite->stopAllActions();
    auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_STAND_HIT, name));
    auto animate = cocos2d::Animate::create(animation);
    animate->setDuration(0.8f);
    auto func = [&]{
        this->sprite->stopAllActions();
        this->stand();
    };
    auto sequence = cocos2d::Sequence::create(animate, cocos2d::CallFunc::create(func), NULL);
    sequence->setTag(OP_GPS_ACTION_2_STAND_HIT);
    this->sprite->runAction(sequence);

}

void Fighter::stand_jump(int distance)
{
    
    if(isActionStoppable())
    {
        this->physicsSprite->stopAllActions();
        this->sprite->stopAllActions();
        auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_STAND_JUMP, name));
        auto animate = cocos2d::Animate::create(animation);
        auto jumpBy = cocos2d::JumpBy::create(animate->getDuration(), cocos2d::Vec2(0, 0), 300.0f, 1);
        auto moveBy = cocos2d::MoveBy::create(animate->getDuration(), cocos2d::Vec2(distance, 0));
        auto spawn = cocos2d::Spawn::create(animate, jumpBy, NULL);
        auto callFunc = cocos2d::CallFunc::create([&]{this->sprite->stopAllActions();this->stand();});
        auto sequence = cocos2d::Sequence::create(spawn, callFunc, NULL);
        sequence->setTag(OP_GPS_ACTION_2_STAND_JUMP);
        this->sprite->runAction(sequence);
        this->physicsSprite->runAction(moveBy);
    }
}



void Fighter::stand_moveback()
{
    
    if(!(this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEBACK)) && isActionStoppable())
    {
        this->physicsSprite->stopAllActions();
        this->sprite->stopAllActions();
        auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_STAND_MOVEBACK, name));
        auto animate = cocos2d::Animate::create(animation);
        //        animate->setDuration(ACTION_1_MOVE_DURATION);
        auto animateForever = cocos2d::RepeatForever::create(animate);
        animateForever->setTag(OP_GPS_ACTION_1_STAND_MOVEBACK);
        auto moveby = cocos2d::MoveBy::create(animate->getDuration(), cocos2d::Vec2(-ACTION_MOVE_SPEED, 0));
        auto movebyForever = cocos2d::RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->physicsSprite->runAction(movebyForever);
    }
}

void Fighter::stand_moveforward()
{
    
    if(!(this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD)) && isActionStoppable())
    {
        this->physicsSprite->stopAllActions();
        this->sprite->stopAllActions();
        auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_STAND_MOVEFORWARD, name));
        auto animate = cocos2d::Animate::create(animation);
        auto animateForever = cocos2d::RepeatForever::create(animate);
        animateForever->setTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD);
        auto moveby = cocos2d::MoveBy::create(animate->getDuration(), cocos2d::Vec2(ACTION_MOVE_SPEED, 0));
        auto movebyForever = cocos2d::RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->physicsSprite->runAction(movebyForever);
    }
}




void Fighter::squat()
{
    if (!(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT)))
    {
        this->sprite->stopAllActions();
        auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_SQUAT, name));
        auto animate = cocos2d::Animate::create(animation);
        auto repeat = cocos2d::RepeatForever::create(animate);
        repeat->setTag(OP_GPS_ACTION_1_SQUAT);
        this->sprite->runAction(repeat);
        
    }
}

void Fighter::squat_down()
{
    if (!(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_DOWN)) && !(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT)) && isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_SQUAT_DOWN, name));
        auto animate = cocos2d::Animate::create(animation);
        auto func = cocos2d::CallFunc::create([&]{this->sprite->stopAllActions();this->squat();});
        auto sequence = cocos2d::Sequence::create(animate, func, NULL);
        sequence->setTag(OP_GPS_ACTION_1_SQUAT_DOWN);
        this->sprite->runAction(sequence);
    }
}

void Fighter::squat_hit()
{
    this->sprite->stopAllActions();
    auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_SQUAT_HIT, name));
    auto animate = cocos2d::Animate::create(animation);
    animate->setDuration(0.5f);
    auto func = [&]{
        this->sprite->stopAllActions();
        this->squat();
    };
    auto sequence = cocos2d::Sequence::create(animate, cocos2d::CallFunc::create(func), NULL);
    sequence->setTag(OP_GPS_ACTION_2_SQUAT_HIT);
    this->sprite->runAction(sequence);
}


void Fighter::squat_moveback()
{
    if(!(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEBACK)) && isActionStoppable())
    {
        this->physicsSprite->stopAllActions();
        this->sprite->stopAllActions();
        auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_SQUAT_MOVEBACK, name));
        auto animate = cocos2d::Animate::create(animation);
        auto animateForever = cocos2d::RepeatForever::create(animate);
        animateForever->setTag(OP_GPS_ACTION_1_SQUAT_MOVEBACK);
        auto moveby = cocos2d::MoveBy::create(animate->getDuration(), cocos2d::Vec2(-ACTION_MOVE_SPEED, 0));
        auto movebyForever = cocos2d::RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->physicsSprite->runAction(movebyForever);
    }
}

void Fighter::squat_moveforward()
{
    if(!(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEFORWARD)) && isActionStoppable())
    {
        this->physicsSprite->stopAllActions();
        this->sprite->stopAllActions();
        auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_SQUAT_MOVEFORWARD, name));
        auto animate = cocos2d::Animate::create(animation);
        auto animateForever = cocos2d::RepeatForever::create(animate);
        animateForever->setTag(OP_GPS_ACTION_1_SQUAT_MOVEFORWARD);
        auto moveby = cocos2d::MoveBy::create(animate->getDuration(), cocos2d::Vec2(ACTION_MOVE_SPEED, 0));
        auto movebyForever = cocos2d::RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->physicsSprite->runAction(movebyForever);
    }
}

void Fighter::squat_up()
{
    
}

void Fighter::start()
{
    this->sprite->stopAllActions();
    auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_START, name));
    auto animate = cocos2d::Animate::create(animation);
    auto sequence = cocos2d::Sequence::create(animate, cocos2d::CallFunc::create([&]{ this->sprite->stopAllActions(); this->stand();}), NULL);
    this->sprite->runAction(sequence);
    
}

void Fighter::win()
{
    this->sprite->stopAllActions();
    auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_WIN, name));
    auto animate = cocos2d::Animate::create(animation);
    auto animateForever = cocos2d::RepeatForever::create(animate);
    animateForever->setTag(OP_GPS_ACTION_3_WIN);
    this->sprite->runAction(animateForever);
}

void Fighter::die()
{
    this->sprite->stopAllActions();
    auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_DIE, name));
    auto func = [&]
    {
        isDie = true;
    };
    auto animate = cocos2d::Animate::create(animation);
    auto sequence = cocos2d::Sequence::create(animate, cocos2d::CallFunc::create(func), NULL);
    this->sprite->runAction(sequence);
}

void Fighter::kick1()
{
    if(isActionStoppable())
    {
        cocos2d::Animation* animation = NULL;
        if (!isSquat())
            animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_STAND_KICK1, name));
        else
            animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_SQUAT_KICK1, name));
        auto animate = cocos2d::Animate::create(animation);
        
        auto preFunc = [&]
        {
            if (this->isHit())
            {
                auto h = opponent->gethealth();
                opponent->setHealthPercentage(h->getPercent() - KICK1_DAMAGE);
                if (opponent->isStand()) {
                    opponent->stand_hit();
                }
                if (opponent->isSquat()) {
                    opponent->squat_hit();
                }
            }
        };
        
        auto func = [&]{
            if (!this->isSquat()) {
                this->sprite->stopAllActions();
                this->stand();
                return;
            }
            this->squat();
            
        };
        
        
        auto sequence = cocos2d::Sequence::create(cocos2d::CallFunc::create(preFunc), animate, cocos2d::CallFunc::create(func), NULL);
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
        cocos2d::Animation* animation = NULL;
        if (!isSquat())
            animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_STAND_KICK2, name));
        else
            animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_SQUAT_KICK2, name));
        auto animate = cocos2d::Animate::create(animation);
        
        auto preFunc = [&]
        {
            if (this->isHit())
            {
                auto h = opponent->gethealth();
                opponent->setHealthPercentage(h->getPercent() - KICK1_DAMAGE);
                if (opponent->isStand()) {
                    opponent->stand_hit();
                }
                if (opponent->isSquat()) {
                    opponent->squat_hit();
                }
            }
        };
        
        auto func = [&]{
            if (!this->isSquat()) {
                this->sprite->stopAllActions();
                this->stand();
                return;
            }
            this->squat();
            
        };
        
        
        auto sequence = cocos2d::Sequence::create(cocos2d::CallFunc::create(preFunc), animate, cocos2d::CallFunc::create(func), NULL);

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
        cocos2d::Animation* animation = NULL;
        if (!isSquat())
            animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_STAND_PUNCH1, name));
        else
            animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_SQUAT_PUNCH1, name));
        auto animate = cocos2d::Animate::create(animation);
        
        auto preFunc = [&]
        {
            if (this->isHit())
            {
                auto h = opponent->gethealth();
                opponent->setHealthPercentage(h->getPercent() - KICK1_DAMAGE);
                if (opponent->isStand()) {
                    opponent->stand_hit();
                }
                if (opponent->isSquat()) {
                    opponent->squat_hit();
                }
            }
        };
        
        auto func = [&]{
            if (!this->isSquat()) {
                this->sprite->stopAllActions();
                this->stand();
                return;
            }
            this->squat();
            
        };
        
        
        auto sequence = cocos2d::Sequence::create(cocos2d::CallFunc::create(preFunc), animate, cocos2d::CallFunc::create(func), NULL);
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
        cocos2d::Animation* animation = NULL;
        if (!isSquat())
            animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_STAND_PUNCH2, name));
        else
            animation = cocos2d::AnimationCache::getInstance()->getAnimation(fmt::format(CHARACTER_SQUAT_PUNCH2, name));
        auto animate = cocos2d::Animate::create(animation);
        
        auto preFunc = [&]
        {
            if (this->isHit())
            {
                auto h = opponent->gethealth();
                opponent->setHealthPercentage(h->getPercent() - KICK1_DAMAGE);
                if (opponent->isStand()) {
                    opponent->stand_hit();
                }
                if (opponent->isSquat()) {
                    opponent->squat_hit();
                }
            }
        };
        
        auto func = [&]{
            if (!this->isSquat()) {
                this->sprite->stopAllActions();
                this->stand();
                return;
            }
            this->squat();
            
        };
        
        
        auto sequence = cocos2d::Sequence::create(cocos2d::CallFunc::create(preFunc), animate, cocos2d::CallFunc::create(func), NULL);
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
    if (   this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEBACK)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_DOWN)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEBACK)
        || this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEFORWARD)
        )
        return true;
    return false;
}


bool Fighter::isHit()
{
    CCLOG("here");
    auto px = getPosition().x;
    auto ox = opponent->getPosition().x;
    auto pw = getSprite()->getBoundingBox().size.width / 2;// * getSprite()->getScaleX() / 2;
    auto ow = opponent->getSprite()->getBoundingBox().size.width / 2;// * opponent->getSprite()->getScaleX() / 2;
    if (isLeft) {
        if ((px + pw) > (ox - ow))
        {
            return true;
        }
        return false;
    }
    else
    {
        if ((px - pw) < (ox + ow))
        {
            return true;
        }
        return false;
    }
}


void Fighter::setHealthPercentage(float p)
{
    if (p <= 0) {
        this->die();
        opponent->win();
    }
    isHealthChanged = true;
    this->health->setPercent(p);
}

float Fighter::getHealthPercentage()
{
    return this->gethealth()->getPercent();
}


