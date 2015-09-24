//
//  Multiplayer.h
//  KOF
//
//  Created by Dongtao Yu on 26/08/2015.
//
//

#ifndef __KOF__Multiplayer__
#define __KOF__Multiplayer__

#include <stdio.h>
#include "appwarp.h"
#include "cocos2d.h"
#include "Definitions.h"
#include "ChooseRoomScene.h"
#include "GameHelper.h"
#include <boost/algorithm/string.hpp>
#include <boost/lockfree/stack.hpp>

#define MAX_USERS 2

class Multiplayer : public AppWarp::ConnectionRequestListener, public AppWarp::ZoneRequestListener, public AppWarp::RoomRequestListener, public AppWarp::NotificationListener
{
    
public:
    
    static Multiplayer* getInstance();
    
    static void initialize(std::string);
    
    static std::string buildMessage(int, int, std::string = "");
    static std::vector<std::vector<std::string>> exractMessage(std::string);
    static bool isMesaageValid(std::string, std::string);
    
    void connect(AppWarp::ConnectionRequestListener*);
    
    void fetchRooms(AppWarp::RoomRequestListener*);
    
    void createRoom(AppWarp::ZoneRequestListener*, std::map<std::string, std::string>);
    
    void joinRoom(AppWarp::RoomRequestListener*);
    
    void leaveRoom(AppWarp::RoomRequestListener*);
    
    void subscribeRoom(AppWarp::RoomRequestListener*);
    
    void unsubsribeRoom(AppWarp::RoomRequestListener*);
    
    void getLiveRoomInfo(AppWarp::RoomRequestListener*);
    
    void sendChat(std::string, bool = true);
    
    void sendChatAfter(int, std::string);
    
    void sendPrivateUdpUpdate(AppWarp::byte* update,int updateLen);
    
    void resetConnectionRequestListener();
    
    void resetAllListener();
//    void setNotificationListener(AppWarp:: No)
    
    bool isConnected();
    
    void recoverConnection();
    
    void resetZoneRequestListener();
    
    void setNotificationListener(AppWarp::NotificationListener*);
    
    
    CC_SYNTHESIZE(std::string, username, Username);
    CC_SYNTHESIZE(std::string, userCharacter, UserCharacter);
    CC_SYNTHESIZE(std::string, opponentUsername, OpponentUsername);
    CC_SYNTHESIZE(std::string, opponentCharacter, OpponentCharacter);
    CC_SYNTHESIZE(std::string, roomID, RoomID);
    CC_SYNTHESIZE(std::string, background, Background);
    CC_SYNTHESIZE(int, bestof, Bestof);
    
    std::queue<std::tuple<std::string, std::vector<std::vector<std::string>>>> chats;
    bool isChatsEmpty();
    std::tuple<std::string, std::vector<std::vector<std::string>>> getChatsFront();
    
private:
    
    static Multiplayer* _instance;
    
    
    // Private constructor
    Multiplayer(std::string username);
    
    
    
    // ConnectionRequestListener
    void onConnectDone(int,int);
    
    // ZoneRequestListener
    void onGetAllRoomsDone(AppWarp::liveresult);
    
    
    void onUserJoinedRoom(AppWarp::room, std::string);
    void onUserLeftRoom(AppWarp::room, std::string);
    void onChatReceived(AppWarp::chat);
//    void onCreateRoomDone(AppWarp::room);
    
    // RoomRequestListner
//    void onGetLiveRoomInfoDone(AppWarp::liveroom);
    
    
    
};

#endif /* defined(__KOF__Multiplayer__) */
