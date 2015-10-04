//
//  GameCenterDelegate.hpp
//  KOF
//
//  Created by Dongtao Yu on 4/10/2015.
//
//

#ifndef GameCenterDelegate_hpp
#define GameCenterDelegate_hpp

#include <stdio.h>
#include "GKHDelegate.h"
#include "GKCppAlternatives.h"

class GameCenterDelegate : public GKHDelegate
{
public:
    static GameCenterDelegate* getInstance();
    static void initialize();
    
    
private:
    GameCenterDelegate();
    static GameCenterDelegate* _instance;
    
    // Players
    void onLocalPlayerAuthenticationChanged();
    
    void onFriendsListRecieved(std::vector<std::string> friends);
    void onPlayerInfoReceived(std::vector<GKPlayerCpp> playerInfo);
//
//    // Scores
//    void onScoresSubmitted(bool success);
//    void onScoresReceived(std::vector<GKScoreCpp> scores);
//    
//    // Achievements
//    void onAchievementReported(GKAchievementCpp achievement);
//    void onResetAchievements(bool success);
//    void onAchievementsLoaded(std::map<std::string, GKAchievementCpp> achievements);
//    
//    // Game Centre Views
//    void onLeaderboardViewDismissed();
//    void onAchievementsViewDismissed();
};

#endif /* GameCenterDelegate_hpp */
