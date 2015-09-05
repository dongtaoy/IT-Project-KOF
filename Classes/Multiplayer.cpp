//
//  Multiplayer.cpp
//  KOF
//
//  Created by Dongtao Yu on 26/08/2015.
//
//

#include "Multiplayer.h"

Multiplayer* Multiplayer::_instance = NULL;


Multiplayer::Multiplayer(std::string username)
{
    
    this->username = username;
    
    // Add APPWARP ID AND KEY
    AppWarp::Client::initialize(APPWARP_APP_KEY,APPWARP_SECRET_KEY);
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setRecoveryAllowance(60);
    CCLOG("%d", client->getState());
}


Multiplayer* Multiplayer::getInstance()
{
    // Multiplayer object not initialized
//    assert(_instance);
    
    return _instance;
}


void Multiplayer::initialize(std::string username)
{
    if(_instance != NULL)
        return;
    
    _instance = new Multiplayer(username);
        
}

void Multiplayer::connect(AppWarp::ConnectionRequestListener* listener)
{
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setConnectionRequestListener(listener);
    CCLOG("Connecting to APPWARP with %s %s %s", APPWARP_APP_KEY, APPWARP_SECRET_KEY, username.c_str());
    client->connect(username);
}

void Multiplayer::fetchRooms(AppWarp::RoomRequestListener* listener)
{
    
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setZoneRequestListener(this);
    client->setRoomRequestListener(listener);
    client->getAllRooms();
}

void Multiplayer::createRoom(AppWarp::ZoneRequestListener* listener, std::map<std::string, std::string> properties)
{
    
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setZoneRequestListener(listener);
    client->createRoom(ROOM_NAME, username, MAX_USERS, properties);
}

void Multiplayer::joinRoom(AppWarp::RoomRequestListener* listener)
{
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setRoomRequestListener(listener);
    client->joinRoom(roomID);
}

void Multiplayer::leaveRoom(AppWarp::RoomRequestListener* listener)
{
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setRoomRequestListener(listener);
    client->leaveRoom(roomID);
    roomID = "";
}


void Multiplayer::subscribeRoom(AppWarp::RoomRequestListener* roomRequestListener, AppWarp::NotificationListener* notificationListener)
{
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setRoomRequestListener(roomRequestListener);
    client->setNotificationListener(notificationListener);
    client->subscribeRoom(roomID);
}

void Multiplayer::sendChat(std::string message)
{
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->sendChat(message);
}

/**
 * The state of the Client. Values are -
 * ConnectionState::disconnected = 2,
 * ConnectionState::connecting = 1,
 * ConnectionState::connected = 0,
 */

bool Multiplayer::isConnected()
{
    AppWarp::Client* client = AppWarp::Client::getInstance();
    int state = client->getState();
    CCLOG("%d", state);
    if(state == 0)
        return true;
    return false;
}

void Multiplayer::recoverConnection()
{
    
    AppWarp::Client::getInstance()->recoverConnection();
}

void Multiplayer::resetZoneRequestListener()
{
//    initZoneRequestListener()
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setZoneRequestListener(this);
}

/*
 Lisenter
 */

// ConnectionRequestListener
void Multiplayer::onConnectDone(int result, int)
{
    CCLOG("hereh");
    switch (result) {
        case AppWarp::ResultCode::success:
            CCLOG("onConnectDone .. SUCCESS..session=%d\n", AppWarp::AppWarpSessionID);
            break;
            
        case AppWarp::ResultCode::success_recovered:
            CCLOG("onConnectDone .. success_recovered..session=%d\n", AppWarp::AppWarpSessionID);
            break;
            
        default:
            CCLOG("onConnectDone .. FAILED with reasonCode=%d..session=%d\n", result, AppWarp::AppWarpSessionID);
            break;
    }
}

void Multiplayer::setRoomID(std::string roomID)
{
    this->roomID = roomID;
}


std::string Multiplayer::getRoomID()
{
    return this->roomID;
}

void Multiplayer::onGetAllRoomsDone(AppWarp::liveresult result)
{
    
    AppWarp::Client *warpClientRef;
    warpClientRef = AppWarp::Client::getInstance();
    CCLOG("onGetAllRoomsDone : %d", result.result);
    for(std::vector<int>::size_type i = 0; i != result.list.size(); i++){
        warpClientRef->getLiveRoomInfo(result.list[i]);
    }
    
}


void Multiplayer::getLiveRoomInfo(AppWarp::RoomRequestListener* listener)
{
    AppWarp::Client *client = AppWarp::Client::getInstance();
    client->setRoomRequestListener(listener);
    client->getLiveRoomInfo(roomID);
}

//void Multiplayer::onCreateRoomDone(AppWarp::room event)
//{
//    std::cout << event.roomId << std::endl;
//}

//
//void Multiplayer::onGetLiveRoomInfoDone(AppWarp::liveroom result)
//{
//    std::cout << result.rm.name << std::endl;
//    //    CCLOG("%s", result.rm.name);
//}


