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

void PhotonMultiplayer::opCreateRoom(std::map<std::string, std::string> properties)
{
    ExitGames::Common::Hashtable p = ExitGames::Common::Hashtable();
    
    ExitGames::Common::JString backgroundK = ROOM_PROPERTY_BACKGROUND;
    ExitGames::Common::JString backgroundV = properties.find(ROOM_PROPERTY_BACKGROUND)->second.c_str();
    
    printf("backgorund: %ls\n", backgroundV.cstr());
    
    ExitGames::Common::JString bestofK = ROOM_PROPERTY_BESTOF;
    ExitGames::Common::JString bestofV = properties.find(ROOM_PROPERTY_BESTOF)->second.c_str();
    
    printf("backgorund: %ls\n", bestofV.cstr());
    
    ExitGames::Common::JString name = "123";
    
    p.put(backgroundK, backgroundV);
    p.put(bestofK, bestofV);
    
    ExitGames::Common::JVector<ExitGames::Common::JString> v = ExitGames::Common::JVector<ExitGames::Common::JString>();
    
    v.addElement(backgroundK);
    v.addElement(bestofK);
    
    
//    p.put(ROOM_PROPERTY_BACKGROUND, properties.find(ROOM_PROPERTY_BACKGROUND)->second, 1);
//    p.put(ROOM_PROPERTY_BESTOF, properties.find(ROOM_PROPERTY_BESTOF)->second, 1);
    c.opCreateRoom(
                   name,
                   true,
                   true,
                   2,
                   p,
                   v,
                   ExitGames::Common::JString(),
                   ExitGames::LoadBalancing::LobbyType::DEFAULT,
                   INT_MAX/2,
                   3600);
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


std::string PhotonMultiplayer::JStringToString(ExitGames::Common::JString input)
{
    std::string output;
    for (int i = 0 ; i < input.length(); i++)
    {
        if (input.charAt(i) != '\"'){
            output += input.charAt(i);
        }
    }
    
    
    return output;
}

std::vector<std::tuple<std::string, int, int, std::map<std::string, std::string>>>  PhotonMultiplayer::getRoomList(void)
{
    std::vector<std::tuple<std::string, int, int, std::map<std::string, std::string>>> v;
    
    ExitGames::Common::JVector<ExitGames::LoadBalancing::Room*> r = c.getRoomList();
    for (int i = 0 ; i < r.getSize() ; i++)
    {
        std::string name = JStringToString(r[i]->getName());
        int numUsers = r[i]->getPlayerCount();
        int maxUsers = r[i]->getMaxPlayers();
        std::map<std::string, std::string> p;
        ExitGames::Common::JString backgroundK = ROOM_PROPERTY_BACKGROUND;
        std::string backgroundV = JStringToString(r[i]->getCustomProperties().getValue(backgroundK)->toString());
        ExitGames::Common::JString bestofK = ROOM_PROPERTY_BESTOF;
        std::string bestofV = JStringToString(r[i]->getCustomProperties().getValue(bestofK)->toString());
        p[ROOM_PROPERTY_BACKGROUND] = backgroundV;
        p[ROOM_PROPERTY_BESTOF] = bestofV;
        v.push_back(std::make_tuple(name, numUsers, maxUsers, p));
    }
    return v;
}


// protocol implementations

void PhotonMultiplayer::debugReturn(int /*debugLevel*/, const ExitGames::Common::JString& string)
{
    printf("debugReturn %ls", string.cstr());
}

void PhotonMultiplayer::connectionErrorReturn(int errorCode)
{
    printf("connectionErrorReturn %d", errorCode);
}

void PhotonMultiplayer::clientErrorReturn(int errorCode)
{
    printf("clientErrorReturn %d", errorCode);
}

void PhotonMultiplayer::warningReturn(int warningCode)
{
    printf("warningReturn %d", warningCode);
}

void PhotonMultiplayer::serverErrorReturn(int errorCode)
{
    printf("serverErrorReturn %d", errorCode);
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
    printf("RoundTripTime: %ds\n", c.getRoundTripTime());
    printf("RoundTripTimeVariance: %ds\n", c.getRoundTripTimeVariance());
    printf("ConnectReturn: %d", errorCode);
    if (errorCode) {
        
        return;
    }
    listener->onConnectDone();
    
}

void PhotonMultiplayer::disconnectReturn(void)
{
}

void PhotonMultiplayer::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    for(int i = 0 ; i < gameProperties.getKeys().getSize(); i++)
    {
        printf("%ls", gameProperties.getKeys()[i].toString().cstr());
    }
    printf("createRoomReturn: %d", errorCode);
//    callback 
    
}
void PhotonMultiplayer::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    printf("joinRoomReturn: %d", errorCode);
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