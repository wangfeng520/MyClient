//
//  homePage.h
//  Client
//
//  Created by lh on 13-2-22.

#ifndef __Client__homePage__
#define __Client__homePage__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MyMenu.h"
#include "LevelMap.h"
#include "Fire.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;


class homePage:public cocos2d::Layer{
public:

    ~homePage();
    virtual void onExit();
    
    virtual bool init();
    
    
    void openNewBuZhen();
    void openArenaWindow();
    
  
    CREATE_FUNC(homePage);
    
private:
    void recPersonal();
    void recEquips();
    
    void rec_4500();
    
    

    //烟雾 大雁 特效
//    void maintexiaoDY();
//    void maintexiaoYW();
//    void runtexiaoDY();
//    void runtexiaoYW();
//    void dyvisable();
//    void ywvisable();
    
    void zhuangtaiLoad();
    void initTitle();
    void downBtnLoading();
    void btnsLoading();
    
    
    void mainView();
    void openPersonal();
    void openHeCheng();
    void employFriends();
    void recharge();
    void openMailWindow();
    
    
    
    void removelayers();

    Size size;
    
    LevelMap * layerMainMap;
//    personalinfo *layerPersonInfo;
//    newBuZhen * layerNewBuZhen; 
//    
    
    MenuItemImage *btnHeCheng;
    MenuItemImage *btnEmployFriends;
    MenuItemImage *btnPersonal;
    MenuItemImage *btnArena;
    MenuItemImage *btnMail;
    MenuItemImage *homeLink;
    MenuItemImage *linkFecharge;
    Menu *menu;
    
 //   Loading * load;
    
    
   
};
#endif /* defined(__Client__homePage__) */
