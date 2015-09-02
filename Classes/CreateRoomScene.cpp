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
    
    
    auto node = CSLoader::createNode(CREATE_ROOM_SCENE_FILE);
    Button* buttonBack =  static_cast<Button*>(node->getChildByName(BACK_BUTTON));
    assert(buttonBack);
    
    Button* buttonCreate = static_cast<Button*>(node->getChildByName(CREATE_BUTTON));
    assert(buttonCreate);
    
    buttonCreate->addTouchEventListener(CC_CALLBACK_2(CreateRoomScene::CreateRoom, this));
    buttonBack->addTouchEventListener(CC_CALLBACK_2(CreateRoomScene::GotoChooseRoomScene, this));
    

    for(int i = 1 ; i <= NUM_BACKGROUNDS ; i ++)
    {
        Widget* image = static_cast<Widget*>(node->getChildByName(CREATE_ROOM_SCENE_BACKGROUND_PREFIX+std::to_string(i)));
        image->addTouchEventListener(CC_CALLBACK_2(CreateRoomScene::BackgroundSelectedChanged, this));
    }
    
    for(int i = 1 ; i <= NUM_BESTOF ; i ++)
    {
        CheckBox* checkbox = static_cast<CheckBox*>(node->getChildByName(CREATE_ROOM_SCENE_CHECKBOX_PREFIX+std::to_string(i)));
        
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



void CreateRoomScene::CreateRoom(Ref* node, ui::Widget::TouchEventType type)
{
    
    if(type == Widget::TouchEventType::ENDED){
        
        if(backgroundSelected != NULL && bestOfSelected != NULL)
        {
            std::string background = static_cast<Node*>(backgroundSelected)->getName();
            std::string bestof = static_cast<Node*>(bestOfSelected)->getChildByName<Text*>(CREATE_ROOM_SCENE_BESTOF_LABEL)->getString();
            
            std::map<std::string, std::string> properties ={{ROOM_PROPERTY_BACKGROUND, background},{ROOM_PROPERTY_BESTOF, bestof}};
            
            Multiplayer::getInstance()->createRoom(this, properties);
        }
        
    }
}

void CreateRoomScene::onCreateRoomDone(AppWarp::room event)
{
    if(event.result == AppWarp::ResultCode::success){
        CCLOG("CREATED %s", event.roomId.c_str());
        Multiplayer::getInstance()->setRoomID(event.roomId);
        auto scene = ChooseCharactorScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }else{
        MessageBox("CONNECTION ERROR", "ERROR");
    }
    Multiplayer::getInstance()->resetZoneRequestListener();
}