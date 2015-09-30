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
};

#endif /* MultiplayerCallback_h */
