#include "TeXiao.h"

static texiao * tx=NULL;

//bool texiao::init(){
//    if(!Sprite::init()){
//        return  false;
//    }
//    this->texiaoCreate();
//    return true;
//}
texiao::texiao(){
    //加载图片缓存
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("result_attacked.plist");
    
}
texiao::~texiao(){
    
}
texiao * texiao::TX(){
    if (!tx) {
        tx= new texiao();
    }
    return tx;
}
Sprite * texiao::lingqucg(){
    //Vector<SpriteFrame*> lqcg;
    Vector<SpriteFrame*> lqcg;
    
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("lq_lq_01.png");
    Sprite *lq=Sprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=8; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "lq_lq_%02d.png",i);
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(allnames);
        lqcg.pushBack(spf);
        
    }
    
    ActionInterval * Action=RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(lqcg,0.15f)));
    lq->runAction(Action);
    return lq;

}
Sprite * texiao::duoqucg(){
   // Vector<SpriteFrame*> dqsb;
    Vector<SpriteFrame*> dqsb;
    
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("lq_cg_01.png");
    Sprite *dq=Sprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=9; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "lq_cg_%02d.png",i);
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(allnames);

        dqsb.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(dqsb,0.15f)));
    dq->runAction(Action);
    return dq;
}
Sprite * texiao::duoqusb(){
    Vector<SpriteFrame*> dqcg;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("lq_sb_01.png");
    Sprite *dq=Sprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=9; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "lq_sb_%02d.png",i);
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(allnames);
        dqcg.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(dqcg,0.15f)));
    dq->runAction(Action);
    return dq;
}
Sprite * texiao::yanwu(){
    Vector<SpriteFrame*> yanwu;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("ef_01.png");
    Sprite *yw=Sprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=22; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "ef_%02d.png",i);
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(allnames);
        yanwu.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(yanwu,0.083f)));
    yw->runAction(Action);
    return yw;

}
Sprite * texiao::dayan(){
    Vector<SpriteFrame*> daya;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("dy_00016.png");
    Sprite *yw=Sprite::createWithSpriteFrame(pFrame);
    for (int i=16;i<=62; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "dy_%05d.png",i);
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(allnames);
        daya.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(daya,0.0417f)));
    yw->runAction(Action);
    return yw;
}
Sprite * texiao::texiaosCreate(const char *name, int num){
    char names[20]="";
    sprintf(names, "%s_01.png",name);
    Vector<SpriteFrame*> zuixingArr;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName(names);//"zxj_01.png"
    Sprite *zxjsp=Sprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=num; i++)
    {
        
        char allnames[50]="";
        sprintf(allnames, "%s_%02d.png",name,i);
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(allnames);
        //CCString::createWithFormat("zxj_%02d.png",i)->getCString()
        
        zuixingArr.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(zuixingArr,0.125f)));
    zxjsp->runAction(Action);
    return zxjsp;
}
//受伤特效
Sprite * texiao:: texiaoCreate(){

    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("result_00001.png");
    Sprite *tzsp=Sprite::createWithSpriteFrame(pFrame);
    Vector<SpriteFrame*>  kneif;
  
            for (int i=2;i<=8; i++)
            {

                SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("result_%05d.png",i)->getCString());
                
                kneif.pushBack(spf);
                
            }


    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(kneif,0.2f)));
    tzsp->runAction(Action);
    return tzsp;

    
}
Sprite * texiao::beginyanwu(){
    Vector<SpriteFrame*> touzhiArr;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("begin_yw_01.png");
    Sprite *tzsp=Sprite::createWithSpriteFrame(pFrame);
    //tzsp->setPosition(ccp(player->getPosition().x, player->getPosition().y));
    for (int i=2;i<=16; i++)
    {
        
        
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("begin_yw_%02d.png",i)->getCString());
        
        touzhiArr.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(touzhiArr,0.125f)));
    tzsp->runAction(Action);
    return tzsp;
}
//投掷特效
Sprite * texiao:: touzhiCreate(){

    Vector<SpriteFrame*> touzhiArr;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("tz-01.png");
    Sprite *tzsp=Sprite::createWithSpriteFrame(pFrame);
    //tzsp->setPosition(ccp(player->getPosition().x, player->getPosition().y));
    for (int i=2;i<=8; i++)
    {
        
        
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("tz-%02d.png",i)->getCString());
        
        touzhiArr.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(touzhiArr,0.2f)));
    tzsp->runAction(Action);
    return tzsp;
}
//投掷命中特效
Sprite * texiao::mingzhongCreate(){
    Vector<SpriteFrame*> mingzhongArr;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("mz-01.png");
    Sprite *mzsp=Sprite::createWithSpriteFrame(pFrame);
    //tzsp->setPosition(ccp(player->getPosition().x, player->getPosition().y));
    for (int i=2;i<=7; i++)
    {
        
        
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("mz-%02d.png",i)->getCString());
        
        mingzhongArr.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(mingzhongArr,0.2f)));
    mzsp->runAction(Action);
    return mzsp;

}
//普通攻击
Sprite * texiao::normalAttackCreate(){
    Vector<SpriteFrame*> mingzhongArr;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("n_attack_01.png");
    Sprite *mzsp=Sprite::createWithSpriteFrame(pFrame);
    //tzsp->setPosition(ccp(player->getPosition().x, player->getPosition().y));
    for (int i=2;i<=5; i++)
    {
        
        
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("n_attack_%02d.png",i)->getCString());
        
        mingzhongArr.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(mingzhongArr,0.1f)));
    mzsp->runAction(Action);
    return mzsp;

}
//醉醒技
Sprite * texiao::zuixingji(){
    Vector<SpriteFrame*> zuixingArr;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("zxj_01.png");
    Sprite *zxjsp=Sprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=10; i++)
    {
        
        
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("zxj_%02d.png",i)->getCString());
        
        zuixingArr.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(zuixingArr,0.1f)));
    zxjsp->runAction(Action);
    return zxjsp;

}
//太极八卦
Sprite * texiao::taijibagua(){
    Vector<SpriteFrame*> tjbgArr;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("tjbg_01.png");
    Sprite *tjbgsp=Sprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=12; i++)
    {
        
        
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("tjbg_%02d.png",i)->getCString());
        
        tjbgArr.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(tjbgArr,0.1f)));
    tjbgsp->runAction(Action);
    return tjbgsp;
}
//天公怒
Sprite * texiao::tiangongnu(){
    Vector<SpriteFrame*> tgnArr;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("tgn_01.png");
    Sprite *tgnsp=Sprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=9; i++)
    {
        
        
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("tgn_%02d.png",i)->getCString());
        
        tgnArr.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(tgnArr,0.1f)));
    tgnsp->runAction(Action);
    return tgnsp;
}
//遇神诛神
Sprite * texiao::yushenzhushen(){
    Vector<SpriteFrame*> yszsArr;
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName("yszs_01.png");
    Sprite *yszssp=Sprite::createWithSpriteFrame(pFrame);
    for (int i=2;i<=9; i++)
    {
        
        
        SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(CCString::createWithFormat("yszs_%02d.png",i)->getCString());
        
        yszsArr.pushBack(spf);
        
    }
    
    ActionInterval * Action=CCRepeatForever::create(Animate::create(Animation::createWithSpriteFrames(yszsArr,0.1f)));
    yszssp->runAction(Action);
    return yszssp;
}
//Sprite * texiao::huangquezhen(){
//    
//}
//Sprite * texiao::kunshouzhidou(){
//    
//}//困兽之斗
//Sprite * texiao::luandaozhan(){
//    
//}//乱刀斩
//Sprite * texiao::meirenji(){
//    
//}//美人计
//Sprite * texiao::pojunji(){
//    
//}//破军计
//Sprite * texiao::qubingji(){
//    
//}//屈兵计
//Sprite * texiao::shengdongjixi_mz(){
//    
//}//声东击西-命中
//Sprite * texiao::shengdongjixi_tz(){
//    
//}//声东击西-投掷
//Sprite * texiao::shijizhou(){
//    
//}//狮子吼
//Sprite * texiao::shuangfuzhishang_cz(){
//    
//}//双斧之伤-出招
//Sprite * texiao::shuangfuzhishang_mz(){
//    
//}//双斧之伤-命中
//Sprite * texiao::shuangjizhishang_cz(){
//    
//}//双戟之伤-出招
//Sprite * texiao::texiao::shuangjizhishang_mz(){
//    
//}//双戟之伤-命中
//Sprite * texiao::shuanglianzhishang_cz(){
//    
//}//双廉之伤-出招
//Sprite * texiao::shuanglianzhishang_mz(){
//    
//}//双廉之伤-命中
//Sprite * texiao::shuangqiangzhishang_cz(){
//    
//}//双枪之伤-出招
//Sprite * texiao::shuangqiangzhishang_mz()
//{
//    
//}//双枪之伤-命中
//Sprite * texiao::shuangrenzhishang_cz(){
//    
//}//双刃之伤-出招
//Sprite * texiao::shuangrenzhishang_mz(){
//    
//}//双刃之伤-命中
//Sprite * texiao::shuijisanqianli(){
//    
//}//水击三千里
//Sprite * texiao::touxi(){
//    
//}//偷袭
//Sprite * texiao::wanlibingfeng(){
//    
//}//万里冰封
//Sprite * texiao::xiefengzhen(){
//    
//}//邪风阵
//Sprite * texiao::yehuoliaoyuan(){
//    
//}//野火燎原
//移除方法
void texiao::removeSprite(Node *sender){
    this->removeFromParentAndCleanup(true);
}
