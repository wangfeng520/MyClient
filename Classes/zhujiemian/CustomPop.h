//
//  CustomPop.h
//  wx
//
//  Created by guoyahui on 13-6-29.
//
//

#ifndef __wx__CustomPop__
#define __wx__CustomPop__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CustomPop:public LayerColor
{
public:
    
    static void show(const char* str);
    
private:
    CREATE_FUNC(CustomPop);
    virtual bool init();
    //    virtual void onExit();
    CustomPop();
    ~CustomPop();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
    void close();
    
    bool istouch;
    
    Menu * btnsMenu;
    
    
    Label* desc;
};

#endif /* defined(__wx__CustomPop__) */
