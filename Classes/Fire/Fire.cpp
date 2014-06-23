#include "Fire.h"

#include "TeXiao.h"
#include "AnimatePacker.h"
#include "Singleton.h"
#include "CustomPop.h"

#define Time 2.5f
static Fire * g_config=NULL;
static int moreene[9]={0};
static int skillnumbers[20]={0};

Fire::~Fire(){
    
    log("Fire destroy!!!!!!!!!!");
    ene_dic->release();
    if (sk) {
        delete sk;
    }
}
Fire* Fire::fire(){
    if (!g_config) {
        
        //log("Audio effect %d",a);
        g_config = new Fire();
    }
    
    return g_config;
    
}

bool Fire::init(){
    if(!Layer::init())
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    TextureCache::getInstance()->removeAllTextures();
    this->setTouchEnabled(true);
    
    size=Director::getInstance()->getWinSize();
    
    Sprite * background=Sprite::create("firework_bkg.png");
    background->setPosition(Point(size.width/2, size.height/2));
    
    this->addChild(background,-2);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bg2.mp3");
    initFireData();
    
    return true;
    
}
void Fire::initFireData(){
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("jn_name.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("begin1.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("result_attacked.plist");
    
    label1=Label::create("", "Marker Felt", 30, Size(200,40), TextHAlignment::LEFT);
    label1->setColor(Color3B(0, 0, 255));
    label1->setPosition(Point(520, 500));
    this->addChild(label1,5);
    label2=Label::create("", "Marker Felt", 30, Size(200,40), TextHAlignment::LEFT);
    label2->setColor(Color3B(0, 0, 255));
    label2->setPosition(Point(520, 460));
    this->addChild(label2,5);
    label3=Label::create("", "Marker Felt", 30, Size(200,40), TextHAlignment::LEFT);
    label3->setColor(Color3B(0, 0, 255));
    label3->setPosition(Point(520, 420));
    this->addChild(label3,5);
    ene_dic=CCDictionary::create();
    ene_dic->retain();
    AnimatePacker :: getInstance()->loadAnimations("qishouTX.xml");
    
    buff1=Sprite::create("tjbgbuff.png");
    buff1->setPosition(Point(320, 260));
    buff1->setVisible(false);
    this->addChild(buff1);
    buff2=Sprite::create("xsjbuff.png");
    buff2->setPosition(Point(320, 260));
    buff2->setVisible(false);
    this->addChild(buff2);
    buff3=Sprite::create("yszsbuff.png");
    buff3->setPosition(Point(320, 260));
    buff3->setVisible(false);
    this->addChild(buff3);
    
    first=false;
    kaishi=0;
    sk=new skillList();
    
    rounds=0;
    
    log("*********___________----------");
    rapidjson::Document d2;
    rapidjson::Value list;
    
    string path = FileUtils::getInstance()->fullPathForFilename("level2data.json");
    string content = FileUtils::getInstance()->getStringFromFile(path.c_str());
    
    d2.Parse<rapidjson::kParseDefaultFlags>(content.c_str());
    
    
    int skill;
    int eee=0;
    data=d2["data"];
    // rapidjson::Value startValue(kArrayType);
    startValue=data["startData"];
    stepData=data["stepData"];
    
    for (int i=0; i<stepData.Size(); i++) {
        log("@");
        skill=stepData[i]["skill"].GetInt();
        if(skill!=610101){
            for(int j=0;j<20;j++){
                if(skillnumbers[j]==skill){
                    break;
                }else{
                    if(skillnumbers[j]==0){
                        skillnumbers[eee]=skill;
                        eee++;
                        break;
                    }
                }
                
            }
        }
    }
    
    for(int i=0;i<20;i++){
        if(skillnumbers[i]!=0){
            const char * texiaoname=sk->skills(skillnumbers[i]);
            char names[40]="";
            sprintf(names, "%s.xml",texiaoname);
            log("%s",names);
            AnimatePacker::getInstance()->loadAnimations(names);
        }
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bg2.mp3", true);
    
    this->getJsonData();
    
}
void Fire::getJsonData(){
    
    log("enter this");
    
    this->jsonData();
    
    
    this->attackData();
}
void Fire::jsonData(){
    log("开始jsonData");
    rapidjson::Value array;
    
    const char * name;
    int battleId;
    int pinzhi;
    int level;
    float chaCurrentHp;
    float chaTotalHp;
    int icon;
    int chaId;
    
    char tag[2];
    int sz =startValue.Size();
    for (int i=0; i<sz; i++) {
        pos=startValue[i][A2U("chaPos")].GetInt();
        battleId=startValue[i][A2U("chaBattleId")].GetInt();
        direction=startValue[i][A2U("chaDirection")].GetInt();
        level=startValue[i][A2U("chaLevel")].GetInt();
        icon=startValue[i][A2U("chaIcon")].GetInt();
        // pinzhi=startValue[i][A2U("difficulty")].GetInt();
        name=startValue[i][A2U("chaName")].GetString();
        chaTotalHp=startValue[i][A2U("chaTotalHp")].GetDouble();
        chaCurrentHp=startValue[i][A2U("chaCurrentHp")].GetDouble();
        chaId=startValue[i][A2U("chaId")].GetInt();
        
        
        this->setBlood(chaCurrentHp, chaTotalHp, pos,direction);
        log("pinzhi:%d",pinzhi);
        sprintf(tag, "%d%d",direction, pos); // 9宫格中得位置
        cout<<name<<endl;
        if(direction==1){  // 下方的布局
            log("%d",pinzhi);
            log("pos%d", (pos) % 3 );
            
            int x1 = size.width / 2  + ((pos - 1) % 3 - 1 ) * 150;
            int y1 = size.height / 2 - ((pos - 1) / 3)  * 120 - 70;
            Sprite *player1 = Sprite::create(); // player1其实就是不同的边框比如对应黄色、白色、黑色卡牌
            switch (pinzhi) {
                case 1:
                    player1->create("common_qs_bkg_1.png");
                    break;
                case 2:
                    player1->create("common_qs_bkg_1.png");
                    break;
                case 3:
                    player1->create("common_qs_bkg_1.png");
                    break;
                case 4:
                    player1->create("common_qs_bkg_1.png");
                    break;
                    
                default:
                    player1->create("common_qs_bkg_1.png");
                    break;
                    
            }
            char iconname[30]="";
            sprintf(iconname, "qs_%04d.png",icon);
            Sprite *player111=Sprite::create(iconname);
            player111->setScale(0.38);
            player111->setAnchorPoint(Point(0, 0));
            player111->setPosition(Point(0, 5));  // (0,5)是相对于player1的中间
            
            player1->setTag(direction*10+pos); // 根据位置设置tag标签
            player1->setPosition(Point(x1, y1));
            player1->addChild(player111);
            this->addChild(player1);
            
            Sprite * xuetiao =Sprite::create("PK_blood.png");
            xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
            xuetiao->setAnchorPoint(Point(0, 1));
            
            xuetiao->setTag(1000+direction*10+pos);
            xuetiao->setPosition(Point(2, 5));
            player1->addChild(xuetiao,2);
            player1->setScale(0.6);
        }
        else if(direction==2){
            
            int x2 = size.width / 2  + ((pos - 1) % 3 - 1 ) * 150;
            int y2 = size.height / 2 + (pos - 1) / 3  * 120 + 70;
            
            Sprite *ene1 = Sprite::create();
            
            switch (pinzhi) {
                case 1:
                    ene1->create("common_qs_bkg_1.png");
                    break;
                case 2:
                    ene1->create("common_qs_bkg_1.png");
                    break;
                case 3:
                    ene1->create("common_qs_bkg_1.png");
                    break;
                case 4:
                    ene1->create("common_qs_bkg_1.png");
                    break;
                    
                default:
                    ene1->create("common_qs_bkg_1.png");
                    break;
                    
            }
            
            ene1->setScale(0.9);
            char iconname[30]="";
            sprintf(iconname, "qs_%04d.png",icon);
            //                    Sprite *  ene111=Sprite::create("qs_0001.png");
            Sprite *  ene111=Sprite::create(iconname);
            ene111->setScale(0.38);
            ene1->setTag(direction*10+pos);
            
            ene1->setPosition(Point(x2, y2));
            ene111->setAnchorPoint(Point(0, 0));
            ene1->addChild(ene111);
            this->addChild(ene1);
            Sprite * xuetiao =Sprite::create("PK_blood.png");
            xuetiao->setAnchorPoint(Point(0, 1));
            xuetiao->setTag(1000+direction*10+pos);
            xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
            xuetiao->setPosition(Point(2, 5));
            ene1->addChild(xuetiao,2);
            ene1->setScale(0.6);
        }
    }
}

void Fire::attackData(){
    
    log("开始执行attackData");
    int chaBattleId;
    int eneBattleId;
    int eneChaId;
    int eneActionId;
    int eneChangeHP;
    int eneCurrentHp;
    int eneTotalHp;
    int chaId;
    int actionId;
    int skillId;
    int chaCurrentPower;
    
    rapidjson::Value eneArr;
    
    //此处解析攻击json数据
    battleresult=data["battleResult"].GetInt();
    CData::getCData()->setFireResult(battleresult);
    chaBattleId=stepData[rounds]["chaBattleId"].GetInt();
    // dir=stepData[rounds][A2U("chaDirection")].GetInt();
    eneArr=stepData[rounds][A2U("enemyChaArr")];
    chaId=stepData[rounds][A2U("chaId")].GetInt();
    actionId=stepData[rounds][A2U("actionId")].GetInt();
    skillId=stepData[rounds][A2U("skill")].GetInt();
    if(stepData[rounds].HasMember("chaCurrentPower")) {
        chaCurrentPower= stepData[rounds]["chaCurrentPower"].GetInt();
        
    }
    _chaCurrentPower=chaCurrentPower;
    if(eneArr.Size()==1)
    {
        eneBattleId=eneArr[rounds]["enemyBattleId"].GetInt();
        eneChaId=eneArr[rounds]["enemyChaId"].GetInt();
        eneActionId=eneArr[rounds]["enemyActionId"].GetInt();
        eneChangeHP=eneArr[rounds]["enemyChangeHp"].GetInt();
        eneCurrentHp=eneArr[rounds]["enemyCurrentHp"].GetInt();
        if(eneArr[rounds].HasMember("enemyTotalHp")) {
            eneTotalHp=eneArr[rounds]["enemyTotalHp"].GetInt();
        }
        if(eneArr[rounds].HasMember("enemyCurrentPower")) {
            _eneCurrentPower=eneArr[rounds]["enemyCurrentPower"].GetInt();
        }
        
        // if(chaBattleId==-1){
        ///     this->debuff(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp);
        // }else{
        this->actionAttack(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp, actionId, chaBattleId,chaId,skillId);
        // }
    }
    else if(eneArr.Size()>1){
        int eneChaid[eneArr.Size()];
        int eneChanHp[eneArr.Size()];
        int eneCurrHp[eneArr.Size()];
        int eneTotHp[eneArr.Size()];
        int eneBattId[eneArr.Size()];
        int eneActId[eneArr.Size()];
        for(int i=0;i<eneArr.Size();i++){
            eneBattleId=eneArr[i]["enemyBattleId"].GetInt();
            
            eneChaId=eneArr[i]["enemyChaId"].GetInt();
            
            eneActionId=eneArr[i]["enemyActionId"].GetInt();
            
            eneChangeHP=eneArr[i]["enemyChangeHp"].GetInt();
            
            eneCurrentHp=eneArr[i]["enemyCurrentHp"].GetInt();
            
            eneTotalHp=eneArr[i]["enemyTotalHp"].GetInt();
            eneChaid[i]=eneChaId;
            eneChanHp[i]=eneChangeHP;
            eneCurrHp[i]=eneCurrentHp;
            eneTotHp[i]=eneTotalHp;
            eneActId[i]=eneActionId;
            eneBattId[i]=eneBattleId;
            
        }
        
        this->moreActionAttack(eneBattId, eneChaid, eneChanHp, eneCurrHp, eneTotHp, eneActId, chaBattleId, chaId,eneArr.Size(),skillId);
        
    }
     rounds++;
}
void Fire::actionAttack(int eneBattleId,int eneChaID,int eneChangeHp,int eneCurrentHp,int eneTotalHp,int actionID,int chaBattleID,int chaId,int skillId){
    log("actionAttack开始执行eneBattleId:%d",eneBattleId);
    enemy=(Sprite *)this->getChildByTag(eneBattleId);
    player=(Sprite *)this->getChildByTag(chaBattleID);
    chaIdd=chaBattleID;
    if (kaishi==0){
        
        Vector<SpriteFrame *> kneif;
        
        SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("01.png");  // “战斗开始”的特效
        explosion = Sprite::createWithSpriteFrame(pFrame);
        explosion->setPosition(Point(size.width/2, size.height/2));
        this->addChild(explosion);
        for (int i=2;i<=10; i++)
        {
            SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("%02d.png",i)->getCString());
            kneif.pushBack(spf);
        }
        
        ActionInterval * delay=DelayTime::create(3.6/Time);
        Animation * Action=Animation::createWithSpriteFrames(kneif, 0.18f/Time);
        CallFunc * fun2=CallFunc::create(CC_CALLBACK_0(Fire::runBegin, this));
        ActionInterval* act = CCAnimate::create(Action);
        FiniteTimeAction *playerAct=Sequence::create(delay,act,fun2,NULL);
        explosion->runAction(playerAct);
        
        _skillId=skillId;
        changeHp=eneChangeHp;
        currHp=eneCurrentHp;
        eneBID=eneBattleId;
        totalHp=eneTotalHp;
        _actionId=actionID;
        
    }
    //此处执行攻击者动画
    else if(kaishi==1){
        this->runBegin();
        _skillId=skillId;
        changeHp=eneChangeHp;
        currHp=eneCurrentHp;
        eneBID=eneBattleId;
        totalHp=eneTotalHp;
        _actionId=actionID;
    }
}
void Fire::runBegin(){
    log("runBegin 开始执行chaBattleId :%d",chaIdd);
    if(kaishi==0){
        kaishi=1;
        explosion->removeFromParentAndCleanup(true);
    }
    
    cout<<chaIdd/10<<endl;
    if(chaIdd/10==1){ // 表示在下方九宫格
        const char * texiaoname=sk->skills(_skillId);
        if(!strcmp(texiaoname, "sq")||!strcmp(texiaoname, "sl")||!strcmp(texiaoname, "sj")||!strcmp(texiaoname, "sf")||!strcmp(texiaoname, "sr")||!strcmp(texiaoname, "sdjx")||!strcmp(texiaoname, "mrj")||!strcmp(texiaoname, "wlbf")){
            
        }
        else{
           
        }
        
        ActionInterval * moveon=MoveTo::create(0.12/Time, Point(player->getPosition().x, player->getPosition().y+20));
        ActionInterval * movedown=MoveTo::create(0.12/Time, Point(player->getPosition().x, player->getPosition().y));
        
        CallFunc * fun4=CallFunc::create(CC_CALLBACK_0(Fire::fangzhao, this));
        FiniteTimeAction *playerAct1=Sequence::create(moveon,movedown,fun4,NULL);
        log("玩家攻击player tag ===%d",player->getTag());
        player->runAction(playerAct1);
    }
    else if(chaIdd/10==2){ // 上方,也可以理解为被攻击
        
        ActionInterval * moveon=MoveTo::create(0.12/Time, Point(player->getPosition().x, player->getPosition().y-20));
        ActionInterval * movedown=MoveTo::create(0.12/Time, Point(player->getPosition().x, player->getPosition().y));
        
        CallFunc * fun4=CallFunc::create(CC_CALLBACK_0(Fire::fangzhao, this));
        FiniteTimeAction *playerAct1=Sequence::create(moveon,movedown,fun4,NULL);
        log("玩家被攻击player tag ===%d",player->getTag());
        player->runAction(playerAct1);
    }
    
}
void Fire::fangzhao(){
   log("fangzhao 开始执行_actionId :%d",_actionId);
    //此处执行招数动画
    if(_actionId==98){
        
        log("暂时屏蔽");
    }else if(_actionId==99){
        normalAttack = Sprite::create("attack_img.png");
        normalAttack->setTag(0012);
       
        if(chaIdd/10==1){
            //normalAttack->setRotation(90);
        }
        else if(chaIdd/10==2){
            normalAttack->setRotation(180); // 特效按锚点旋转180度相当于视觉上反过来
        }
        
        float y1;
        float y2;
        float x1;
        float x2;
        float angel;
        x1=player->getPosition().x;
        x2=enemy->getPosition().x;
        y1=player->getPosition().y;
        y2=enemy->getPosition().y;
        normalAttack->setPosition(Point(x1, y1+30));
        //normalAttack->setScale(2.0);
        this->addChild(normalAttack,5);
        
        angel=(y1-y2)/(x1-x2);
        angel=atanf(angel)/M_PI*180;  // 用来调整特效的旋转保证放招是攻击方对着被攻击方效果
        //CData::getCData()->setFiremusic();
        srandom(time(NULL));
        int s2=0;
        s2=rand()%3;  // 随机播放音效
        switch(s2)
        {
            case 0:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("battleAttack1.mp3");
                break;
            case 1:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("battleAttack2.mp3");
                break;
            case 2:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("battleAttack3.mp3");
                break;
            default:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("battleAttack1.mp3");
                break;
        }
        ActionInterval * moveto=MoveTo::create(0.4/Time, Point(player->getPosition().x, player->getPosition().y+30));//改动 Point(enemy->getPosition().x, enemy->getPosition().y)
        CallFunc * fun2=CallFunc::create(CC_CALLBACK_0(Fire::attacked, this));
        //CallFunc * fun3=CallFunc::create(this, callfunc_selector(Fire::removeSprite));
        FiniteTimeAction *playerAct=Sequence::create(moveto,fun2,NULL);
        normalAttack->runAction(playerAct);
    }
}
void Fire::attacked(){
    log("attacked 开始执行_actionId :%d",_actionId);
    this->removeChildByTag(8032,true);
    //label->stopAllActions();
    this->removeChildByTag(999,true);
    if(_actionId==99){
        log("_chaCurrentPower %d",_chaCurrentPower);
        normalAttack->stopAllActions();
        this->removeChildByTag(0012,true);  // 移除攻击特效~
        tx=Sprite::create("attacked_img.png");
        tx->setTag(9099);
        tx->setPosition(Point(70, 75));
        
        char cHp[10]={0};
        sprintf(cHp, "%d",changeHp);
        reduB=CCLabelAtlas::create(cHp, "number.png", 30, 50, '-');  // 显示掉了多少血
        reduB->setColor(Color3B(255, 0, 0));
        reduB->setAnchorPoint(Point(0.5, 0));
        reduB->setPosition(Point(enemy->getContentSize().width/2, enemy->getContentSize().height/2));
        
        enemy->addChild(reduB);
        
        enemy->addChild(tx);
        ActionInterval *a_jianxue=MoveTo::create(0.45/Time, Point(reduB->getPosition().x, reduB->getPosition().y+80));
        
        ActionInterval * set_big=ScaleTo::create(0.4/Time, 1.5);
        
        FadeOut *a_jiaxue_fadeout=FadeOut::create(0.5f/Time);
        
        CallFunc * reduceBlood=CallFunc::create(CC_CALLBACK_0(Fire::changeBlood, this));//changeBlood
        FiniteTimeAction *jianxueaction=Sequence::create(set_big,a_jianxue,a_jiaxue_fadeout,reduceBlood,NULL);
        reduB->runAction(jianxueaction);
        
        zhenping(enemy);
    }
    else if(_actionId==98)
    {
        
        this->removeChildByTag(8078,true);
        const char * texiaoname=sk->skills(_skillId);
        //        char txname[50]="";
        //        sprintf(txname, "%s.xml",texiaoname);
        //AnimatePacker :: getInstance()->loadAnimations(txname);
        char combine[50]="";
        // AnimatePacker :: getInstance()->loadAnimations(txname);
        sprintf(combine, "%s_01.png",texiaoname);
        mz=Sprite::createWithSpriteFrameName(combine);
        //texiao->setPosition(Point(320, 480));
        mz->runAction(AnimatePacker::getInstance()->getAnimate(texiaoname));
        //int idnum=sk->skillnums(_skillId);
        
        
        // mz=texiao::TX()->texiaosCreate(texiaoname, idnum);
        mz->setTag(9098);
        
        //mz=texiao::TX()->mingzhongCreate();
        mz->setPosition(Point(50, 50));
        char cHp[10]={0};
        sprintf(cHp, "%d",changeHp);
        //label->removeFromParentAndCleanup(true);
        // reduB1=Label::create(cHp,"Marker Felt", 30);
        reduB1=CCLabelAtlas::create(cHp, "number.png", 30, 50, '-');
        reduB1->setColor(Color3B(255, 0, 0));
        reduB1->setAnchorPoint(Point(0.5, 0));
        reduB1->setPosition(Point(enemy->getContentSize().width/2, enemy->getContentSize().height/2));
        enemy->addChild(reduB1);
        enemy->addChild(mz);
        
        ActionInterval * delay=DelayTime::create(1);        //ActionInterval *a_jianxue=MoveTo::create(0.45, Point(reduB1->getPosition().x, reduB1->getPosition().y+80));
        CallFunc * reduceBlood=CallFunc::create(CC_CALLBACK_0(Fire::changeBlood, this));
        FiniteTimeAction * final=Sequence::create(delay,reduceBlood,NULL);
        mz->runAction(final);
        //ActionInterval * set_small=CCScaleTo::create(0, 0);
        ActionInterval * set_big=CCScaleTo::create(0.2/Time, 1.5);
        ActionInterval * set_nor=CCScaleTo::create(0.2/Time, 1);
        
        FadeOut *a_jiaxue_fadeout=FadeOut::create(0.5f/Time);
        //  CallFunc * func=CallFunc::create(this, callfunc_selector(Fire::MeasureEneDead));
        
        
        //changeBlood
        FiniteTimeAction *jianxueaction=Sequence::create(set_big,set_nor,a_jiaxue_fadeout,NULL);
        reduB1->runAction(jianxueaction);
        zhenping(enemy);
        //        CCShaky3D *shake=CCShaky3D::create(0.3/Time, Size(2, 2), 5, false);
        //        enemy->runAction(shake);
        
    }
}
void Fire::zhenping(Node * sender){
    log("zhenping");
    Point size = sender->getPosition();
    ActionInterval * left1 = MoveTo::create(0.03,Point(sender->getPosition().x+5,sender->getPosition().y));
    ActionInterval * right1 = MoveTo::create(0.03,Point(sender->getPosition().x-5,sender->getPosition().y));
    ActionInterval * top1 = MoveTo::create(0.03,Point(sender->getPosition().x,sender->getPosition().y+5));
    ActionInterval * rom1 = MoveTo::create(0.03,size);
    FiniteTimeAction* action3 = Sequence::create(left1,right1,top1,rom1,NULL);
    sender->runAction(action3);
}
void Fire::changeBlood(){
    log("changeBlood开始:cur %d, change %d",currHp,changeHp);
   
    if (_actionId==98) {
        enemy->removeChildByTag(9098,true);
        reduB1->removeFromParentAndCleanup(true);
    }else if(_actionId==99){
        enemy->removeChildByTag(9099,true);
        reduB->removeFromParentAndCleanup(true);
    }
    Sprite * blood=(Sprite *)enemy->getChildByTag(1000+eneBID);
    double percent;
   
    if(currHp+changeHp<=0){
        ActionInterval *  scal=ScaleTo::create(0.75/Time, 0, 1);
        CallFunc * func=CallFunc::create(CC_CALLBACK_0(Fire::MeasureEneDead, this));
        // ActionInterval * delay=CCDelayTime::create(0.2);
        FiniteTimeAction *Action=Sequence::create(scal,func,NULL);
        blood->runAction(Action);
        
    }else if(currHp+changeHp>0){
        
        percent=((double)(currHp+changeHp)/(double)totalHp);
        
        log("%f",percent);
        // cout<<currHp/totalHp<<endl;
        //currHp=currHp+changeHp;
        ActionInterval *  scal=ScaleTo::create(0.75/Time, percent, 1);
        // ActionInterval * delay=CCDelayTime::create(0.2);
        CallFunc * func=CallFunc::create(CC_CALLBACK_0(Fire::MeasureEneDead, this));
        FiniteTimeAction *Action=Sequence::create(scal,func,NULL);
        blood->runAction(Action);
    }
    
}
void Fire::MeasureEneDead(){
    log("开始执行MeasureEneDead_actionId : %d", _actionId);
    
    if (_actionId==98) {
        enemy->removeChildByTag(9098,true);
    }else if(_actionId==99){
        enemy->removeChildByTag(9099,true);
    }
    if(changeHp+currHp<=0){
        ActionInterval * fadeout=FadeOut::create(0.2);  //FadeOut 作用：创建一个渐变消失的动作 参数是时间
        CallFunc * func=CallFunc::create(CC_CALLBACK_0(Fire::removeit, this));
        FiniteTimeAction * final=Sequence::create(fadeout,func,NULL);
        enemy->runAction(final);
    }
    else{
        this->checkOut();
    }
}
void Fire::removeit(){
    Sprite * xuetiao=(Sprite *)this->getChildByTag(1000+eneBID);
    enemy->removeFromParentAndCleanup(true);
    this->removeChild(xuetiao,true);
    this->checkOut();
}
void Fire::checkOut(){
    log("开始checkOut,rounds:%d", rounds);
    chaBattleId=0;
    int eneBattleId;
    int eneChaId;
    int eneActionId;
    int eneChangeHP;
    int eneCurrentHp;
    int eneTotalHp;
    int chaId;
    int actionID;
    int skillId;
    int chaCurrentPower;
    
    rapidjson::Value eneArr;
    rapidjson::Value buff;
    if (stepData[rounds].IsObject()){
        
        if(stepData[rounds].HasMember("chaBattleId")) {
            chaBattleId=stepData[rounds][A2U("chaBattleId")].GetInt();
        }
        
        if(chaBattleId!=0){
            eneArr=stepData[rounds]["enemyChaArr"];
            chaId=stepData[rounds]["chaId"].GetInt();
            actionID=stepData[rounds]["actionId"].GetInt();
            skillId=stepData[rounds]["skill"].GetInt();
            
            if(stepData[rounds].HasMember("chaCurrentPower")) {
                chaCurrentPower=stepData[rounds]["chaCurrentPower"].GetInt();
            }
            if(eneArr.IsArray() && eneArr.Size()==1)
            {
                int round=0;
                if(eneChaId-10<10){
                    fireinfo * fire=new fireinfo();
                    fire->personId=eneChaId-10;
                    
                    buff=eneArr[round]["enemyBuffArr"];
                    for (int i=0; i<buff.Size(); i++) {
                        fire->buff[i]=buff[i].GetInt();
                    }
                    player_map.insert(fire->personId, fire);
                }
                eneBattleId=eneArr[round]["enemyBattleId"].GetInt();
                
                eneChaId=eneArr[round]["enemyChaId"].GetInt();
                
                eneActionId=eneArr[round]["enemyActionId"].GetInt();
                
                eneChangeHP=eneArr[round]["enemyChangeHp"].GetInt();
                
                eneCurrentHp=eneArr[round]["enemyCurrentHp"].GetInt();
                
                eneTotalHp=eneArr[round]["enemyTotalHp"].GetInt();
                //                            if(chaBattleId==-1){
                //                                this->debuff(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp);
                //                            }else{
                this->actionAttack(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp, actionID, chaBattleId,chaId,skillId);
                //            }
                
            }
            else if(eneArr.Size()>1){
                int eneChaid[eneArr.Size()];
                int eneChanHp[eneArr.Size()];
                int eneCurrHp[eneArr.Size()];
                int eneTotHp[eneArr.Size()];
                int eneBattId[eneArr.Size()];
                int eneActId[eneArr.Size()];
                for(int i=0;i<eneArr.Size();i++){
                    if(eneChaId-10<10){
                        fireinfo * fire=   new fireinfo();
                        fire->personId=eneChaId-10;
                        
                        buff=eneArr[i]["enemyBuffArr"];
                        for (int i=0; i<buff.Size(); i++) {
                            fire->buff[i]=buff[i].GetInt();
                        }
                        if(buff.Size()==0){
                            * fire->buff=0;
                            player_map.insert(fire->personId, fire);
                        }else{
                            player_map.insert(fire->personId, fire);
                        }
                        //delete fire;
                    }
                    eneBattleId=eneArr[i]["enemyBattleId"].GetInt();
                    
                    eneChaId=eneArr[i]["enemyChaId"].GetInt();
                    
                    eneActionId=eneArr[i]["enemyActionId"].GetInt();
                    
                    eneChangeHP=eneArr[i]["enemyChangeHp"].GetInt();
                    
                    eneCurrentHp=eneArr[i]["enemyCurrentHp"].GetInt();
                    
                    eneTotalHp=eneArr[i]["enemyTotalHp"].GetInt();
                    eneChaid[i]=eneChaId;
                    eneChanHp[i]=eneChangeHP;
                    eneCurrHp[i]=eneCurrentHp;
                    eneTotHp[i]=eneTotalHp;
                    eneActId[i]=eneActionId;
                    eneBattId[i]=eneBattleId;
                }
                // this->moreActionAttack(eneBattId, eneChaid, eneChanHp, eneCurrHp, eneTotHp, eneActId, chaBattleId, chaId,eneArr.Size(),skillId);
            }
            int e1=0;
            int e2=0;
            int e3=0;
            for (int i=0; i<9; i++) {
                fireinfo *fire=(fireinfo *) player_map.at(i);
                if(fire){
                    for(int j=0;j<5;j++){
                        if(fire->buff[j]==100005){
                            e1++;
                        }else if(fire->buff[j]==100003){
                            e2++;
                        }else if(fire->buff[j]==100001){
                            e3++;
                        }
                    }
                }
            }
            if(e1==0){
                buff1->setVisible(false);
            }else if(e2==0)
            {
                buff2->setVisible(false);
            }else if(e3==0){
                buff3->setVisible(false);
            }
            
           rounds++;
        }
        else{
           
            CustomPop::show("战斗结束！");
            
        }
        //此处将获取的json数据传递给消息触发器
        
    }
}








void Fire::moreActionAttack(int *eneBattId, int *eneChaid, int * eneChanHp, int * eneCurrHp, int * eneTotHp, int * eneActId, int chaBattleId, int chaId,int length,int skillId){
    max=1;
    for(int i=0;i<length;i++){
        _eneBattId[i]=eneBattId[i];
        _eneChaid[i]=eneChaid[i];
        _eneChanHp[i]=eneChanHp[i];
        _eneCurrHp[i]=eneCurrHp[i];
        _eneTotHp[i]=eneTotHp[i];
        _eneActId[i]=eneActId[i];
        
    }
    _skillId=skillId;
    _chaBattleId=chaBattleId;
    _chaId=chaId;
    _length=length;
    if (kaishi==0){
        kaishi=1;
        
        //    knif=CCSpriteBatchNode::create("begin.png");
        //    this->addChild(knif);
        
        Vector<SpriteFrame*> kneif = Vector<SpriteFrame*>();
        //  CCArray * kneif=CCArray::create();
        
        SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("01.png");
        Sprite *explosion = Sprite::createWithSpriteFrame(pFrame);
        explosion->setTag(1111);
        explosion->setPosition(Point(size.width/2, size.height/2));
        this->addChild(explosion);
        for(int i=2;i<=10; i++)
        {
            SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("%02d.png",i)->getCString());
            
            kneif.pushBack(spf);
        }
        
        ActionInterval * delay=DelayTime::create(1);
        Animation * Action=Animation::createWithSpriteFrames(kneif, 0.1f);//createWithSpriteFrames(kneif, 0.1f);
        CallFunc * fun2=CallFunc::create(CC_CALLBACK_0(Fire::moreattactnext,this));
        FiniteTimeAction *playerAct=Sequence::create(delay,CCAnimate::create(Action),fun2,NULL);
        explosion->runAction(playerAct);
    }
    else {
        this->moreattactnext();
    }
}
void Fire::moreattactnext(){
    player=(Sprite *)this->getChildByTag(_chaBattleId);
    FadeOut *playfadeout=FadeOut::create(0.18f);//0.18f
    FadeIn *playerfadein=FadeIn::create(0.3f);//0.3f
    CallFunc * fun2=CallFunc::create(CC_CALLBACK_0(Fire::moreAttackName,this));
    FiniteTimeAction *playerAct=Sequence::create(playfadeout,playerfadein,fun2,NULL);
    player->runAction(playerAct);
    
}
void Fire::moreAttackName(){
    this->removeChildByTag(1111);
    const char * skillname=sk->skillname(_skillId);
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName(skillname);
    label=CCSprite::createWithSpriteFrame(pFrame);
    
    label->setPosition(Point(size.width/2, size.height/2));
    label->setTag(999);
    this->addChild(label);
    ActionInterval *action=CCMoveTo::create(0.88, Point(size.width/2, size.height/2));
    FadeOut *fadeout=FadeOut::create(0.12f);
    CallFunc * func1=CallFunc::create(this, callfunc_selector(Fire::moreAttackTitle));
    //CCCallFunc * fun3=CCCallFunc::create(this, callfunc_selector(Fire::removeSprite));
    FiniteTimeAction *allaction=Sequence::create(action,fadeout,func1,NULL);
    label->runAction(allaction);
    
}
void Fire::moreAttackTitle(){
    this->removeChildByTag(999,true);
    skill *sk=this->returnskills(_skillId);
    skillList * skk=new skillList();
    if(eneBID-10<10){
        if(_skillId==100002){
            buffbegin(1);
            label3->setColor(Color3B(0, 255, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("我方防御增加");
            label3->setPosition(Point(520, 420));
            FadeIn * fadein=FadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            MoveTo *  moveon=MoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
            
        }else if(_skillId==100005){
            buffbegin(2);
            label3->setColor(Color3B(0, 255, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("我方攻击增加");
            label3->setPosition(Point(520, 420));
            FadeIn * fadein=FadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            MoveTo *  moveon=MoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
            
        }
        else if(_skillId==100001){
            buffbegin(3);
            label3->setColor(Color3B(0, 255, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("我方暴击增加");
            label3->setPosition(Point(520, 420));
            FadeIn * fadein=FadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            MoveTo *  moveon=MoveTo::create(1, ccp(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }
    }else{
        if(_skillId==100002){
            label3->setColor(Color3B(255, 0, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("敌方防御增加");
            label3->setPosition(Point(520, 420));
            FadeIn * fadein=FadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            MoveTo *  moveon=MoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }else if(_skillId==100005){
            buffbegin(2);
            label3->setColor(Color3B(255, 0, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("敌方攻击增加");
            label3->setPosition(Point(520, 420));
            FadeIn * fadein=FadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            MoveTo *  moveon=MoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }
        else if(_skillId==100001){
            buffbegin(3);
            label3->setColor(Color3B(255, 0, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("敌方暴击增加");
            label3->setPosition(Point(520, 420));
            FadeIn * fadein=FadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            MoveTo *  moveon=MoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }
    }
}
void Fire::buffbegin(int bufftype){
    
    ActionInterval * buffrote1=RotateBy::create(10, 360);
    ActionInterval * buffrote2=RotateBy::create(15, 360);
    ActionInterval * fadein1=FadeIn::create(1);
    ActionInterval * fadeout1=FadeOut::create(1);
    FiniteTimeAction * final=Sequence::create(fadein1,fadeout1,NULL);
    ActionInterval * fadein2=FadeIn::create(1.5);
    ActionInterval * fadeout2=FadeOut::create(1.5);
    FiniteTimeAction * final2=Sequence::create(fadein2,fadeout2,NULL);
    ActionInterval * fadein3=FadeIn::create(1.2);
    ActionInterval * fadeout3=FadeOut::create(1.2);
    FiniteTimeAction * final3=Sequence::create(fadein3,fadeout3,NULL);
    switch (bufftype) {
        case 1:
            buff1->setVisible(true);
            buff1->runAction(CCRepeatForever::create(buffrote1));
            buff1->runAction(CCRepeatForever::create((ActionInterval *)final));
            break;
        case 2:
            buff2->setVisible(true);
            buff2->runAction(CCRepeatForever::create(buffrote2));
            buff2->runAction(CCRepeatForever::create((ActionInterval *)final3));
            break;
        case 3:
            buff3->setVisible(true);
            buff3->runAction(CCRepeatForever::create((ActionInterval *)final2));
            break;
        default:
            break;
    }
    
}
void Fire::buffend(){
    
}
void Fire::throwtwice(){
    enemy=(Sprite *)this->getChildByTag(eneBID);
    player=(Sprite *)this->getChildByTag(chaIdd);
    log("%d",player->getTag());
    log("%d",enemy->getTag());
    log("%f",player->getPosition().x);
    log("%f",player->getPosition().y);
    log("%f",enemy->getPosition().x);
    log("%f",enemy->getPosition().y);
    //    const char * skillname=sk->throwTX(_skillId);
    const char * texiaoname=sk->skills(_skillId);
    ParticleSystemQuad * stars;
    if(!strcmp(texiaoname, "tx")){
        stars=CCParticleSystemQuad::create("touxi_1.plist");
        // stars->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire_1.png"));
        // stars->setBlendAdditive(false);
        stars->setPosition(player->getPosition());
        stars->setTag(8032);
        this->addChild(stars);
        ActionInterval * delay=DelayTime::create(0.1);
        ActionInterval * moveto=MoveTo::create(0.5/Time, enemy->getPosition());
        
        CallFunc * func=CallFunc::create(CC_CALLBACK_0(Fire::attacked, this));
        FiniteTimeAction * final=Sequence::create(delay,moveto,func,NULL);
        stars->runAction(final);
    }else{
        char txname[50]="";
        sprintf(txname, "%s.xml",texiaoname);
        
        char combine[50]="";
        
        sprintf(combine, "%s_01_01.png",texiaoname);
        tz=Sprite::createWithSpriteFrameName(combine);
        
        char animate[50]="";
        sprintf(animate, "%s_tz",texiaoname);
        tz->runAction(CCRepeatForever::create( AnimatePacker::getInstance()->getAnimate(animate)));
        float y1;
        float y2;
        float x1;
        float x2;
        float angel;
        x1=player->getPosition().x;
        x2=enemy->getPosition().x;
        y1=player->getPosition().y;
        y2=enemy->getPosition().y;
        
        angel=(y1-y2)/(x1-x2);
        angel=atanf(angel)/M_PI*180;
        
        tz->setPosition(Point(x1, y1+50));
        if(angel<0){
            tz->setRotation(90-angel);
            
        }else{
            tz->setRotation(90-angel);
        }
        tz->setTag(8078);
        this->addChild(tz,2);
        
        
        ActionInterval * delay=DelayTime::create(0.1);
        ActionInterval * moveto=MoveTo::create(0.5/Time, enemy->getPosition());
        
        CallFunc * func=CallFunc::create(CC_CALLBACK_0(Fire::attacked, this));
        FiniteTimeAction * final=Sequence::create(delay,moveto,func,NULL);
        tz->runAction(final);
        
    }
    
}
void Fire::setBlood(float curB, float nowB, int i,int dir){
    //此处初始化敌方武将血条
}
/*
 void  Fire::setJson(rapidjson::Value json){
 _json=json;
 int coin;
 
 coin=json["star"].GetInt();
 log("%d %d",coin,_json["star"].GetInt());
 }
 rapidjson::Value  Fire::getJson(){
 int star=_json["star"].GetInt();
 log("%d",star);
 return _json;
 }
 */
int Fire::getStar(){
    return NULL;
}
int Fire::result(){
    return battleresult;
}
Sprite * Fire::moveup(){
    updown=Sprite::create("smalljiantou.png");
    ActionInterval * up=MoveBy::create(0.5/Time, Point(updown->getPosition().x, updown->getPosition().y+20));
    ActionInterval * down=MoveBy::create(0.5/Time, Point(updown->getPosition().x, updown->getPosition().y-20));
    FiniteTimeAction * final=Sequence::create(up,down,NULL);
    RepeatForever * rep=RepeatForever::create((ActionInterval *)final);
    updown->runAction(rep);
    return updown;
}
skill * Fire::returnskills(int skillId){
    
    rapidjson::Reader read;
    rapidjson::Value root;
    rapidjson::Value data;
    rapidjson::Value row;
    char skillss[40]="";
    sprintf(skillss, "%d",skillId);
    skill * skills=new skill();
    skills->autorelease();
    rapidjson::Document d2;
    
    //    string path = FileUtils::getInstance()->fullPathForFilename("skill.json");
    //    String* str = String::createWithContentsOfFile(path.c_str());
    
    std::string path=FileUtils::getInstance()->getStringFromFile("hero.json");
    d2.Parse<rapidjson::kParseDefaultFlags>(path.c_str());
    
    //    if(read.parse(str->getCString(), root)){
    data=d2[skillss];
    
    
    skills->releaseEffect=data["releaseEffect"].GetInt();
    skills->throwEffectId=data["throwEffectId"].GetInt();
    skills->bearEffect=data["bearEffect"].GetInt();
    //    }
    //    ifs.close();
    return skills;
}
Fire *Fire::getInstance(){
    Fire *fireInstance=new Fire();
    return fireInstance;
}
int Fire::getaudionum(){
    return audionum;
}

void Fire::enegrySprite(Sprite * node,int star){
    //    switch (star) {
    //        case 1:
    //            statements
    //            break;
    //
    //        default:
    //            break;
    //    }
}
Scene * Fire::scene(){
    Scene *scene=CCScene::create();
    Fire *fire=Fire::create();
    fire->setTag(902);
    scene->addChild(fire);
    return scene;
}

void Fire::onExit(){
    AnimatePacker :: getInstance()->freeAnimations ("qishouTX.xml");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName ("result_attacked.plist");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName ("jn_name.plist");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName ("begin1.plist");
    
    Layer::onExit();
    player_map.clear();
    
}
void Fire::recv_4501(){
    
    
}





