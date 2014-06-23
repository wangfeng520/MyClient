#ifndef __client1__heroItem__
#define __client1__heroItem__

#include <iostream>
#include "cocos2d.h"
#include "hcitemdata.h"

USING_NS_CC;

class heroItem:public Sprite
{
public:
    
    ~heroItem();
//    virtual void onExit();
    
    virtual bool init();
    void setData(heroItemData *obj);
    void clData();
//    void setNumVisible(bool b);
    
    heroItemData* itemdata;
    
    //    CCObject * itemData;
    
    Sprite * bkg;
    Sprite* qualitybkg;
    
    Sprite *datasp;
    
    CCLabelTTF* lablenum;
    
//    bool isNumVisible;
    
    CREATE_FUNC(heroItem);
    
    
    
};



#endif /* defined(__client1__heroItem__) */
