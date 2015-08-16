#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class HelloWorld : public cocos2d::Layer,TableViewDataSource,TableViewDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
public:
    
    virtual Size cellSizeForTable(TableView *table);
    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
public:
    virtual void scrollViewDidScroll(ScrollView* view){};
    
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
};

#endif // __HELLOWORLD_SCENE_H__