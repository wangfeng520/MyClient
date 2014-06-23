
#ifndef __client1__zhuangtaiLoad__
#define __client1__zhuangtaiLoad__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "LoadingLayer.h"
//此类需要传递json数据，获取上面的人物资金，体力等
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class zhuangtai:public cocos2d::LayerColor{
public:
    virtual bool init();
    virtual void onExit();
    ~zhuangtai();
    
    void send_103();
    void rec_103();
    
    
    
    Loading * load;
   
    Label *levelLabel;
    void sendZGBagInfo();
    void receiveZGBagInfo();
    Menu *backGrounds;
//   static zhuangtai * creat();
    void removeZGBag();
    void setGid(int gid);
    int getGid();
    int _gid;

    int _goldNum;
    int _agNum;
    int _tiNum;
    int _qiNum;
    int _expNum;
    Label *_goldLabel;
    Label *_ag;
    Label *_ti;
    Label *_qi;
    Label * nameLabel;
    int coin;
    int level;
    int vipNum;
    int Exp;
    int maxExp;
    int gas;
    int power;
    int gold;
    int __coin;
    
    std::string rolename;
    std::stringstream icoin;
    std::stringstream igold;
    std::stringstream ilevel;
   const  char * _gold;
   const  char * _coin;
   const  char * _level;
    const  char * _rollName;
    void setCoin(int coin);
    int getExp();
    int getGas();
    int getPower();
    int getMaxExp();
    int getGold();
    void openZGBag();
    int getcoin();
    void reload();
    void receiveUpdata();
    void  zhuangtaiInit();
    
    void clkLinkRecharge();
    void clkHomeLink();
    
    void initData();
    
    Sprite * _exp;
    Sprite *backGround;
//    CCMenuItemImage *homeLink;
//    CCMenuItemImage *linkFecharge;
    void removeB();
    void upData();
    
    Size size;
    CREATE_FUNC(zhuangtai);
};
#endif /* defined(__client1__zhuangtaiLoad__) */
