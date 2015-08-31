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

class Multiplayer : public AppWarp::ConnectionRequestListener, public AppWarp::ZoneRequestListener, public AppWarp::RoomRequestListener
{
    
public:
    
    static Multiplayer* getInstance();
    
    static void initialize(std::string username);
    
    void fetchRooms();
    
    bool isConnected();
    
    void recoverConnection();
    
private:
    static Multiplayer* _instance;
    
    bool connected;
    
    // Private constructor
    Multiplayer(std::string username);
    
    
    
    // ConnectionRequestListener
    void onConnectDone(int, int);
    
    // ZoneRequestListener
    void onGetAllRoomsDone(AppWarp::liveresult);
    
    // RoomRequestListner
    void onGetLiveRoomInfoDone(AppWarp::liveroom);
    
    
};

#endif /* defined(__KOF__Multiplayer__) */
