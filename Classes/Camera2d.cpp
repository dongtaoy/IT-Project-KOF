//
//  Camera.cpp
//  KOF
//
//  Created by Dongtao Yu on 11/09/2015.
//
//

#include "Camera2d.h"

USING_NS_CC;

Camera2d::Camera2d(Fighter* player, Fighter* opponent, Sprite* background)
{
    this->player = player;
    this->opponent = opponent;
    this->background = background;
    
    
}

void Camera2d::update(float dt)
{
    this->playerScreenPos = player->getScreenPosition();
    this->opponentScreenPos = opponent->getScreenPosition();

    Size visibleSize = Director::getInstance()->getWinSize();
    
//    if (playerScreenPos.x < CAMERA_MOVE_THRESHOLD)
//    {
//        moveBackground(CAMERA_MOVE_THRESHOLD - playerScreenPos.x);
//    }
//    
//    if (playerScreenPos.x > (visibleSize.width - CAMERA_MOVE_THRESHOLD))
//    {
//        moveBackground(-CAMERA_MOVE_THRESHOLD + (visibleSize.width - playerScreenPos.x));
//    }

    auto mid = background->convertToNodeSpace(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    auto toPlayer = mid.x - player->getPosition().x;
    auto toOpponent = mid.x - opponent->getPosition().x;
    
    if(std::signbit(toPlayer) != std::signbit(toOpponent))
    {
        auto displacement = (toPlayer + toOpponent) / 2;
        if(toPlayer > toOpponent)
            moveBackground(displacement);
        else if(toPlayer < toOpponent)
            moveBackground(-displacement);
    }
//    else
//    {
//        auto displacement = std::abs(toPlayer + toOpponent) / 2;
//        if(std::signbit(toPlayer))
//        {
//            moveBackground(+displacement);
//        }else
//        {
//            moveBackground(-displacement);
//        }
//    }
    
    CCLOG("%f %f", toPlayer, toOpponent);
    
//    auto startpos = opponentScreenPos.x > playerScreenPos.x ? playerScreenPos.x : opponentScreenPos.x;
//    auto mid = startpos + std::abs(playerScreenPos.x - opponentScreenPos.x) / 2;
//    auto displacement = background->getPosition().x - mid;
//    moveBackground(displacement);
    
//    auto backgroundScreenPos = background->getParent()->convertToWorldSpace(background->getPosition());
//    
//    CCLOG("%f %f", background->getParent()->convertToWorldSpace(background->getPosition()).x, mid);
//    
//    auto newPos = background->getParent()->convertToNodeSpace(Vec2(mid, backgroundScreenPos.y));
//    
//    CCLOG("%f %f", newPos.x, newPos.y);
//    
//    background->setPosition(newPos);
//    
//    if (background->getParent()->convertToWorldSpace(background->getPosition()).x != mid)
//    {
//        
//    }
    
//    if (opponentScreenPos.x < CAMERA_MOVE_THRESHOLD + CAMERA_FIGHTER_OFFSET)
//    {
//        moveBackground(CAMERA_MOVE_THRESHOLD + CAMERA_FIGHTER_OFFSET - playerScreenPos.x);
//    }
//    
//    if (opponentScreenPos.x > (visibleSize.width - CAMERA_MOVE_THRESHOLD - CAMERA_FIGHTER_OFFSET))
//    {
//        moveBackground(-CAMERA_MOVE_THRESHOLD - CAMERA_FIGHTER_OFFSET + (visibleSize.width - playerScreenPos.x));
//    }
    
}

void Camera2d::moveBackground(float displacement)
{
    auto visibleSize = Director::getInstance()->getWinSize();
    auto box = background->getBoundingBox();
    if (box.origin.x + displacement > 0 || box.origin.x + displacement + box.size.width < visibleSize.width)
        return;
    
    Vec2 currentPosition = background->getPosition();
    Vec2 newPosition = Vec2(currentPosition.x + displacement, currentPosition.y);
    background->setPosition(newPosition);
}

