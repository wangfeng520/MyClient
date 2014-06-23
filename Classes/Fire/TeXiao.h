#ifndef __client1__TeXiao__
#define __client1__TeXiao__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
class texiao:public cocos2d::Sprite{
public:
    //virtual bool init();
    texiao();
    ~texiao();
   static texiao * TX();
    SpriteBatchNode * touzhi;
    Sprite * texiaosCreate(const char * name,int num);
    Sprite * texiaoCreate();
    Sprite * yanwu();
    Sprite * dayan();
    Sprite * beginyanwu();
    Sprite * touzhiCreate();
    Sprite * lingqucg();
    Sprite * duoqucg();
    Sprite * duoqusb();
    Sprite * mingzhongCreate();
    Sprite * normalAttackCreate();
    Sprite * taijibagua();//太极八卦
    Sprite * tiangongnu();//天公怒
    Sprite * zuixingji();//醉醒技
    Sprite * yushenzhushen();//遇神诛神
    Sprite * huangquezhen();//黄雀阵
    Sprite * kunshouzhidou();//困兽之斗
    Sprite * luandaozhan();//乱刀斩
    Sprite * meirenji();//美人计
    Sprite * pojunji();//破军计
    Sprite * qubingji();//屈兵计
    Sprite * shengdongjixi_mz();//声东击西-命中
    Sprite * shengdongjixi_tz();//声东击西-投掷
    Sprite * shijizhou();//狮子吼
    Sprite * shuangfuzhishang_cz();//双斧之伤-出招
    Sprite * shuangfuzhishang_mz();//双斧之伤-命中
    Sprite * shuangjizhishang_cz();//双戟之伤-出招
    Sprite * shuangjizhishang_mz();//双戟之伤-命中
    Sprite * shuanglianzhishang_cz();//双廉之伤-出招
    Sprite * shuanglianzhishang_mz();//双廉之伤-命中
    Sprite * shuangqiangzhishang_cz();//双枪之伤-出招
    Sprite * shuangqiangzhishang_mz();//双枪之伤-命中
    Sprite * shuangrenzhishang_cz();//双刃之伤-出招
    Sprite * shuangrenzhishang_mz();//双刃之伤-命中
    Sprite * shuijisanqianli();//水击三千里
    Sprite * touxi();//偷袭
    Sprite * wanlibingfeng();//万里冰封
    Sprite * xiefengzhen();//邪风阵
    Sprite * yehuoliaoyuan();//野火燎原
    void removeSprite(Node * sender);
    CREATE_FUNC(texiao);
};
#endif /* defined(__client1__TeXiao__) */
