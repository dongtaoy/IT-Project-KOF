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
    node->setName("LoadingLayer");
    this->addChild(node);
    
    return true;
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

void LoadingLayer::SetLoadingBarPercentage(Scene* scene, int value)
{
    
}