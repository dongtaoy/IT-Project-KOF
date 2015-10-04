//
//  GameCenterDelegate.cpp
//  KOF
//
//  Created by Dongtao Yu on 4/10/2015.
//
//

#include "GameCenterDelegate.h"


GameCenterDelegate* GameCenterDelegate::_instance = NULL;

GameCenterDelegate::GameCenterDelegate()
{
    
}


GameCenterDelegate* GameCenterDelegate::getInstance()
{
    return _instance;
}


void GameCenterDelegate::initialize()
{
    if(_instance != NULL)
        return;
    
    _instance = new GameCenterDelegate();
    
}


void GameCenterDelegate::onLocalPlayerAuthenticationChanged()
{
    CCLOG("player changed");
}

void GameCenterDelegate::onPlayerInfoReceived(std::vector<GKPlayerCpp> playerInfo)
{
    CCLOG("PlayerInfoReceived");
    for (int i = 0 ; i < playerInfo.size() ; i ++)
    {
        CCLOG("FRIENDS %d : %s", i, playerInfo.at(i).displayName.c_str());
    }
}


void GameCenterDelegate::onFriendsListRecieved(std::vector<std::string> friends)
{
    CCLOG("FriendsListRecieved");
    for (int i = 0 ; i < friends.size() ; i ++)
    {
        CCLOG("FRIENDS %d : %s", i, friends.at(i).c_str());
    }
}

