#ifndef __client1__LodingLayer__
#define __client1__LodingLayer__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <limits>
using namespace cocos2d;
using namespace CocosDenshion;
class Loading:public LayerColor{
public:
    virtual bool init();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    ~Loading();
    Animation *animation;
   
    Vector<SpriteFrame *> sf_vec;
    ActionInterval *go;
    CREATE_FUNC(Loading);
};
#endif /* defined(__client1__LodingLayer__) */
