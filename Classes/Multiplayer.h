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
#include "MultiplayerCallback.h"

#define MAX_USERS 2


class Multiplayer : public AppWarp::ConnectionRequestListener, public AppWarp::ZoneRequestListener, public AppWarp::RoomRequestListener, public AppWarp::NotificationListener
{
    

protected:
#pragma mark Variables
    CC_SYNTHESIZE(std::string, username, Username);
    CC_SYNTHESIZE(std::string, userCharacter, UserCharacter);
    CC_SYNTHESIZE(std::string, opponentUsername, OpponentUsername);
    CC_SYNTHESIZE(std::string, opponentCharacter, OpponentCharacter);
    CC_SYNTHESIZE(std::string, roomID, RoomID);
    CC_SYNTHESIZE(std::string, background, Background);
    CC_SYNTHESIZE(int, bestof, Bestof);
    CC_SYNTHESIZE(std::queue<command_t>, commands, Commands);
    CC_SYNTHESIZE(MultiplayerCallback*, callback, Callback);
    CC_SYNTHESIZE(std::string, prevMessage, PrevMessage);
    
    
public:
#pragma mark Constructors
    static Multiplayer* getInstance();
    static void initialize(std::string);
    
    
    
#pragma mark Actions
    static void joinRoom(MultiplayerCallback*);
    static void fetchRooms(MultiplayerCallback*);
    static void createRoom(MultiplayerCallback*, std::map<std::string, std::string>);
    static void unsubsribeRoom(MultiplayerCallback*);
    static void connect(MultiplayerCallback*);
    static void recoverConnection();
    static void sendChat(int, int, std::string = "");
    static void sendChat(std::string);
    
#pragma mark Helper
    void resetAllListener();
    bool isConnected();
    bool isCommandsEmpty();
    command_t popCommands();
    static command_t exractMessage(std::string);
    static bool isCommandValid(int, command_t);
    static std::string buildMessage(int scene, int op, std::string properties="");
    static std::string buildProperties(std::initializer_list<std::string> properties);
    static bool isPlayer(std::string name);
private:
    static Multiplayer* _instance;
    
    
#pragma mark Private constructor
    Multiplayer(std::string username);
    
#pragma mark Connection listener
    void onConnectDone(int,int);
    
#pragma mark Zone Request Listener
    void onGetAllRoomsDone(AppWarp::liveresult);
    
#pragma mark Notification Listener
    void onUserJoinedRoom(AppWarp::room, std::string);
    void onUserLeftRoom(AppWarp::room, std::string);
    void onChatReceived(AppWarp::chat);
    
#pragma mark Room Request Listener
    void onJoinRoomDone(AppWarp::room);
    void onLeaveRoomDone(AppWarp::room);
    
    void onSubscribeRoomDone(AppWarp::room);
    void onUnsubscribeRoomDone(AppWarp::room);
    
#pragma mark Zone Request Listener
    void onGetLiveRoomInfoDone(AppWarp::liveroom);
    void onCreateRoomDone(AppWarp::room);
    
};

#endif /* defined(__KOF__Multiplayer__) */
