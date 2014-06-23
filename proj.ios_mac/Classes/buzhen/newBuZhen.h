#ifndef __client1__newBuZhen__
#define __client1__newBuZhen__

#include <iostream>
#include "cocos2d.h"
#include "hcitemdata.h"
#include "heroItem.h"
//#include "SocketClient.h"


USING_NS_CC;
using namespace std;

class newBuZhen:public LayerColor
{
public:
    virtual bool init();
    virtual void onExit();
    ~newBuZhen();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);

    
    void send_2306();
    void rec_2306();
    void send_2300();
    void rec_2300();
    void send_2307(int petid,int chatype,int opertype,int frompos,int topos);
    void rec_2307();
    void send_3505();
    void rec_3505();
    
    void refresh_2300();
    void refresh_2306();
    
    
    
    int dragingindex;
    int acceptindex;
    
    bool readdraging;
    bool draging;
    bool lock;
    
 //   SocketClient *sclient;
    
    heroItem * readydragingsp;
    heroItem * dragingsp;
    
    heroItem * acceptsp;
    
    CCDictionary *dic;
    
    Size size;
    
    
    
    CREATE_FUNC(newBuZhen);
};

#endif /* defined(__client1__newBuZhen__) */
