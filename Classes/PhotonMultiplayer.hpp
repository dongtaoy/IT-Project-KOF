//
//  PhotonMultiplayer.hpp
//  KOF
//
//  Created by Dongtao Yu on 6/10/2015.
//
//

#ifndef PhotonMultiplayer_hpp
#define PhotonMultiplayer_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "LoadBalancing-cpp/inc/Client.h"


class PhotonMultiplayer : private ExitGames::LoadBalancing::Listener
{
public:
    static PhotonMultiplayer* _instance;
    static void initialize(ExitGames::Common::JString);
    static PhotonMultiplayer* getInstance();
    
    void service();
    
    void run(void);
    void connect(void);
    void opCreateRoom(void);
    void opJoinRandomRoom(void);
    void disconnect(void);
    void sendEvent(void);
    
private:
    PhotonMultiplayer(ExitGames::Common::JString);
    // receive and print out debug out here
    virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);
    
    // implement your error-handling here
    virtual void connectionErrorReturn(int errorCode);
    virtual void clientErrorReturn(int errorCode);
    virtual void warningReturn(int warningCode);
    virtual void serverErrorReturn(int errorCode);
    
    // events, triggered by certain operations of all players in the same room
    virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
    virtual void leaveRoomEventAction(int playerNr, bool isInactive);
    virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);
    
    virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
    virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
    virtual void onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers);
    
    // callbacks for operations on PhotonLoadBalancing server
    virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString);
    virtual void disconnectReturn(void);
    virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
    virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
    virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
    virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
    virtual void joinLobbyReturn(void);
    virtual void leaveLobbyReturn(void);
    
    ExitGames::LoadBalancing::Client c;
    ExitGames::Common::Logger mLogger;
};


#endif /* PhotonMultiplayer_hpp */
