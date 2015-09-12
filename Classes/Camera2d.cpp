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
    
    if (playerScreenPos.x < CAMERA_MOVE_THRESHOLD + CAMERA_FIGHTER_OFFSET)
    {
        moveBackground(CAMERA_MOVE_THRESHOLD + CAMERA_FIGHTER_OFFSET - playerScreenPos.x);
    }
    
    if (playerScreenPos.x > (visibleSize.width - CAMERA_MOVE_THRESHOLD - CAMERA_FIGHTER_OFFSET))
    {
        moveBackground(-CAMERA_MOVE_THRESHOLD - CAMERA_FIGHTER_OFFSET + (visibleSize.width - playerScreenPos.x));
    }
    
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

