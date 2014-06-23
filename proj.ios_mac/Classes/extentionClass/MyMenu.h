#ifndef __Client__MyMenu__
#define __Client__MyMenu__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
class MyMenu:public cocos2d::Menu{
public:
   
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    bool moved;
    CREATE_FUNC(MyMenu);
};
#endif /* defined(__Client__MyMenu__) */
