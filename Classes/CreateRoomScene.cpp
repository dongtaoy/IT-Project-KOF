//
//  CreateRoomScene.cpp
//  KOF
//
//  Created by Dongtao Yu on 25/08/2015.
//
//

#include "CreateRoomScene.h"

using namespace ui;
USING_NS_CC;

Scene* CreateRoomScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CreateRoomScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CreateRoomScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto node = CSLoader::createNode("CreateRoom.csb");
    Button* buttonBack =  static_cast<Button*>(node->getChildByName("buttonBack"));
    assert(buttonBack);
    
    Button* buttonCreate = static_cast<Button*>(node->getChildByName("buttonCreate"));
    assert(buttonCreate);
    
    buttonCreate->addTouchEventListener(CC_CALLBACK_2(CreateRoomScene::CreateRoom, this));
    buttonBack->addTouchEventListener(CC_CALLBACK_2(CreateRoomScene::GotoChooseRoomScene, this));
    

    for(int i = 1 ; i <= NUM_BACKGROUNDS ; i ++)
    {
        Widget* image = static_cast<Widget*>(node->getChildByName("background"+std::to_string(i)));
        image->addTouchEventListener(CC_CALLBACK_2(CreateRoomScene::BackgroundSelectedChanged, this));
    }
    
    for(int i = 1 ; i <= NUM_BESTOF ; i ++)
    {
        CheckBox* checkbox = static_cast<CheckBox*>(node->getChildByName("checkbox"+std::to_string(i)));
        
        checkbox->addEventListener(CC_CALLBACK_2(CreateRoomScene::CheckboxSelectedChanged, this));
    }
    
    this->addChild(node);
    
    return true;
}

void CreateRoomScene::CheckboxSelectedChanged(Ref* pSender, CheckBox::EventType type)
{
    if(type == CheckBox::EventType::SELECTED){
        
        if(bestOfSelected != NULL){
            static_cast<CheckBox*>(bestOfSelected)->setSelected(false);
        }
        bestOfSelected = pSender;
//        static_cast<CheckBox*>(bestOfSelected)->setSelected(true);
        
    }
    else{
        bestOfSelected = NULL;
    }
}

void CreateRoomScene::BackgroundSelectedChanged(Ref* pSender, Widget::TouchEventType type)
{
    
    if(type == Widget::TouchEventType::ENDED)
    {
        if(backgroundSelected != NULL)
        {
            RemoveSelectedBorder(backgroundSelected);
        }
        backgroundSelected = pSender;
        ShowSelectedBorder(backgroundSelected);
    }
}


void CreateRoomScene::ShowSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName(BORDER_UNSELECTED)->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName(BORDER_SELECTED)->setVisible(true);
}

void CreateRoomScene::RemoveSelectedBorder(Ref* pSender)
{
    static_cast<Node*>(pSender)->getChildByName(BORDER_SELECTED)->setVisible(false);
    static_cast<Node*>(pSender)->getChildByName(BORDER_UNSELECTED)->setVisible(true);
}


void CreateRoomScene::GotoChooseRoomScene(Ref*, ui::Widget::TouchEventType type)
{
    
    auto scene = ChooseRoomScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}



void CreateRoomScene::CreateRoom(Ref*, ui::Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED){
        
        CCLOG("%p %p", backgroundSelected, bestOfSelected);
//        auto node = this->getChildByName(CREATEROOM_SCENE);
//    
//        TextField* textRoomName = static_cast<TextField*>(node->getChildByName("spriteRoomName")->getChildByName("textRoomName"));
//    
//        std::string name = textRoomName->getString().c_str();
//    
//        if(name.compare("")){
//    
//            Multiplayer::getInstance()->createRoom(name);
//        
//            auto scene = ChooseRoomScene::createScene();
//    
//            Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
//        }
    }
}