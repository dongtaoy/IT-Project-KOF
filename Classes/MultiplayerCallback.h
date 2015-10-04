//
//  MultiplayerCallback.h
//  KOF
//
//  Created by Dongtao Yu on 25/09/2015.
//
//

#ifndef MultiplayerCallback_h
#define MultiplayerCallback_h

class MultiplayerCallback
{
public:
    
#pragma mark Lobby Request Listeners
    virtual void onJoinLobbyDone(){ CCLOG("join lobby done...");};
    virtual void onSubscribeLobbyDone(){ CCLOG("subscribe loby done"); };
    
    virtual void onUnsubscribeLobbyDone() { CCLOG("unsubsribe lobby done"); };
    virtual void onLeaveLobbyDone(){ CCLOG("leave lobby done...");};
    
#pragma mark Room Request Listeners

    virtual void onJoinRoomDone(){ CCLOG("join room done..."); };
    virtual void onSubscribeRoomDone(){ CCLOG("Subscribe room done..."); };
    
    
    virtual void onUnsubscribeRoomDone(){ CCLOG("unsubsribe room done..."); };
    virtual void onLeaveRoomDone(){ CCLOG("leave room done..."); };
    
    virtual void onGetLiveRoomInfoDone(std::string roomId,
                                       std::string owner,
                                       int maxUsers,
                                       std::string name,
                                       std::string customData,
                                       std::vector<std::string> users,
                                       std::map<std::string, std::string> properties){ CCLOG("get live room info done..."); };
    
#pragma mark Zone Request Listener
    virtual void onCreateRoomDone(std::string roomId, std::string owner, int maxUsers, std::string name){ CCLOG("create room done..."); };
    
    virtual void onConnectDone(){ CCLOG("connection done"); };
    
    virtual void onRoomCreated(std::string roomID, std::string bestOf, std::string background){ CCLOG("room created"); };
    virtual void onRoomDestroyed(std::string roomID) { CCLOG("room destroyed"); };
};

#endif /* MultiplayerCallback_h */
