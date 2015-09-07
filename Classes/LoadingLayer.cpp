//
//  LoadingLayer.cpp
//  KOF
//
//  Created by Dongtao Yu on 7/09/2015.
//
//

#include "LoadingLayer.h"

USING_NS_CC;


bool LoadingLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(cocos2d::Color4B(0 , 0, 0, 0)))
    {
        return false;
    }
    
    this->setName("LoadingLayer");
    auto node = CSLoader::createNode("LoadingLayer.csb");
    this->setOpacity(80);
    this->addChild(node);
    
    return true;
}

void LoadingLayer::AddLoadingLayer(Node* scene)
{
    auto node = LoadingLayer::create();
    scene->addChild(node);
}

void LoadingLayer::RemoveLoadingLayer(Node* scene)
{
    scene->removeChildByName("LoadingLayer");
}


void LoadingLayer::AppendText(Node* scene, std::string value)
{
    auto node = scene->getChildByName("LoadingLayer")->getChildByName("LoadingLayer")->getChildByName<ui::Text*>("text");
    node->setString(node->getString() + value);
}

void LoadingLayer::SetText(Node* scene, std::string value)
{
    auto node = scene->getChildByName("LoadingLayer")->getChildByName("LoadingLayer")->getChildByName<ui::Text*>("text");
    node->setString(value);
}

void LoadingLayer::SetLoadingBarPercentage(Node* scene, float value)
{
    auto node = scene->getChildByName("LoadingLayer")->getChildByName("LoadingLayer")->getChildByName<ui::LoadingBar*>("loadingBar");
    node->setPercent(value);
}

void LoadingLayer::SetTextAndLoadingBar(Node* scene, bool append, std::string string, float value)
{
    if(append)
        AppendText(scene, string);
    else
        SetText(scene, string);
    
    SetLoadingBarPercentage(scene, value);
    
}