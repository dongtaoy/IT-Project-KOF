//
//  HelloWorld.cpp
//  KOF
//
//  Created by Dongtao Yu on 16/08/2015.
//
//

#include "HelloWorld.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }
    
    
    TableView *tv = TableView::create(this, Size(300, 300));
    tv->setAnchorPoint(Point(0,0));// Set the anchor
    tv->setPosition(100,0);
    tv->setDelegate(this); // Setting the line click event
    
    addChild(tv);
    return true;
}

Size HelloWorld::cellSizeForTable(TableView *table) {// Returns the size of each TableViewCell
    return Size(300, 50);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView* table, ssize_t idx) {// Returns a TableViewCell, the getView method is equivalent to Android BaseAdapter
    TableViewCell *cell = table->dequeueCell();
    LabelTTF *label;
    if (cell == NULL) {
        cell = TableViewCell::create();
        label = LabelTTF::create();
        label->setTag(2);
        label->setFontSize(20);
        label->setAnchorPoint(Point(0,0));
        cell->addChild(label);
    } else {
        label = (LabelTTF*) cell->getChildByTag(2);
    }
    label->setString(StringUtils::format("label %d", (int)idx));
    
    return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView *table) {// Returns the number of rows of TableView
    return 100;
}

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell){// TableView click event
    LabelTTF *label = (LabelTTF*)cell->getChildByTag(2);
    log("click %s",label->getString().c_str());
}