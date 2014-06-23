#ifndef __Client__FireWork__
#define __Client__FireWork__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "skillList.h"
//#include <istream.h>
#include "cocos-ext.h"
#include "next.h"
#include "LodingLayer.h"
#include "CData.h"
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace extension;
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
    CCDictionary * player_dic;
    Sprite * chatbg;
    Label * printLabel;
    double percent1;
    void moreattactnext();
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
    Sprite *explosion;
    virtual bool init();
//    Fire();
    ~Fire();
    void enegrySprite(Sprite * node,int star);
    void removeit();
    int getaudionum();
    void throwtwice();
    void whethertwice();
    void buffbegin(int bufftype);
    void buffend();
    void zhenping(Node * sender);
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
    int direction;
    int  result();//返回战斗结果
    int rounds;//回合数
    int pos;//敌我双方武将所在九宫格位置
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
    rapidjson::Value stepData;
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
    int j;
    int t;
    void setJson(rapidjson::Value json);
    rapidjson::Value getJson();
    void debuff(int eneBid,int enechaid,int changeHp1,int eneCurrHp,int eneTotalHp);
    void repate();
    void runBegin();
    void changeBlood();//改变血量
    void MutileChangeBlood();
    void fangzhao();//播放招数动画
    void setBlood(float curB,float nowB,int i,int dir);//设置双方初试血条
    void enemiesLoad();//敌方武将初始化
    void playerLoad();//我方武将初始化
    void jsonData(char * json);//解析json
    void getJsonData(char * json);
    void actionAttack(int eneBattleId,int eneChaID,int eneChangeHp,int eneCurrentHp,int eneTotalHp,int actionID,int chaBattleID,int chaId,int skillId);//攻击者攻击动画
    void whetherChat(int index);
    void chatPlay();
    void moreActionAttack(int * eneBattId, int * eneChaid,int * eneChanHp,int * eneCurrHp,int  * eneTotHp,int  * eneActId,int chaBattleId,int chaId,int length,int skillId);//多重攻击
    void removeSprite(Node * sender);
    void moreAttacked();
    void moreAttackTitle();//攻击动画
    void SimpleAttack();//循环单一攻击
    void MoreAttack();//循环多重攻击
    void attackData(char *json);
    void attack(float changeHP);
    void checkOut();
    void attacked();//被攻击动画
    void removeAction();
    void moreAttackName();
    void AttackName();
    void doChat();
    void removeChat();
    void nextchat();
    
    Sprite * jiantou;
    void MeasureEneDead();//判断敌人是否死亡
    void MutileMeasureEneDead(Node * sender);
    Sprite * moveup();
    Sprite * updown;
    //    virtual void  registerWithTouchDispatcher();
    //    virtual bool ccTouchBegan(CCSet* touch, CCEvent* event);
    //    virtual void ccTouchMoved(CCSet* touch, CCEvent* event);
    //    virtual void ccTouchEnded(CCSet* touch, CCEvent* event);
    void updatalabel(float dt);
    int e;
    // Sprite *ene1;
    int max;
    int getStar();
    int enemytag;
    const   char *namee;
    Size size;
};

#endif /* defined(__Client__FireWork__) */
