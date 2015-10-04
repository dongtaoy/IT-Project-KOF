//
//  Multiplayer.cpp
//  KOF
//
//  Created by Dongtao Yu on 26/08/2015.
//
//

#include "Multiplayer.h"

Multiplayer* Multiplayer::_instance = NULL;

#pragma mark Constructors

Multiplayer::Multiplayer(std::string username)
{
    
    this->username = username;
    
    // Add APPWARP ID AND KEY
    AppWarp::Client::initialize(APPWARP_APP_KEY,APPWARP_SECRET_KEY);
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setRecoveryAllowance(60);
    client->setConnectionRequestListener(this);
    client->setZoneRequestListener(this);
    client->setNotificationListener(this);
    client->setRoomRequestListener(this);
    client->setChatRequestListener(this);
    client->setLobbyRequestListener(this);
    
    isSuccessSent = true;
}


Multiplayer* Multiplayer::getInstance()
{
    return _instance;
}


void Multiplayer::initialize(std::string username)
{
    if(_instance != NULL)
        return;
    
    _instance = new Multiplayer(username);
        
}

#pragma mark Actions

void Multiplayer::connect(MultiplayerCallback* cb)
{
    Multiplayer* m = Multiplayer::getInstance();
    m->callback = cb;
    AppWarp::Client* client = AppWarp::Client::getInstance();
    CCLOG("Connecting to APPWARP with %s %s %s", APPWARP_APP_KEY, APPWARP_SECRET_KEY, m->username.c_str());
    client->connect(m->username);
}


void Multiplayer::fetchRooms(MultiplayerCallback* cb)
{
    CCLOG("Sending Request to fetch rooms");
    Multiplayer::getInstance()->callback = cb;
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->getAllRooms();
}


void Multiplayer::createRoom(MultiplayerCallback* cb, std::map<std::string, std::string> properties)
{
    Multiplayer::getInstance()->callback = cb;
    AppWarp::Client* client = AppWarp::Client::getInstance();
    CCLOG("Sending Request to create room");
    client->createRoom(ROOM_NAME, Multiplayer::getInstance()->username, MAX_USERS, properties);
}

void Multiplayer::onRoomCreated(AppWarp::room event){
    if (event.result == AppWarp::ResultCode::success){
        AppWarp::Client::getInstance()->getLiveRoomInfo(event.roomId);
    }
}

void Multiplayer::onRoomDestroyed(AppWarp::room event){
        CCLOG("work %s", event.roomId.c_str());
        callback->onRoomDestroyed(event.roomId);
}


void Multiplayer::joinLobby(MultiplayerCallback* cb)
{
    Multiplayer* m = Multiplayer::getInstance();
    m->callback = cb;
    AppWarp::Client* client = AppWarp::Client::getInstance();
    CCLOG("Sending Request to join lobby");
    client->joinLobby();
}


void Multiplayer::leaveLobby(MultiplayerCallback* cb)
{
    Multiplayer* m = Multiplayer::getInstance();
    m->callback = cb;
    AppWarp::Client* client = AppWarp::Client::getInstance();
    CCLOG("Sending Request to leave subscribe");
    client->leaveLobby();
}



void Multiplayer::subscribeLobby(MultiplayerCallback* cb)
{
    Multiplayer* m = Multiplayer::getInstance();
    m->callback = cb;
    AppWarp::Client* client = AppWarp::Client::getInstance();
    CCLOG("Sending Request to join subscribe");
    client->subscribeLobby();
}

void Multiplayer::unsubsribeLobby(MultiplayerCallback* cb)
{
    Multiplayer* m = Multiplayer::getInstance();
    m->callback = cb;
    AppWarp::Client* client = AppWarp::Client::getInstance();
    CCLOG("Sending Request to join subscribe");
    client->unsubscribeLobby();
}

void Multiplayer::joinRoom(MultiplayerCallback* cb)
{
    Multiplayer* m = Multiplayer::getInstance();
    m->callback = cb;
    AppWarp::Client* client = AppWarp::Client::getInstance();
    CCLOG("Sending Request to join room %s", m->roomID.c_str());
    client->joinRoom(m->roomID);
}


void Multiplayer::unsubsribeRoom(MultiplayerCallback* cb)
{
    Multiplayer* m = Multiplayer::getInstance();
    m->opponentUsername = "";
    m->background = "";
    m->bestof = 0;
    m->userCharacter = "";
    m->opponentCharacter = "";
    m->callback = cb;
    CCLOG("Sending Request to unsubsribe room %s", m->roomID.c_str());
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->unsubscribeRoom(m->roomID);
}

void Multiplayer::sendChat(int scene, int op, std::string properties)
{
    
    AppWarp::Client::getInstance()->sendChat(
                                            std::to_string(scene) + ';'
                                            + std::to_string(op) + ';'
                                            + properties + ';');
        
}

void Multiplayer::sendChat(std::string message)
{
    
    Multiplayer* m = Multiplayer::getInstance();
    if (!message.compare(m->prevMessage))
        return;
    CCLOG("sending %s", message.c_str());
    m->prevMessage = message;
    AppWarp::Client::getInstance()->sendChat(message);
    
}

void Multiplayer::recoverConnection()
{
    AppWarp::Client::getInstance()->recoverConnection();
}

#pragma mark Helper

bool Multiplayer::isPlayer(std::string name)
{
    return !Multiplayer::getInstance()->getUsername().compare(name);
}


Point Multiplayer::extractPos(std::string properties)
{
    std::vector<std::string> value = GameHelper::split(properties, '%');
    return Point(std::stof(value.at(0).c_str()), std::stof(value.at(1)));
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
    if(state == 0)
        return true;
    return false;
}


void Multiplayer::resetAllListener()
{
    AppWarp::Client* client = AppWarp::Client::getInstance();
    client->setConnectionRequestListener(this);
    client->setZoneRequestListener(this);
    client->setNotificationListener(this);
    client->setRoomRequestListener(this);
}


bool Multiplayer::isCommandsEmpty()
{
    return commands.empty();
}


command_t Multiplayer::popCommands()
{
    command_t front = commands.front();
    commands.pop();
    return front;
}


command_t Multiplayer::exractMessage(std::string message)
{
    std::vector<std::string> temp = GameHelper::split(message, ';');
    command_t command;
    command.scene = atoi(temp.at(0).c_str());
    command.operation = atoi(temp.at(1).c_str());
    command.properties = temp.at(2);
    return command;
}

std::string Multiplayer::buildProperties(std::initializer_list<std::string> properties)
{
    std::string value;
    for(auto i = properties.begin(); i != properties.end(); i++)
    {
        value += *i + '%';
    }
    return value;

}

std::string Multiplayer::buildMessage(int scene, int op, std::string properties)
{
    return std::to_string(scene) + ';' + std::to_string(op) + ';' + properties + ';';
}

bool Multiplayer::isCommandValid(int scene, command_t command)
{
    if (command.scene == scene || command.scene == MP_GLOBLE)
        return true;
    return false;
}

#pragma mark Connection Request Listener

void Multiplayer::onConnectDone(int result, int)
{
    switch (result) {
        case AppWarp::ResultCode::success:
            callback->onConnectDone();
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


#pragma mark Notification Listeners

void Multiplayer::onChatReceived(AppWarp::chat chat)
{
    command_t command = exractMessage(chat.chat);
    command.sender = chat.sender;
    
    commands.push(command);
}


void Multiplayer::onUserJoinedRoom(AppWarp::room, std::string name)
{
    CCLOG("%s joined", name.c_str());
    
    command_t command;
    command.scene = MP_GLOBLE;
    command.sender = name;
    command.operation = OP_GB_USER_JOINED;
    
    commands.push(command);
    
}


void Multiplayer::onUserLeftRoom(AppWarp::room, std::string name)
{
    CCLOG("%s left", name.c_str());
    
    command_t command;
    command.scene = MP_GLOBLE;
    command.sender = name;
    command.operation = OP_GB_USER_LEFT;
    
    commands.push(command);
}


#pragma mark Room Request Listeners

void Multiplayer::onJoinLobbyDone(AppWarp::lobby event)
{
    if (event.result == AppWarp::ResultCode::success){
        AppWarp::Client::getInstance()->subscribeLobby();
        callback->onJoinLobbyDone();
    }
    else{
        CCLOG("fail to join lobby");
    }
}

void Multiplayer::onLeaveLobbyDone(AppWarp::lobby event)
{
    if (event.result == AppWarp::ResultCode::success){
        callback->onLeaveLobbyDone();
    }else{
        CCLOG("fail to leave lobby");
    }
}

void Multiplayer::onSubscribeLobbyDone(AppWarp::lobby event)
{
    if (event.result == AppWarp::ResultCode::success){
        callback->onSubscribeLobbyDone();
    }else{
        CCLOG("fail to subscribe lobby");
    }
}

void Multiplayer::onUnsubscribeLobbyDone(AppWarp::lobby event)
{
    if (event.result == AppWarp::ResultCode::success){
        callback->onUnsubscribeLobbyDone();
    }else{
        CCLOG("fail to unsubscribe lobby");
    }
}

void Multiplayer::onJoinRoomDone(AppWarp::room event)
{
    if (event.result == AppWarp::ResultCode::success) {
        AppWarp::Client::getInstance()->subscribeRoom(getRoomID());
        callback->onJoinRoomDone();
    }
    else{
        CCLOG("fail to join room");
    }
}


void Multiplayer::onLeaveRoomDone(AppWarp::room event)
{
    if (event.result == AppWarp::ResultCode::success)
    {
        callback->onLeaveRoomDone();
    }
    else{
        CCLOG("fail to leave room");
    }
}


void Multiplayer::onSubscribeRoomDone(AppWarp::room event)
{
    if (event.result == AppWarp::ResultCode::success) {
        callback->onSubscribeRoomDone();
    }
    else{
        CCLOG("fail to join room");
    }
}


void Multiplayer::onUnsubscribeRoomDone(AppWarp::room event)
{
    if (event.result == AppWarp::ResultCode::success)
    {
        AppWarp::Client::getInstance()->leaveRoom(getRoomID());
        this->roomID = "";
        callback->onUnsubscribeRoomDone();
    }
    else
    {
        CCLOG("fail to unsubscribe room");
    }
    
}

void Multiplayer::onGetLiveRoomInfoDone(AppWarp::liveroom event)
{
    if (event.result == AppWarp::ResultCode::success) {
        callback->onGetLiveRoomInfoDone(event.rm.roomId,
                                        event.rm.owner,
                                        event.rm.maxUsers,
                                        event.rm.name,
                                        event.customData,
                                        event.users,
                                        event.properties);
    }
    else
    {
        CCLOG("fail to get live room info");
    }
}



#pragma mark Zone Request Listener

void Multiplayer::onGetAllRoomsDone(AppWarp::liveresult result)
{
    AppWarp::Client *warpClientRef;
    warpClientRef = AppWarp::Client::getInstance();
    for(std::vector<int>::size_type i = 0; i != result.list.size(); i++){
        warpClientRef->getLiveRoomInfo(result.list[i]);
    }
    
}

void Multiplayer::onCreateRoomDone(AppWarp::room event)
{
    if (event.result == AppWarp::ResultCode::success) {
        AppWarp::Client::getInstance()->joinRoom(event.roomId);
        callback->onCreateRoomDone(event.roomId, event.owner, event.maxUsers, event.name);
    }
    else
    {
        CCLOG("fail to create room");
    }
}


void Multiplayer::onSendChatDone(int result)
{
    isSuccessSent = true;
    if (result == AppWarp::ResultCode::success)
        CCLOG("sent success");
    else
        CCLOG("sent failed");
    
}