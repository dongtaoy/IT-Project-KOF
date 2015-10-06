//
//  PhotonMultiplayer.cpp
//  KOF
//
//  Created by Dongtao Yu on 6/10/2015.
//
//

#include "PhotonMultiplayer.hpp"


static const ExitGames::Common::JString appId = L"baa6d632-3cd1-4304-95fc-50bd619551a6"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";


PhotonMultiplayer* PhotonMultiplayer::_instance = NULL;

void PhotonMultiplayer::initialize(ExitGames::Common::JString name)
{
    if (_instance == NULL)
    {
        _instance = new PhotonMultiplayer(name);
    }
}


PhotonMultiplayer* PhotonMultiplayer::getInstance()
{
    return _instance;
}

// functions
PhotonMultiplayer::PhotonMultiplayer(ExitGames::Common::JString name)
:c(*this, appId, appVersion, name, ExitGames::Photon::ConnectionProtocol::UDP, ExitGames::LoadBalancing::AuthenticationValues(), true, false)
{
    
}

void PhotonMultiplayer::service()
{
    c.service();
}

void PhotonMultiplayer::connect(void)
{
    CCLOG("connecting");
    c.connect();
    
}

void PhotonMultiplayer::disconnect(void)
{
    
}

void PhotonMultiplayer::opCreateRoom(void)
{
    
}

void PhotonMultiplayer::opJoinRandomRoom(void)
{
}

void PhotonMultiplayer::run(void)
{
}

void PhotonMultiplayer::sendEvent(void)
{
}

void PhotonMultiplayer::setListener(MultiplayerCallback* l)
{
    this->listener = l;
}

bool PhotonMultiplayer::isConnected()
{
    if (c.getState() == ExitGames::LoadBalancing::PeerStates::JoinedLobby)
        return true;
    
    return false;
}



// protocol implementations

void PhotonMultiplayer::debugReturn(int /*debugLevel*/, const ExitGames::Common::JString& string)
{
    printf("return %ls", string.cstr());
}

void PhotonMultiplayer::connectionErrorReturn(int errorCode)
{
    printf("return %d", errorCode);
}

void PhotonMultiplayer::clientErrorReturn(int errorCode)
{
    printf("return %d", errorCode);
}

void PhotonMultiplayer::warningReturn(int warningCode)
{
    printf("return %d", warningCode);
}

void PhotonMultiplayer::serverErrorReturn(int errorCode)
{
    printf("return %d", errorCode);
}



void PhotonMultiplayer::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& /*playernrs*/, const ExitGames::LoadBalancing::Player& player)
{
}

void PhotonMultiplayer::leaveRoomEventAction(int playerNr, bool isInactive)
{
}

void PhotonMultiplayer::customEventAction(int /*playerNr*/, nByte /*eventCode*/, const ExitGames::Common::Object& eventContent)
{
}

void PhotonMultiplayer::connectReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
    printf("here\n %d\n", c.getRoundTripTime());
    printf("%d\n", c.getRoundTripTimeVariance());
    printf("return %d", errorCode);
    if (errorCode) {
        return;
    }
    listener->onConnectDone();
    
}

void PhotonMultiplayer::disconnectReturn(void)
{
}

void PhotonMultiplayer::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
}
void PhotonMultiplayer::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
}

void PhotonMultiplayer::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
}

void PhotonMultiplayer::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
}

void PhotonMultiplayer::joinLobbyReturn(void)
{
    
}

void PhotonMultiplayer::leaveLobbyReturn(void)
{
}

void PhotonMultiplayer::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
}

void PhotonMultiplayer::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
}

void PhotonMultiplayer::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers)
{
    c.selectRegion("au");
}