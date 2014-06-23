#ifndef __Client__FireWork__
#define __Client__FireWork__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "skillList.h"
//#include <istream.h>
#include "cocos-ext.h"
#include "next.h"
#include "LoadingLayer.h"
#include "CData.h"
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace extension;
using namespace rapidjson;

class fireinfo:public Ref{
public:
    fireinfo(){
        personId=0;
        *buff=0;
    }
    int personId;
    int buff[5];
};
class skill:public Ref{
public:
    int releaseEffect;
    int bearEffect;
    int throwEffectId;
    
};
class chatdialogue:public Ref{
public:
    string msg;
    string name;
    int icon;
    chatdialogue(){
        msg="";
        name="";
        icon=0;
    }
};
class Fire:public cocos2d::Layer{
    
public:
    CREATE_FUNC(Fire);
    static Fire *getInstance();
    void recv_4501();
    virtual void onExit();
    void initFireData();
    
    int audionum;
    Loading *load;
    Label * label1;
    Label * label2;
    Label * label3;
    CCDictionary * ene_dic;

    Map<int, fireinfo*> player_map;
    Sprite * chatbg;
    Label * printLabel;
    double percent1;

    Map<int, chatdialogue *> * chat_dic;
    
    skillList * sk;
    Sprite * tz;
    skill * skk;
    skill * returnskills(int skillId);
    // CCLabel * reduB;
    LabelAtlas * reduB;
    LabelAtlas * reduB1;
    
    int ea;
    int chaIdd;
    int chaBattleId;
    bool chengzhan;
    Sprite * buff1;
    Sprite * buff2;
    Sprite * buff3;
    Sprite *explosion; // 战斗开始的动画开场
    virtual bool init();
//    Fire();
    ~Fire();
    void enegrySprite(Sprite * node,int star);
   
    int getaudionum();
    void throwtwice();
    void whethertwice();
    void buffbegin(int bufftype);
    void buffend();
 
    int roundss;
    Sprite * enemyIcon;

//    Map<int, MenuItemSprite *> jn_dic;
    
    Label * enemyName1;
    Label * playerName1;
    Sprite * playerIcon;
    static  Fire * fire();
    // virtual bool init();
    Sprite *eneB1;
    Sprite * normalAttack;
    int _chaCurrentPower;
    int _eneCurrentPower;
    int skillnumbers1[20];
    static  Scene * scene();
    int direction; // 阵营，1下方，2上方
    int pos;//敌我双方武将所在九宫格位置
    int  result();//返回战斗结果
    int rounds;//回合数
    int kaishi;//标记
    int battleresult;//战役结果
    int changeHp;//改变的血量
    int currHp;//当前血量
    int eneBID;//敌人ID
    int totalHp;//血量上限
    int _actionId;//动作ID
    int _star;//星级
    int _skillId;//技能ID;
    Sprite *tx;//受伤特效
    Sprite * texiao;//技能特效
    Sprite * mz;//命中特效
    
    Sprite *label;//CCLabel
    Sprite * enemy;
    Sprite * player;
    Scale9Sprite * m_pNextBG;
    Label *  chatBounder;
    
    bool first;
    int _eneBattId[9];//多
    int _eneChaid[9]; //个
    int _eneChanHp[9];//敌
    int _eneCurrHp[9];//人
    int _eneTotHp[9]; //数
    int _eneActId[9]; //组
    int _chaBattleId;
    int _chaId;
    int _length;
    rapidjson::Value  _json;
    rapidjson::Value startValue;
    rapidjson::Value stepData;
    rapidjson::Value data;
    
//    rapidjson::Document d2;
    int j;
    int t;
    void setJson();
    rapidjson::Value getJson();
  
  

    void jsonData();//解析json 步骤1
    
    void getJsonData();   //  步骤2
    
    void attackData(); // 攻击数据 步骤3
    void actionAttack(int eneBattleId,int eneChaID,int eneChangeHp,int eneCurrentHp,int eneTotalHp,int actionID,int chaBattleID,int chaId,int skillId);//攻击者攻击动画 // 步骤4
    void moreActionAttack(int * eneBattId, int * eneChaid,int * eneChanHp,int * eneCurrHp,int  * eneTotHp,int  * eneActId,int chaBattleId,int chaId,int length,int skillId);//多重攻击
    void moreattactnext();
    void moreAttackName();
    void moreAttackTitle();
    void runBegin(); // 步骤5
    void fangzhao();//播放招数动画 步骤6
    void attacked();//被攻击动画7
    void zhenping(Node * sender); // 受到攻击的时候震动屏幕 步骤8
    void changeBlood();//改变血量 步骤9
    void MeasureEneDead();//判断敌人是否死亡 步骤10
    void removeit(); // 步骤11
    
    void checkOut(); // 战斗结束
    void setBlood(float curB,float nowB,int i,int dir);//设置双方初试血条
    void attack(float changeHP);
   
    Sprite * jiantou;
    Sprite * moveup();
    Sprite * updown;
  
    int e;
    // Sprite *ene1;
    int max;
    int getStar();
    int enemytag;
    const   char *namee;
    Size size;


};

#endif /* defined(__Client__FireWork__) */
