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

#define MAX_USERS 2

class Multiplayer : public AppWarp::ConnectionRequestListener, public AppWarp::ZoneRequestListener//, public AppWarp::RoomRequestListener
{
    
public:
    
    static Multiplayer* getInstance();
    
    static void initialize(std::string);
    
    static std::string buildMessage(int, int, std::string);
    static std::vector<std::string> exractMessage(std::string);
    
    void connect(AppWarp::ConnectionRequestListener*);
    
    void fetchRooms(AppWarp::RoomRequestListener*);
    
    void createRoom(AppWarp::ZoneRequestListener*, std::map<std::string, std::string>);
    
    void joinRoom(AppWarp::RoomRequestListener*);
    
    void leaveRoom(AppWarp::RoomRequestListener*);
    
    void subscribeRoom(AppWarp::RoomRequestListener*);
    
    void unsubsribeRoom(AppWarp::RoomRequestListener*);
    
    void getLiveRoomInfo(AppWarp::RoomRequestListener*);
    
    void sendChat(std::string);

    
    bool isConnected();
    
    void recoverConnection();
    
    void resetZoneRequestListener();
    
    void setNotificationListener(AppWarp::NotificationListener*);
    
    void setRoomID(std::string);
    
    std::string getRoomID();
    
    std::string getUsername();
    
    
    
private:
    
    
    std::string username;
    std::string roomID;
    
    static Multiplayer* _instance;
    
    
    // Private constructor
    Multiplayer(std::string username);
    
    
    
    // ConnectionRequestListener
    void onConnectDone(int,int);
    
    // ZoneRequestListener
    void onGetAllRoomsDone(AppWarp::liveresult);
    
//    void onCreateRoomDone(AppWarp::room);
    
    // RoomRequestListner
//    void onGetLiveRoomInfoDone(AppWarp::liveroom);
    
    
    
};

#endif /* defined(__KOF__Multiplayer__) */
