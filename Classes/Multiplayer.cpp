//
//  Multiplayer.cpp
//  KOF
//
//  Created by Dongtao Yu on 26/08/2015.
//
//

#include "Multiplayer.h"

Multiplayer* _instance = NULL;


Multiplayer::Multiplayer(std::string username)
{
    // Add APPWARP ID AND KEY
    AppWarp::Client::initialize(APPWARP_APP_KEY,APPWARP_SECRET_KEY);
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setConnectionRequestListener(this);
    client->setZoneRequestListener(this);
    client->setRoomRequestListener(this);
    CCLOG("Connecting to APPWARP with %s %s", APPWARP_APP_KEY, APPWARP_SECRET_KEY);
    client->connect(username);
}


Multiplayer* Multiplayer::getInstance()
{
    // Multiplayer object not initialized
    assert(_instance);
    
    return _instance;
}


void Multiplayer::initialize(std::string username)
{
    if(_instance != NULL)
        return;
    
    _instance = new Multiplayer(username);
        
}

// ConnectionRequestListener
void Multiplayer::onConnectDone(int result, int code)
{
    switch (result) {
        case AppWarp::ResultCode::success:
            CCLOG("onConnectDone .. SUCCESS..session=%d\n", AppWarp::AppWarpSessionID);
            break;
            
        case AppWarp::ResultCode::success_recovered:
            
            break;
            
        default:
            CCLOG("onConnectDone .. FAILED with reasonCode=%d..session=%d\n", code, AppWarp::AppWarpSessionID);
            break;
    }
}



void Multiplayer::onGetAllRoomsDone(AppWarp::liveresult result)
{
    AppWarp::Client *warpClientRef;
    warpClientRef = AppWarp::Client::getInstance();
    CCLOG("onGetAllRoomsDone : %d", result.result);
    for(std::vector<int>::size_type i = 0; i != result.list.size(); i++){
        std::cout << result.list[i] << std::endl;
        warpClientRef->getLiveRoomInfo(result.list[i]);
    }
}

void Multiplayer::onGetLiveRoomInfoDone(AppWarp::liveroom result)
{
    std::cout << result.rm.name << std::endl;
    //    CCLOG("%s", result.rm.name);
}


