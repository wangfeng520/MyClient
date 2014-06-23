
#ifndef __client1__popwindow__
#define __client1__popwindow__

#include <iostream>
#include"cocos2d.h"
#include "myobject.h"
//#include "LodingLayer.h"
//#include "newBuZhen.h"

USING_NS_CC;
using namespace std;



class buildingpop:public LayerColor{
public:
    
    
    virtual bool init();
//    virtual void onExit();
    ~buildingpop();
    
//    virtual void  registerWithTouchDispatcher();
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    bool istouch;
    
    void receiveFireData();
    void show(MapItem *item);
    void hide();
    
    void close();
    void fight();
    void buzhen();
    
    
    
    
    
    
MapItem *item;
Menu * btnsMenu;
    MenuItemImage * ft;
    MenuItemImage * cl;
    MenuItemImage * bz;

    bool lock;
    
    LabelTTF *name;
    LabelTTF *namedesc;
    LabelTTF *name1;;
    LabelTTF *namedesc1;
    LabelTTF *name2;
    
    LabelTTF* goldlabel;
    LabelTTF* weilabel;
    LabelTTF* wulabel;
    
    CREATE_FUNC(buildingpop);
};


#endif /* defined(__client1__popwindow__) */
