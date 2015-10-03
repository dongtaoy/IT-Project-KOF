//
//  Fighter.cpp
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#include "Fighter.h"

USING_NS_CC;
using namespace ui;

Fighter::Fighter(Sprite* sprite, LoadingBar* health , std::string name, bool isLeft)
{
    this->name = name;
    this->isLeft = isLeft;
    this->sprite = sprite;
    this->health = health;
    this->sprite->setSpriteFrame((boost::format(CHARACTER_INITIAL_FRAME) % name).str());
    auto size = Size(this->sprite->getContentSize().width * this->sprite->getScaleX(),
                     this->sprite->getContentSize().height * this->sprite->getScaleY());
    size = this->sprite->getBoundingBox().size;
    auto body = PhysicsBody::createBox(size, PhysicsMaterial(1.0f,0.0f,1.0f));
    body->setRotationEnable(false);
    body->setGravityEnable(true);
//    body->applyForce(Vec2(0.0f, -99999.0f));
    this->sprite->setPhysicsBody(body);
//    auto node = Node::create();
//    node-
//    node->setPhysicsBody(body);
//    this->sprite->addChild(node);
//    auto body = PhysicsBody::createBox(Size(x - Character_Edge_Offset, y), PhysicsMaterial(Physic_Box_Density, Physic_Box_Restitution, Physic_Box_Friction));
//    sprite->setPhysicsBody(body);
//    
//        //set colission detect
//    body->setCollisionBitmask(bitmask);
//    body->setContactTestBitmask(true);
//    
//        //keep character still
//    body->setRotationEnable(false);
//    body->setGravityEnable(true);
    
    
    this->start();
    
}


void Fighter::update(float)
{
    auto visibleSize = Director::getInstance()->getWinSize();
    auto playerBox = this->getBoundingBox();
    auto opponentBox = opponent->getBoundingBox();
    auto backgroundbox = this->getSprite()->getParent()->getContentSize();
    
    // background size
    if (this->getPosition().x - (playerBox.size.width / 2) - CAMERA_FIGHTER_OFFSET < 0)
    {
        this->setPosition(Vec2((playerBox.size.width / 2) + CAMERA_FIGHTER_OFFSET , this->getPosition().y));
    }
    
    if (this->getPosition().x + (playerBox.size.width / 2) + CAMERA_FIGHTER_OFFSET > backgroundbox.width)
    {
        this->setPosition(Vec2(backgroundbox.width - (playerBox.size.width / 2) - CAMERA_FIGHTER_OFFSET, this->getPosition().y));
    }
    
    
    // screen size
    if (this->getScreenPosition().x - SCREEN_FIGHTER_OFFSET < 0)
    {
        this->setPosition(Vec2(this->sprite->getParent()->convertToNodeSpace(Vec2(SCREEN_FIGHTER_OFFSET, 0)).x,getPosition().y));
    }
    
    if (this->getScreenPosition().x + SCREEN_FIGHTER_OFFSET > visibleSize.width)
    {
        this->setPosition(Vec2(this->sprite->getParent()->convertToNodeSpace(Vec2(visibleSize.width - SCREEN_FIGHTER_OFFSET, 0)).x,getPosition().y));
    }
    
    
//    if (isle)
    
//    if (isLeft)
//    {
//        if (getPosition().x + SCREEN_FIGHTER_OFFSET > opponent->getPosition().x) {
//            this->setPosition(Vec2(opponent->getPosition().x - SCREEN_FIGHTER_OFFSET, getPosition().y));
//        }
//    }
//    else
//    {
//        if (getPosition().x - SCREEN_FIGHTER_OFFSET < opponent->getPosition().x) {
//            this->setPosition(Vec2(opponent->getPosition().x + SCREEN_FIGHTER_OFFSET, getPosition().y));
//        }
//    }
    
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
    
    if(isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_JUMP)%name).str());
        auto animate = Animate::create(animation);
        auto jumpTo = JumpTo::create(animate->getDuration(), Vec2(getPosition().x + distance, getPosition().y), 300.0f, 1);
        auto spawn = Spawn::create(animate, jumpTo, NULL);
        auto callFunc = CallFunc::create([&]{this->sprite->stopAllActions();this->stand();});
        auto sequence = Sequence::create(spawn, callFunc, NULL);
        sequence->setTag(OP_GPS_ACTION_2_STAND_JUMP);
        this->sprite->runAction(sequence);
    }
}



void Fighter::stand_moveback()
{
    
    if(!(this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEBACK)) && isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_MOVEBACK)%name).str());
        auto animate = Animate::create(animation);
        //        animate->setDuration(ACTION_1_MOVE_DURATION);
        auto animateForever = RepeatForever::create(animate);
        animateForever->setTag(OP_GPS_ACTION_1_STAND_MOVEBACK);
        auto moveby = MoveBy::create(animate->getDuration(), Vec2(-ACTION_MOVE_SPEED, 0));
        auto movebyForever = RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->sprite->runAction(movebyForever);
    }
}

void Fighter::stand_moveforward()
{
    
    if(!(this->sprite->getActionByTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD)) && isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_STAND_MOVEFORWARD)%name).str());
        auto animate = Animate::create(animation);
        auto animateForever = RepeatForever::create(animate);
        animateForever->setTag(OP_GPS_ACTION_1_STAND_MOVEFORWARD);
        auto moveby = MoveBy::create(animate->getDuration(), Vec2(ACTION_MOVE_SPEED, 0));
        auto movebyForever = RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->sprite->runAction(movebyForever);
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
    if(!(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEBACK)) && isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT_MOVEBACK)%name).str());
        auto animate = Animate::create(animation);
        auto animateForever = RepeatForever::create(animate);
        animateForever->setTag(OP_GPS_ACTION_1_SQUAT_MOVEBACK);
        auto moveby = MoveBy::create(animate->getDuration(), Vec2(-ACTION_MOVE_SPEED, 0));
        auto movebyForever = RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->sprite->runAction(movebyForever);
    }
}

void Fighter::squat_moveforward()
{
    if(!(this->sprite->getActionByTag(OP_GPS_ACTION_1_SQUAT_MOVEFORWARD)) && isActionStoppable())
    {
        this->sprite->stopAllActions();
        auto animation = AnimationCache::getInstance()->getAnimation((boost::format(CHARACTER_SQUAT_MOVEFORWARD)%name).str());
        auto animate = Animate::create(animation);
        auto animateForever = RepeatForever::create(animate);
        animateForever->setTag(OP_GPS_ACTION_1_SQUAT_MOVEFORWARD);
        auto moveby = MoveBy::create(animate->getDuration(), Vec2(ACTION_MOVE_SPEED, 0));
        auto movebyForever = RepeatForever::create(moveby);
        this->sprite->runAction(animateForever);
        this->sprite->runAction(movebyForever);
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
            
            if (this->isHit())
            {
                auto h = opponent->gethealth();
                h->setPercent(h->getPercent() - KICK1_DAMAGE);
            }
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
            
            if (this->isHit())
            {
                auto h = opponent->gethealth();
                h->setPercent(h->getPercent() - KICK2_DAMAGE);
            }
            
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
            if (this->isHit())
            {
                auto h = opponent->gethealth();
                h->setPercent(h->getPercent() - PUNCH1_DAMAGE);
            }
            
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
            
            if (this->isHit())
            {
                auto h = opponent->gethealth();
                h->setPercent(h->getPercent() - PUNCH2_DAMAGE);
//                opponent->
            }
            
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

