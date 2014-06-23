
#ifndef __client1__next__
#define __client1__next__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <limits>
using namespace cocos2d;
using namespace CocosDenshion;
class nextLayer:public LayerColor{
public:
    virtual bool init();
 
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
    CREATE_FUNC(nextLayer);
};
#endif /* defined(__client1__next__) */
