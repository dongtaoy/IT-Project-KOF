//
//  TestSplashScene.cpp
//  KOF
//
//  Created by 小七爷 on 15/11/1.
//
//

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "catch.hpp"
#include "Fighter.h"

TEST_CASE("Test Splash Scene related node")
{
     auto node = CSLoader::createNode("SplashScreen.csb");
     ui::LoadingBar* loadingBar = static_cast<ui::LoadingBar*>(node->getChildByName("SplashScreen")->getChildByName("loadingBar"));
}