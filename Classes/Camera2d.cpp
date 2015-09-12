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
    
    Size visibleSize = Director::getInstance()->getWinSize();
    
    CCLOG("%f %f", background->getContentSize().width, background->getContentSize().height);
    CCLOG("%f %f", background->getScaleX(), background->getScaleY());
    
    CCLOG("%f %f", background->getPosition().x, background->getPosition().y);
    CCLOG("%f %f", visibleSize.width, visibleSize.height);
    
}

void Camera2d::update()
{
//    auto playerPosition = player->getSprite()->getPosition();
//    auto opponentPosition = opponent->getSprite()->getPosition();
//    auto playerSize = player->getSprite()->getContentSize();
//    auto opponentSize = player->getSprite()->getContentSize();
    
//    auto playerPosition = player->getSprite()->getPosition();
//    
//    if (playerPosition.x < 200) {
//        background->setPosition(Vec2(background->getPosition().x + 200 - playerPosition.x, background->getPosition().y));
//    }

    this->playerScreenPos = toScreenCoord(background, player);
    this->opponentScreenPos = toScreenCoord(background, opponent);
    CCLOG("background    : %f %f", background->getContentSize().width , background->getContentSize().height);
    CCLOG("background pos: %f %f", background->getPosition().x, background->getPosition().y);
    CCLOG("player in back: %f %f", player->getPosition().x, player->getPosition().y);
    CCLOG("%f %f", playerScreenPos.x , playerScreenPos.y);
}

Vec2 Camera2d::toScreenCoord(Sprite* background, Fighter* fighter)
{
    return Vec2(fighter->getPosition().x - ((background->getContentSize().width) / 2 - background->getPosition().x ),
                fighter->getPosition().y - ((background->getContentSize().height) / 2 - background->getPosition().y));
}

//void Camera2d::moveBackground()
//{
//    
//}

bool Camera2d::checkBoundary(float x){
    
//    auto playerPosition = player->getSprite()->getPosition();
//    auto opponentPosition = opponent->getSprite()->getPosition();
//    auto playerSize = player->getSprite()->getContentSize();
//    auto opponentSize = player->getSprite()->getContentSize();
//    
//    if ((playerPosition.x + x) < leftBoundary || (playerPosition.x + x)> rightBoundary)
//    {
//        return false;
//        
//    }
//    return true;
}

