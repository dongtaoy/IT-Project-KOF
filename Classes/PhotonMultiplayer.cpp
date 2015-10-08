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

ExitGames::Common::JString PhotonMultiplayer::buildProperties(std::initializer_list<std::string> properties)
{
    std::string value;
    for(auto i = properties.begin(); i != properties.end(); i++)
    {
        value += *i + '%';
    }
    return value.c_str();
    
}

ExitGames::Common::JString PhotonMultiplayer::buildEvent(int scene, int op, std::string properties)
{
    ExitGames::Common::JString output;
    output += std::to_string(scene).c_str();
    output += ';';
    output += std::to_string(op).c_str();
    output += ';';
    output += properties.c_str();
    output += ';';
    return output;
}

command_t PhotonMultiplayer::extractEvent(std::string message)
{
    std::vector<std::string> temp = GameHelper::split(message, ';');
    command_t command;
    command.scene = atoi(temp.at(0).c_str());
    command.operation = atoi(temp.at(1).c_str());
    command.properties = temp.at(2);
    return command;
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
    
    ExitGames::Common::JString name = GameHelper::randomIntString(5).c_str();
    
    p.put(backgroundK, backgroundV);
    p.put(bestofK, bestofV);
    
    ExitGames::Common::JVector<ExitGames::Common::JString> v = ExitGames::Common::JVector<ExitGames::Common::JString>();
    
    v.addElement(backgroundK);
    v.addElement(bestofK);
    
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


void PhotonMultiplayer::opLeaveRoom()
{
    c.opLeaveRoom();
}

void PhotonMultiplayer::opJoinRoom(std::string id)
{
    c.opJoinRoom(id.c_str());
}

void PhotonMultiplayer::opJoinRandomRoom(void)
{
}

void PhotonMultiplayer::run(void)
{
}

void PhotonMultiplayer::sendEvent(std::string event)
{
    
    c.opRaiseEvent(true, StringToJString(event), 0);
}

void PhotonMultiplayer::sendEvent(int scene, int op, std::string properties)
{
//    printf("sending events");
    c.opRaiseEvent(true, buildEvent(scene, op, properties), 0);
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

std::string PhotonMultiplayer::getRoomID()
{
    return JStringToString(c.getCurrentlyJoinedRoom().getName());
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

ExitGames::Common::JString PhotonMultiplayer::StringToJString(std::string input)
{
    ExitGames::Common::JString output = input.c_str();
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
    listener->joinRoomEventAction();
}

void PhotonMultiplayer::leaveRoomEventAction(int playerNr, bool isInactive)
{
    listener->leaveRoomEventAction();
}


void PhotonMultiplayer::customEventAction(int /*playerNr*/, nByte /*eventCode*/, const ExitGames::Common::Object& eventContent)
{
    listener->customEventAction(extractEvent(JStringToString(eventContent.toString())));
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
    printf("createRoomReturn: %d", errorCode);
    listener->onCreateRoomDone();
}
void PhotonMultiplayer::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    
    printf("joinRoomReturn: %d", errorCode);
    listener->onJoinRoomDone();
}

void PhotonMultiplayer::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    
}

void PhotonMultiplayer::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
    printf("leaveRoomReturn: %d", errorCode);
    listener->onLeaveRoomDone();
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


void PhotonMultiplayer::onRoomListUpdate(void)
{
    printf("onRoomListUpdate");
    listener->onRoomListUpdate();
}