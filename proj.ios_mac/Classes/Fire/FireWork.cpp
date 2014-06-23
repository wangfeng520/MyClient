#include "FireWork.h"

#include "TeXiao.h"
//#include "GameOver.h"
#include "AnimatePacker.h"
#include "Singleton.h"
//#include "SocketManager.h"
#include "CustomPop.h"

#define Time 2.5f
static Fire * g_config=NULL;
static int moreene[9]={0};
static int skillnumbers[20]={0};


bool Fire::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    TextureCache::getInstance()->removeAllTextures();
    
    size=Director::getInstance()->getWinSize();
    
    Sprite * background=Sprite::create("firework_bkg.png");
    background->setPosition(Point(size.width/2, size.height/2));
    
    this->addChild(background,-2);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bg2.mp3");
    initFireData();
    
    return true;
    
}


void Fire::initFireData()
{   
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
    player_dic=CCDictionary::create();
    player_dic->retain();
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
    this->setTouchEnabled(true);
    first=false;
    kaishi=0;
    sk=new skillList();
    
    rounds=0;
    
    log("*********___________----------");
    
    char * data2=CData::getCData()->getdata();
    rapidjson::Document d2;
    rapidjson::Value stepdata;
    rapidjson::Value list;
   //    Json::Value root;
//    Json::Value data;
//    Json::Value stepdata;
    
    
    d2.Parse<rapidjson::kParseDefaultFlags>(data2);
    
    int skill;
    int eee=0;
    rapidjson::Value &data=d2["data"];
    
        stepdata=data["stepData"];
        for (int i=0; i<stepdata.Size(); i++) {
            log("@");
            skill=stepdata[i]["skill"].GetInt();
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
    
    bool flaag=false;

    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bg2.mp3", true);
    
    this->getJsonData(data2);
    
    }

Fire *Fire::getInstance()
{
    Fire *fireInstance=new Fire();
    return fireInstance;
}
int Fire::getaudionum(){
    return audionum;
}
void Fire::whetherChat(int index){
    
    nextLayer * nex=nextLayer::create();
    nex->setTag(004);
    this->addChild(nex);
    printLabel=Label::create("", "Marker Felt", 24, Size(0, 50), TextHAlignment::LEFT);
    printLabel->setAnchorPoint(Point(0, 1));
    printLabel->setPosition(Point(10, 50));
    this->addChild(printLabel,5);

    rapidjson::Document d2;
    rapidjson::Value shuju;
    rapidjson::Value root;

    string path = FileUtils::getInstance()->fullPathForFilename("dialogue1.json");
    string str = FileUtils::getInstance()->getStringFromFile(path.c_str());

    d2.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
   
    int ic=5;
    const char * na;
    int ic1=0;
    const char * na1;

    
//    if(read.parse(str->getCString(), root)){
        char inttostr[40]="";
        sprintf(inttostr, "%d",index);
        shuju=root[inttostr];
        
        
        log("%d",shuju.Size());
        for (int i=0; i<shuju.Size(); i++) {
            
            chatdialogue * dia=new chatdialogue();
            dia->autorelease();
            dia->msg=shuju[i]["msg"].GetString();
            dia->name=shuju[i]["name"].GetString();
            dia->icon=shuju[i]["icon"].GetInt();
            chat_dic->insert(i, dia);
        }
        
//    }
    chatdialogue * d=(chatdialogue *)chat_dic->at(0);
    chatdialogue * d1=(chatdialogue *)chat_dic->at(1);//\u5f20\u4e09
    if(d){
        if(!strcmp(d->name.c_str(), "")){
            ic=d->icon;
            na="主公";
        }
        else{
            
            ic1=d->icon;
            na1=d->name.c_str();
   
        }
    }
    if(d1){
        if(!strcmp(d1->name.c_str(), "")){
            ic=d1->icon;
            na="主公";
            
        }
        else{
            
            ic1=d1->icon;
            na1=d1->name.c_str();
            
            
            
        }
    }
    
    jiantou =this->moveup();
    jiantou->setPosition(Point(600, 10));
    jiantou->setVisible(false);
    chatbg=Sprite::create("chat_bg.png");
    
    chatbg->setOpacity(GLubyte(153));
    chatbg->setAnchorPoint(Point(0, 0));
    chatbg->setPosition(Point(5, 30));
    this->addChild(chatbg,1);
    
    chatbg->addChild(jiantou,2);
    
    
    
    if(ic1>10){
        char icc1[60]="";
        sprintf(icc1, "qs_%d.png",ic1);
        //        enemyIcon=Sprite::create("qs_0001.png");
        enemyIcon=Sprite::create(icc1);
        enemyIcon->setScale(0.38);
        enemyIcon->setVisible(false);
        //enemyIcon->setAnchorPoint(Point(0, 0));
        enemyIcon->setPosition(Point(80, 100));
        
        this->addChild(enemyIcon,1);
        enemyName1=Label::create(na1, "Marker Felt", 35, Size(180, 45), TextHAlignment::LEFT);
        enemyName1->setAnchorPoint(Point(0, 0));
        //create(na1, "Marker Felt", 35);
        enemyName1->setVisible(false);
        //enemyName1->setAnchorPoint(Point(0, 0));
        enemyName1->setPosition(Point(180, 100));
        enemyName1->setColor(Color3B(230, 0, 18));
        this->addChild(enemyName1,1);
    }
    if(ic==0){
        char icc[60]="";
        //        sprintf(icc, "s_wj_icon_%d.png",ic);
        int sex = CData::getCData()->getSex();
        if(sex == 1)
        {
            playerIcon=Sprite::create("qs_0001.png");
        }
        else if (sex == 2)
        {
            playerIcon=Sprite::create("qs_0002.png");
        }
        else
        {
            playerIcon=Sprite::create("qs_0003.png");
        }
        
        
        playerIcon->setScale(0.38);
        playerIcon->setVisible(false);
        
        playerIcon->setPosition(Point(80, 100));//560 100
        this->addChild(playerIcon,1);
        
        
        playerName1=Label::create(na, "Marker Felt", 35, Size(180, 45), TextHAlignment::LEFT);
        
        playerName1->setVisible(false);
        playerName1->setColor(Color3B(23, 181, 172));
        
        playerName1->setAnchorPoint(Point(0, 0));
        playerName1->setPosition(Point(180, 100));//460
        this->addChild(playerName1,1);
    }
    //    ifs.close();
    this->chatPlay();
    
}
void Fire::chatPlay(){
    
    bool chatFlag=CData::getCData()->getChatFlag();
    
    chat_dic->size();
    log("%zd",chat_dic->size());
    chatdialogue * chadia;
    int leng;
    e=0;
    if(roundss<chat_dic->size()){
        jiantou->setVisible(false);
        chadia=(chatdialogue *)chat_dic->at(roundss);
        if(!strcmp(chadia->name.c_str(), "")){
            char iconName[40]="";
            sprintf(iconName, "qs_%d.png",chadia->icon);
            if(playerIcon){
                playerIcon->setVisible(true);
                playerName1->setVisible(true);
            }
            if(enemyIcon){
                enemyIcon->setVisible(false);
                enemyName1->setVisible(false);
            }
            log("%s",chadia->msg.c_str());
            printLabel=Label::create(chadia->msg.c_str(), "Helvetica", 24, Size(0, 50), TextHAlignment::LEFT);
           // printLabel::create(chadia->msg.c_str(), "Helvetica", Size(0, 50),TextHAlignment::LEFT);//initWithString(chadia->msg.c_str(), "Helvetica",30, Size(0, 50), TextHAlignment::LEFT);//330
            //  print->setContentSize(Size(33, 50));
            printLabel->setAnchorPoint(Point(0, 1));
            printLabel->setPosition(Point(175, 100));
            
            log("%s",chadia->name.c_str());
            // playerName1->setString(chadia->name.c_str());
            this->schedule(schedule_selector(Fire::updatalabel), 0.1);
          
        }
        else{
            char iconName[40]="";
            log("%s",chadia->msg.c_str());
            sprintf(iconName, "qs_%d.png",chadia->icon);
            
            printLabel=Label::create(chadia->msg.c_str(), "Helvetica", 24, Size(0, 50), TextHAlignment::LEFT);
           
            printLabel->setAnchorPoint(Point(0, 1));
            printLabel->setPosition(Point(175, 100));
            // enemyIcon->initWithFile("s_wj_icon_5000.png");
            if(playerIcon){
                playerIcon->setVisible(false);
                playerName1->setVisible(false);
            }
            if(enemyIcon){
                enemyIcon->setVisible(true);
                enemyName1->setVisible(true);
            }
            this->schedule(schedule_selector(Fire::updatalabel), 0.1);
            
        }
    }else{
        this->removeChildByTag(004,true);
        this->doChat();
    }
    
    roundss++;
}
void Fire::zhenping(Node * sender){
    // CCScene * f = CCDirector::sharedDirector()->getRunningScene();
    Point size = sender->getPosition();
    ActionInterval * left1 = MoveTo::create(0.03,Point(sender->getPosition().x+5,sender->getPosition().y));
    ActionInterval * right1 = MoveTo::create(0.03,Point(sender->getPosition().x-5,sender->getPosition().y));
    ActionInterval * top1 = MoveTo::create(0.03,Point(sender->getPosition().x,sender->getPosition().y+5));
    ActionInterval * rom1 = MoveTo::create(0.03,size);
    FiniteTimeAction* action3 = Sequence::create(left1,right1,top1,rom1,NULL);
    sender->runAction(action3);
}
void Fire::updatalabel(float dt){
    if(e==10){
        
        this->unschedule(schedule_selector(Fire::updatalabel));
        jiantou->setVisible(true);
        
    }else{
        e++;
        printLabel->setVisible(true);
        printLabel->setDimensions(33*e, 50);
        if(e==10){
            
            
        }
        
    }
}
void Fire::removeChat(){
    // m_pNextBG->removeChildByTag(9013);
    chatBounder->removeFromParentAndCleanup(true);
    m_pNextBG->removeFromParentAndCleanup(true);
    
}
void Fire::doChat(){
    //this->zhenping();
    this->removeChild(printLabel,true);
    this->removeChild(chatbg,true);
    this->removeChild(playerName1,true);
    this->removeChild(enemyName1,true);
    this->removeChild(enemyIcon,true);
    this->removeChild(playerIcon,true);
    char * data2=CData::getCData()->getdata();
    this->getJsonData(data2);
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
void Fire::nextchat(){
    log("%f",printLabel->getDimensions().width);
    if(printLabel->getDimensions().width<330){
        jiantou->setVisible(true);
        printLabel->setDimensions(330, 50);
        this->unschedule(schedule_selector(Fire::updatalabel));
    }else if(printLabel->getDimensions().width==330){
        
        printLabel->setDimensions(0, 50);
        printLabel->setVisible(false);
        this->chatPlay();
    }
}
Fire::~Fire(){
    
    log("Fire destroy!!!!!!!!!!");
    ene_dic->release();
    player_dic->release();
   
    if (sk) {
        delete sk;
    }
    //    delete tx;
    //    delete mz;
    
    //    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    //    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    
    
}
Fire* Fire::fire(){
    if (!g_config) {
        
        //log("Audio effect %d",a);
        g_config = new Fire();
    }
    
    return g_config;
    
}
void Fire::repate(){
    kaishi=0;
    Sprite * background=Sprite::create("pkbg.png");
    background->setPosition(Point(size.width/2, size.height/2));
    this->addChild(background,-2);
    rounds=0;
    char * data2=CData::getCData()->getdata();
    this->getJsonData(data2);
}
void Fire::getJsonData(char * json){
    
    log("enter this");
    
    this->jsonData(json);
    
    this->attackData(json);
}
CCScene * Fire::scene(){
    CCScene *scene=CCScene::create();
    Fire *fire=Fire::create();
    fire->setTag(902);
    scene->addChild(fire);
    return scene;
}
void Fire::SimpleAttack(){
    this->checkOut();
}
void Fire::MoreAttack(){//******************************
    //for(int i=0;i<_length;i++){
    
    t=0;//**********************
    
    enemy=(Sprite *)this->getChildByTag(_eneBattId[moreene[ea]]);
    enemy->removeChildByTag(9023+moreene[ea],true);
    enemy->removeChildByTag(9800+moreene[ea],true);
    Sprite * blood=(Sprite *)enemy->getChildByTag(_eneBattId[moreene[ea]]+1000);
    
    if(_eneChanHp[moreene[ea]]+_eneCurrHp[moreene[ea]]<=0){
        
        ActionInterval *  scal=ScaleTo::create(1/Time, 0, 1);
        CallFunc * func=CallFunc::create(this, callfunc_selector(Fire::removeAction));
        FiniteTimeAction *Action=Sequence::create(scal,func,NULL);
        blood->runAction(Action);
    }
    else{
        
        //percent=((double)currHp+changeHp/(double)totalHp);
        int ech=_eneChanHp[moreene[ea]];
        int echp=_eneCurrHp[moreene[ea]];
        int eth=_eneTotHp[moreene[ea]];
        percent1=((double)(ech+echp)/(double)(eth));
        ActionInterval *  scal=ScaleTo::create(1/Time, percent1, 1);
        CallFunc * func=CallFunc::create(this,callfunc_selector(Fire::removeAction));
        FiniteTimeAction *Action=Sequence::create(scal,func,NULL);
        blood->runAction(Action);
    }
    ea++;
    //}
}
void Fire::removeAction(){
    
    //for (int i=0; i<_length; i++) {
    if(_eneChanHp[t]+_eneCurrHp[t]<=0){
        enemy=(Sprite *)this->getChildByTag(_eneBattId[t]);
        enemy->setTag(_eneBattId[t]);
        //enemy->removeChildByTag(9023+t);
        const char * texiaoname=sk->skills(_skillId);
        char txname[50]="";
        sprintf(txname, "%s.xml",texiaoname);
        
        // AnimatePacker :: getInstance()->freeAnimations(txname);
        this->removeChildByTag(_eneBattId[t],true);
        _eneBattId[t]=0;
        if(t==_length-1){
            this->SimpleAttack();
        }
    }else{
        enemy=(Sprite *)this->getChildByTag(_eneBattId[t]);
        // enemy->removeChildByTag(9023+t);
        if(t==_length-1){
            this->SimpleAttack();
        }
        
    }
    t++;
}
void Fire::checkOut(){
    
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
    
//    Json::Value eneArr;
//    Json::Value buff;
//    chaBattleId=stepData[rounds]["chaBattleId"].GetInt();
//    
//    if(chaBattleId!=0){
//        eneArr=stepData[rounds]["enemyChaArr"];
//        chaId=stepData[rounds]["chaId"].GetInt();
//        actionID=stepData[rounds]["actionId"].GetInt();
//        skillId=stepData[rounds]["skill"].GetInt();
//        chaCurrentPower=stepData[rounds]["chaCurrentPower"].GetInt();
//        
//        if(eneArr.size()==1)
//        {
//            int round=0;
//            if(eneChaId-10<10){
//                fireinfo * fire=new fireinfo();
//                fire->personId=eneChaId-10;
//                
//                buff=eneArr[round]["enemyBuffArr"];
//                for (int i=0; i<buff.size(); i++) {
//                    fire->buff[i]=buff[i].GetInt();
//                }
//                player_dic->setObject(fire, fire->personId);
//               
//            }
//            eneBattleId=eneArr[round]["enemyBattleId"].GetInt();
//            
//            eneChaId=eneArr[round]["enemyChaId"].GetInt();
//            
//            eneActionId=eneArr[round]["enemyActionId"].GetInt();
//            
//            eneChangeHP=eneArr[round]["enemyChangeHp"].GetInt();
//            
//            eneCurrentHp=eneArr[round]["enemyCurrentHp"].GetInt();
//            
//            eneTotalHp=eneArr[round]["enemyTotalHp"].GetInt();
//            if(chaBattleId==-1){
//                this->debuff(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp);
//            }else{
//                this->actionAttack(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp, actionID, chaBattleId,chaId,skillId);
//            }
//           
//        }
//        else if(eneArr.size()>1){
//            int eneChaid[eneArr.size()];
//            int eneChanHp[eneArr.size()];
//            int eneCurrHp[eneArr.size()];
//            int eneTotHp[eneArr.size()];
//            int eneBattId[eneArr.size()];
//            int eneActId[eneArr.size()];
//            for(int i=0;i<eneArr.size();i++){
//                if(eneChaId-10<10){
//                    fireinfo * fire=   new fireinfo();
//                    fire->personId=eneChaId-10;
//                    
//                    buff=eneArr[i]["enemyBuffArr"];
//                    for (int i=0; i<buff.size(); i++) {
//                        fire->buff[i]=buff[i].GetInt();
//                    }
//                    if(buff.size()==0){
//                        * fire->buff=0;
//                        player_dic->setObject(fire, fire->personId);
//                    }else{
//                        player_dic->setObject(fire, fire->personId);
//                    }
//                    //delete fire;
//                }
//                eneBattleId=eneArr[i]["enemyBattleId"].GetInt();
//                
//                eneChaId=eneArr[i]["enemyChaId"].GetInt();
//                
//                eneActionId=eneArr[i]["enemyActionId"].GetInt();
//                
//                eneChangeHP=eneArr[i]["enemyChangeHp"].GetInt();
//                
//                eneCurrentHp=eneArr[i]["enemyCurrentHp"].GetInt();
//                
//                eneTotalHp=eneArr[i]["enemyTotalHp"].GetInt();
//                eneChaid[i]=eneChaId;
//                eneChanHp[i]=eneChangeHP;
//                eneCurrHp[i]=eneCurrentHp;
//                eneTotHp[i]=eneTotalHp;
//                eneActId[i]=eneActionId;
//                eneBattId[i]=eneBattleId;
//            }
//            this->moreActionAttack(eneBattId, eneChaid, eneChanHp, eneCurrHp, eneTotHp, eneActId, chaBattleId, chaId,eneArr.size(),skillId);
//        }
//        int e1=0;
//        int e2=0;
//        int e3=0;
//        int e4=0;
//        int e5=0;
//        for (int i=0; i<9; i++) {
//            fireinfo *fire=(fireinfo *) player_dic->objectForKey(i);
//            if(fire){
//                for(int j=0;j<5;j++){
//                    if(fire->buff[j]==100005){
//                        e1++;
//                    }else if(fire->buff[j]==100003){
//                        e2++;
//                    }else if(fire->buff[j]==100001){
//                        e3++;
//                    }
//                }
//            }
//        }
//        if(e1==0){
//            buff1->setVisible(false);
//        }else if(e2==0)
//        {
//            buff2->setVisible(false);
//        }else if(e3==0){
//            buff3->setVisible(false);
//        }
//        
//        rounds++;
//    }
//    else{
//        AnimatePacker :: getInstance()->freeAnimations ("qishouTX.xml");
//        SpriteFrameCache::getInstance()->removeSpriteFrameByName ("result_attacked.plist");
//        SpriteFrameCache::getInstance()->removeSpriteFrameByName ("jn_name.plist");
//        SpriteFrameCache::getInstance()->removeSpriteFrameByName ("begin1.plist");
//        for(int i=0;i<20;i++){
//            if(skillnumbers[i]!=0){
//                const char * texiaoname=sk->skills(skillnumbers[i]);
//                char names[40]="";
//                sprintf(names, "%s.xml",texiaoname);
//                AnimatePacker::getInstance()->freeAnimations(names);
//            }
//        }
//        log("game over!");
//        GameOver *game=GameOver::create();
//        game->setTag(8021);
//        this->addChild(game,9999);
//    }
    //此处将获取的json数据传递给消息触发器
    
}
void Fire::attackData(char * jsonData){
    printf("%s\n",jsonData);
//    Json::Reader read;
//    Json::Value value;
    int chaBattleId;
    int eneBattleId;
    int eneChaId;
    int eneActionId;
    int eneChangeHP;
    int eneCurrentHp;
    int eneTotalHp;
    int chaId;
    //int pos;
    int dir;
    int actionId;
    int skillId;int chaCurrentPower;
    
    rapidjson::Document d2;
    rapidjson::Value eneArr;
    
    d2.Parse<rapidjson::kParseDefaultFlags>(jsonData);
    rapidjson::Value &data=d2["data"];

   // Json::Value eneArr;
   // if (read.parse(jsonData, value)) {
        //此处解析攻击json数据
//        Json::Value data=value["data"];
        battleresult=data["battleResult"].GetInt();
        CData::getCData()->setFireResult(battleresult);
        stepData=data["stepData"];
        
        chaBattleId=stepData[rounds]["chaBattleId"].GetInt();
        dir=stepData[rounds]["chaDirection"].GetInt();
        eneArr=stepData[rounds]["enemyChaArr"];
        chaId=stepData[rounds]["chaId"].GetInt();
        actionId=stepData[rounds]["actionId"].GetInt();
        skillId=stepData[rounds]["skill"].GetInt();
        chaCurrentPower=stepData[rounds]["chaCurrentPower"].GetInt();
        _chaCurrentPower=chaCurrentPower;
        if(eneArr.Size()==1)
        {
            eneBattleId=eneArr[rounds]["enemyBattleId"].GetInt();
            eneChaId=eneArr[rounds]["enemyChaId"].GetInt();
            eneActionId=eneArr[rounds]["enemyActionId"].GetInt();
            eneChangeHP=eneArr[rounds]["enemyChangeHp"].GetInt();
            eneCurrentHp=eneArr[rounds]["enemyCurrentHp"].GetInt();
            eneTotalHp=eneArr[rounds]["enemyTotalHp"].GetInt();
            _eneCurrentPower=eneArr[rounds]["enemyCurrentPower"].GetInt();
            if(chaBattleId==-1){
                this->debuff(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp);
            }else{
                this->actionAttack(eneBattleId, eneChaId, eneChangeHP, eneCurrentHp, eneTotalHp, actionId, chaBattleId,chaId,skillId);
            }
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
      //  }
        //此处将获取的json数据传递给消息触发器
    }
    rounds++;
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
        
        //    knif=SpriteBatchNode::create("begin.png");
        //    this->addChild(knif);
        //  CCArray * kneif=CCArray::create();
        Vector<SpriteFrame *> kneif;
        SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("01.png");
        Sprite *explosion = Sprite::createWithSpriteFrame(pFrame);
        explosion->setTag(1111);
        explosion->setPosition(Point(size.width/2, size.height/2));
        this->addChild(explosion);
        for (int i=2;i<=10; i++)
        {
            SpriteFrame *spf=SpriteFrameCache::getInstance()->getSpriteFrameByName(String::createWithFormat("%02d.png",i)->getCString());
            
            kneif.pushBack(spf);
        }
        
        ActionInterval * delay=DelayTime::create(1);
        Animation * Action=Animation::createWithSpriteFrames(kneif, 0.1f);
        CallFunc * fun2=CallFunc::create(this, callfunc_selector(Fire::moreattactnext));
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
    CCFadeIn *playerfadein=CCFadeIn::create(0.3f);//0.3f
    CallFunc * fun2=CallFunc::create(this, callfunc_selector(Fire::moreAttackName));
    FiniteTimeAction *playerAct=Sequence::create(playfadeout,playerfadein,fun2,NULL);
    player->runAction(playerAct);
    
}
void Fire::moreAttackName(){
    //SpriteFrame *pFrame=SpriteFrameCache::getInstance()->spriteFrameByName("lq_lq_01.png");
    
    this->removeChildByTag(1111);
    const char * skillname=sk->skillname(_skillId);
    SpriteFrame *pFrame=SpriteFrameCache::getInstance()->spriteFrameByName(skillname);
    label=Sprite::createWithSpriteFrame(pFrame);
    //label=Label::create(skillname, "Marker Felt", 35);
    label->setPosition(Point(size.width/2, size.height/2));
    label->setTag(999);
    this->addChild(label);
    ActionInterval *action=CCMoveTo::create(0.88, Point(size.width/2, size.height/2));
    FadeOut *fadeout=FadeOut::create(0.12f);
    CallFunc * func1=CallFunc::create(this, callfunc_selector(Fire::moreAttackTitle));
    //CallFunc * fun3=CallFunc::create(this, callfunc_selector(Fire::removeSprite));
    FiniteTimeAction *allaction=Sequence::create(action,fadeout,func1,NULL);
    label->runAction(allaction);
    
}
void Fire::debuff(int eneBid,int enechaid,int changeHp1,int eneCurrHp,int eneTotalHp){
    enemy=(Sprite *)this->getChildByTag(eneBid);
    
    
    
    
    currHp=eneCurrHp;
    totalHp=eneTotalHp;
    changeHp=changeHp1;
    // texiao->removeFromParent();//normalattack
    
    
  //  tx=Sprite::createWithSpriteFrameName("ptbj_01.png");
    tx=Sprite::create("attacked_img.png");
  //  tx->runAction(AnimatePacker::getInstance()->getAnimate("ptbj"));
    tx->setPosition(Point(70, 75));

    
    char cHp[10]={0};
    sprintf(cHp, "%d",changeHp);
    
    //reduB=Label::create(cHp,"Marker Felt", 30);
    reduB=CCLabelAtlas::create(cHp, "number.png", 30, 50, '-');
    reduB->setTag(0020);
    reduB->setColor(Color3B(255, 0, 0));
    reduB->setAnchorPoint(Point(0.5, 0));
    reduB->setPosition(Point(enemy->getContentSize().width/2, enemy->getContentSize().height/2));
    enemy->addChild(reduB);
    enemy->addChild(tx);
    // ActionInterval * set_small=CCScaleTo::create(0, 0);
    ActionInterval * set_big=CCScaleTo::create(0.2/Time, 1.5);
    ActionInterval * set_nor=CCScaleTo::create(0.2/Time, 1);
    //ActionInterval *a_jianxue=CCMoveTo::create(0.45, Point(reduB->getPosition().x, reduB->getPosition().y+80));
    
    FadeOut *a_jiaxue_fadeout=FadeOut::create(0.5f/Time);
    // CallFunc * fun3=CallFunc::create(this, callfunc_selector(Fire::removeSprite));
    CallFunc * reduceBlood=CallFunc::create(this, callfunc_selector(Fire::changeBlood));
    FiniteTimeAction *jianxueaction=Sequence::create(set_big,set_nor,a_jiaxue_fadeout,reduceBlood,NULL);
    //FiniteTimeAction *jianxueaction=Sequence::create(a_jianxue,a_jiaxue_fadeout,reduceBlood,NULL);
    reduB->runAction(jianxueaction);
    //    CCShaky3D *shake=CCShaky3D::create(0.3/Time, Size(2, 2), 5, false);
    //    enemy->runAction(shake);
    zhenping(enemy);
    
    
    
    
    //changeHp=changeHp;
    currHp=eneCurrHp;
    eneBID=eneBid;
    totalHp=eneTotalHp;
    _actionId=99;
}
void Fire::buffbegin(int bufftype){
    
    ActionInterval * buffrote1=CCRotateBy::create(10, 360);
    ActionInterval * buffrote2=CCRotateBy::create(15, 360);
    ActionInterval * fadein1=CCFadeIn::create(1);
    ActionInterval * fadeout1=FadeOut::create(1);
    FiniteTimeAction * final=Sequence::create(fadein1,fadeout1,NULL);
    ActionInterval * fadein2=CCFadeIn::create(1.5);
    ActionInterval * fadeout2=FadeOut::create(1.5);
    FiniteTimeAction * final2=Sequence::create(fadein2,fadeout2,NULL);
    ActionInterval * fadein3=CCFadeIn::create(1.2);
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
void Fire::AttackName(){
    // texiao->removeFromParent();
    this->removeChildByTag(2078,true);
    log("%d",_chaCurrentPower);
    Sprite * nl=(Sprite *)player->getChildByTag(24);

    const char * skillname=sk->skillname(_skillId);
    const char * skillss=sk->throwTX(_skillId);
    if(!strcmp(skillname, "")){
        SpriteFrame *pFrame=SpriteFrameCache::getInstance()->spriteFrameByName(skillname);
        label=Sprite::createWithSpriteFrame(pFrame);
        label->setPosition(Point(size.width/2, size.height/2));
        label->setTag(999);
        this->addChild(label);
        ActionInterval *action=CCMoveTo::create(0.88, Point(size.width/2, size.height/2));
        FadeOut *fadeout=FadeOut::create(0.12f);
        CallFunc * func1=CallFunc::create(this, callfunc_selector(Fire::whethertwice));//Fire::attacked
        // CallFunc * fun3=CallFunc::create(this, callfunc_selector(Fire::removeSprite));
        FiniteTimeAction *allaction=Sequence::create(action,fadeout,func1,NULL);
        label->runAction(allaction);
        this->whethertwice();
    }else {
        this->whethertwice();
    }
}
void Fire::whethertwice(){
    
    skk=(skill *)this->returnskills(_skillId);
    if(skk->throwEffectId!=0){
        this->throwtwice();
    }else{
        this->attacked();
    }
}
void Fire::throwtwice(){
    enemy=(Sprite *)this->getChildByTag(eneBID);
    player=(Sprite *)this->getChildByTag(chaIdd);
    log("%d",player->getTag());
    log("%d",enemy->getTag());
    log("%f  %f",player->getPosition().x);
    log("%f  %f",player->getPosition().y);
    log("%f  %f",enemy->getPosition().x);
    log("%f  %f",enemy->getPosition().y);
    const char * skillname=sk->throwTX(_skillId);
    const char * texiaoname=sk->skills(_skillId);
    CCParticleSystemQuad * stars;
    if(!strcmp(texiaoname, "tx")){
        stars=CCParticleSystemQuad::create("touxi_1.plist");
        // stars->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire_1.png"));
        // stars->setBlendAdditive(false);
        stars->setPosition(player->getPosition());
        stars->setTag(8032);
        this->addChild(stars);
        ActionInterval * delay=DelayTime::create(0.1);
        ActionInterval * moveto=CCMoveTo::create(0.5/Time, enemy->getPosition());
        
        CallFunc * func=CallFunc::create(this, callfunc_selector(Fire::attacked));
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
        ActionInterval * moveto=CCMoveTo::create(0.5/Time, enemy->getPosition());
        
        CallFunc * func=CallFunc::create(this, callfunc_selector(Fire::attacked));
        FiniteTimeAction * final=Sequence::create(delay,moveto,func,NULL);
        tz->runAction(final);
        
    }
    
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
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
            
            //        if(!strcmp(label3->getString(), "")){
            //            label3->setString("我方防御增加");
            //        }else if(!strcmp(label2->getString(), "")){
            //            label2->setString("我方防御增加");
            //        }else if(!strcmp(label1->getString(), "")){
            //            label1->setString("我方防御增加");
            //        }else{
            //            const char * str=label1->getString();
            //            label1->setString(label2->getString());
            //            label2->setString(label3->getString());
            //            label3->setString("我方防御增加");
            //        }
            
        }else if(_skillId==100005){
            buffbegin(2);
            label3->setColor(Color3B(0, 255, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("我方攻击增加");
            label3->setPosition(Point(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
            //        if(!strcmp(label3->getString(), "")){
            //            label3->setString("我方攻击增加");
            //        }else if(!strcmp(label2->getString(), "")){
            //            label2->setString("我方攻击增加");
            //        }else if(!strcmp(label1->getString(), "")){
            //            label1->setString("我方攻击增加");
            //        }else{
            //            const char * str=label1->getString();
            //            label1->setString(label2->getString());
            //            label2->setString(label3->getString());
            //            label3->setString("我方攻击增加");
            //        }
        }
        else if(_skillId==100001){
            buffbegin(3);
            //        if(!strcmp(label3->getString(), "")){
            //            label3->setString("我方暴击增加");
            //        }else if(!strcmp(label2->getString(), "")){
            //            label2->setString("我方暴击增加");
            //        }else if(!strcmp(label1->getString(), "")){
            //            label1->setString("我方暴击增加");
            //        }else{
            //            const char * str=label1->getString();
            //            label1->setString(label2->getString());
            //            label2->setString(label3->getString());
            //            label3->setString("我方暴击增加");
            //        }
            label3->setColor(Color3B(0, 255, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("我方暴击增加");
            label3->setPosition(Point(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }
    }else{
        if(_skillId==100002){
            //            buffbegin(1);
            //            if(!strcmp(label3->getString(), "")){
            //                label3->setString("敌方防御增加");
            //            }else if(!strcmp(label2->getString(), "")){
            //                label2->setString("敌方防御增加");
            //            }else if(!strcmp(label1->getString(), "")){
            //                label1->setString("敌方防御增加");
            //            }else{
            //                const char * str=label1->getString();
            //                label1->setString(label2->getString());
            //                label2->setString(label3->getString());
            //                label3->setString("敌方防御增加");
            //            }
            label3->setColor(Color3B(255, 0, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("敌方防御增加");
            label3->setPosition(Point(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }else if(_skillId==100005){
            buffbegin(2);
            label3->setColor(Color3B(255, 0, 0));
            label3->setOpacity(GLubyte(0));
            label3->setString("敌方攻击增加");
            label3->setPosition(Point(520, 420));
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, Point(520, 520));
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
            CCFadeIn * fadein=CCFadeIn::create(0.5);
            DelayTime * delaytime=DelayTime::create(1);
            CCMoveTo *  moveon=CCMoveTo::create(1, Point(520, 520));
            FadeOut * fadeout=FadeOut::create(1);
            Sequence * seq=Sequence::create(fadein,delaytime,moveon,fadeout,NULL);
            
            label3->runAction(seq);
        }
    }
    
    
    const char * namees=skk->releaseName(sk->releaseEffect);
    log("%s",namees);
    char combine[40]="";
    //    char  anames[40]="";
    //    sprintf(anames, "%s_tz",namees);
    
    sprintf(combine, "%s_01.png",namees);
    log("%s",combine);
    texiao=Sprite::createWithSpriteFrameName(combine);
    texiao->setTag(0014);
    
    texiao->runAction(AnimatePacker::getInstance()->getAnimate(namees));
    //delete skk;
    //texiao=(Sprite *)texiao::TX()->texiaosCreate("mou", 8);
    texiao->setPosition(Point(player->getPosition().x, player->getPosition().y));
    this->addChild(texiao,5);
    ActionInterval * moveto=CCMoveTo::create(0.7, Point(player->getPosition().x, player->getPosition().y));//enemy
    CallFunc * fun2=CallFunc::create(this, callfunc_selector(Fire::moreAttacked));
    FiniteTimeAction *playerAct=Sequence::create(moveto,fun2,NULL);
    
    texiao->runAction(playerAct);
    
}
void Fire::moreAttacked(){
    texiao->removeFromParentAndCleanup(true);
    
    //this->removeChildByTag(0014);
    j=0;
    ea=0;
    //t=0;//ceshi
    const char * texiaoname=sk->skills(_skillId);
    char txname[50]="";
    sprintf(txname, "%s.xml",texiaoname);
    
    // AnimatePacker :: getInstance()->loadAnimations(txname);
    for (int i=0; i<_length; i++) {
        moreene[j]=i;
        j++;
        
        
        
        int idnum=sk->skillnums(_skillId);
        log("%d  %s",idnum,texiaoname);
        if(_skillId==100001){
            
        }else if(_skillId==100002){
            
        }
        enemy=(Sprite *)this->getChildByTag(_eneBattId[i]);
        enemy->setTag(_eneBattId[i]);
        
        char combine[50]="";
        sprintf(combine, "%s_01.png",texiaoname);
        mz=Sprite::createWithSpriteFrameName(combine);
        // mz=Sprite::createWithSpriteFrameName("mou_01.png");
        
        mz->runAction(AnimatePacker::getInstance()->getAnimate(texiaoname));
        
        // mz=texiao::TX()->texiaosCreate(texiaoname, idnum);
        mz->setPosition(Point(50, 50));
        mz->setTag(9023+i);
        char changeBlood[20]="";
        sprintf(changeBlood, "%d",_eneChanHp[i]);
        //Label * reduB=Label::create(changeBlood,"Marker Felt", 30);
        CCLabelAtlas * reduB=CCLabelAtlas::create(changeBlood, "number.png", 30, 50, '-');
        reduB->setColor(Color3B(255, 0, 0));
        reduB->setTag(9800+i);
        reduB->setAnchorPoint(Point(0.5, 0));
        reduB->setPosition(Point(enemy->getContentSize().width/2, enemy->getContentSize().height/2));
        enemy->addChild(mz);
        enemy->addChild(reduB);
        // ActionInterval * set_small=CCScaleBy::create(0, 0);
        ActionInterval * set_big=CCScaleBy::create(0.2, 1.5);
        ActionInterval * set_nor=CCScaleBy::create(0.2, 1);
        //ActionInterval *a_jianxue1=CCMoveTo::create(0.2, Point(reduB->getPosition().x, reduB->getPosition().y+60));
        FadeOut *a_jiaxue_fadeout1=FadeOut::create(0.5f);
        CallFunc*  func2=CallFunc::create(this, callfunc_selector(Fire::MoreAttack));
        FiniteTimeAction *jianxueaction1=Sequence::create(set_big,set_nor,a_jiaxue_fadeout1,func2,NULL);
        reduB->runAction(jianxueaction1);
        zhenping(enemy);
        
        
    }
    
}

void Fire::actionAttack(int eneBattleId,int eneChaID,int eneChangeHp,int eneCurrentHp,int eneTotalHp,int actionID,int chaBattleID,int chaId,int skillId){
    log("%d",eneBattleId);
    enemy=(Sprite *)this->getChildByTag(eneBattleId);
    player=(Sprite *)this->getChildByTag(chaBattleID);
    chaIdd=chaBattleID;
    if (kaishi==0){
        
        
        //    knif=SpriteBatchNode::create("begin.png");
        //    this->addChild(knif);
        CCArray * kneif=CCArray::create();
        
        SpriteFrame *pFrame = SpriteFrameCache::getInstance()->spriteFrameByName("01.png");
        explosion = Sprite::createWithSpriteFrame(pFrame);
        explosion->setPosition(Point(size.width/2, size.height/2));
        this->addChild(explosion);
        for (int i=2;i<=10; i++)
        {
            SpriteFrame *spf=SpriteFrameCache::getInstance()->spriteFrameByName(CCString::createWithFormat("%02d.png",i)->getCString());
            log(CCString::createWithFormat("%02d.png",i)->getCString());
            log("\n");
            kneif->addObject(spf);
        }
        
        ActionInterval * delay=DelayTime::create(3.6/Time);
        Animation * Action=Animation::createWithSpriteFrames(kneif, 0.18f/Time);
        CallFunc * fun2=CallFunc::create(this, callfunc_selector(Fire::runBegin));
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
    if(kaishi==0){
        kaishi=1;
        explosion->removeFromParentAndCleanup(true);
    }
    printf("chaBattleId      %d\n",chaIdd);
    cout<<chaIdd/10<<endl;
    if(chaIdd/10==1){
        // sk=new skillList();
        const char * texiaoname=sk->skills(_skillId);
        if(!strcmp(texiaoname, "sq")||!strcmp(texiaoname, "sl")||!strcmp(texiaoname, "sj")||!strcmp(texiaoname, "sf")||!strcmp(texiaoname, "sr")||!strcmp(texiaoname, "sdjx")||!strcmp(texiaoname, "mrj")||!strcmp(texiaoname, "wlbf")){
            
        }
        else{
            
            //   texiao::TX()->texiaosCreate(texiaoname, 5);
        }
        ///log("%s",texiaoname);
        ActionInterval * moveon=CCMoveTo::create(0.12/Time, Point(player->getPosition().x, player->getPosition().y+20));
        ActionInterval * movedown=CCMoveTo::create(0.12/Time, Point(player->getPosition().x, player->getPosition().y));
        
        CallFunc * fun4=CallFunc::create(this, callfunc_selector(Fire::fangzhao));
        FiniteTimeAction *playerAct1=Sequence::create(moveon,movedown,fun4,NULL);
        player->runAction(playerAct1);
    }
    else if(chaIdd/10==2){
        //skillList * sk=new skillList();
        // const char * texiaoname=sk->skills(_skillId);
        // if(strcmp(texiaoname, "0")){
        ActionInterval * moveon=CCMoveTo::create(0.12/Time, Point(player->getPosition().x, player->getPosition().y-20));
        ActionInterval * movedown=CCMoveTo::create(0.12/Time, Point(player->getPosition().x, player->getPosition().y));
        
        CallFunc * fun4=CallFunc::create(this, callfunc_selector(Fire::fangzhao));
        FiniteTimeAction *playerAct1=Sequence::create(moveon,movedown,fun4,NULL);
        log("player tag ===%d",player->getTag());
        player->runAction(playerAct1);
        //}
        
    }
    
    
}
void Fire::fangzhao(){
    
    //此处执行招数动画
    if(_actionId==98){
        
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
        // CData::getCData()->setTFiremusic();
        srandom(time(NULL));
        int s1=0;
        s1=rand()%3;
        switch(s1)
        {
            case 0:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack1.mp3");
                break;
            case 1:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack2.mp3");
                break;
            case 2:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack3.mp3");
                break;
            default:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack1.mp3");
                break;
        }
        skill *sk=this->returnskills(_skillId);
        skillList * skk=new skillList();
        const char * namees=skk->releaseName(sk->releaseEffect);
        
        
        log("%d",sk->releaseEffect);
        //         char  anames[40]="";
        //        sprintf(anames, "%s_tz",namees);
        char combine[40]="";
        sprintf(combine, "%s_01.png",namees);
        texiao=Sprite::createWithSpriteFrameName(combine);
        
        texiao->setTag(2078);
        texiao->runAction(AnimatePacker::getInstance()->getAnimate(namees));
        // addChild(touxi,99);
        //delete skk;
        //texiao=(Sprite *)texiao::TX()->texiaosCreate("mou", 8);
        texiao->setPosition(Point(player->getPosition().x, player->getPosition().y));
        this->addChild(texiao,5);
        ActionInterval * moveto=CCMoveTo::create(1/Time, Point(player->getPosition().x, player->getPosition().y));//enemy
        CallFunc * fun2=CallFunc::create(this, callfunc_selector(Fire::AttackName));
        FiniteTimeAction *playerAct=Sequence::create(moveto,fun2,NULL);
        texiao->runAction(playerAct);
    }else if(_actionId==99){
        
        
     //   normalAttack=Sprite::createWithSpriteFrameName("ptgj_01.png");
        normalAttack = Sprite::create("attack_img.png");
        normalAttack->setTag(0012);
        // normalAttack->setPosition(Point(320, 480));
   //     normalAttack->runAction(CCRepeatForever::create(AnimatePacker::getInstance()->getAnimate("ptgj")));
        //normalAttack=texiao::TX()->normalAttackCreate();
        if(chaIdd/10==1){
            //normalAttack->setRotation(90);
        }
        else if(chaIdd/10==2){
            normalAttack->setRotation(180);
        }
        normalAttack->setPosition(Point(player->getPosition().x, player->getPosition().y+30));
        //normalAttack->setScale(2.0);
        this->addChild(normalAttack,5);
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
        //CData::getCData()->setFiremusic();
        srandom(time(NULL));
        int s2=0;
        s2=rand()%3;
        switch(s2)
        {
            case 0:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack1.mp3");
                break;
            case 1:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack2.mp3");
                break;
            case 2:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack3.mp3");
                break;
            default:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("battleAttack1.mp3");
                break;
        }
        ActionInterval * moveto=CCMoveTo::create(0.4/Time, Point(player->getPosition().x, player->getPosition().y+30));//改动 Point(enemy->getPosition().x, enemy->getPosition().y)
        CallFunc * fun2=CallFunc::create(this, callfunc_selector(Fire::attacked));
        //CallFunc * fun3=CallFunc::create(this, callfunc_selector(Fire::removeSprite));
        FiniteTimeAction *playerAct=Sequence::create(moveto,fun2,NULL);
        normalAttack->runAction(playerAct);
    }
}
void Fire::attacked(){
    
    this->removeChildByTag(8032,true);
    //label->stopAllActions();
    this->removeChildByTag(999,true);
    if(_actionId==99){
        log("_chaCurrentPower %d",_chaCurrentPower);
        //Sprite * nl=(Sprite *)player->getChildByTag(24);
        //normalAttack->removeFromParentAndCleanup(true);
        normalAttack->stopAllActions();
        this->removeChildByTag(0012,true);
        //enemy->removeChildByTag(0012);
        //tx=Sprite::createWithSpriteFrameName("ptbj_01.png");
        tx=Sprite::create("attacked_img.png");
        //tx->setPosition(Point(320, 480));
        
       // tx->runAction(AnimatePacker::getInstance()->getAnimate("ptbj"));
        // tx=texiao::TX()->texiaoCreate();
        tx->setTag(9099);
        tx->setPosition(Point(70, 75));
        
        char cHp[10]={0};
        sprintf(cHp, "%d",changeHp);
        
        //reduB=Label::create(cHp,"Marker Felt", 30);
        
        reduB=CCLabelAtlas::create(cHp, "number.png", 30, 50, '-');
        reduB->setColor(Color3B(255, 0, 0));
        reduB->setAnchorPoint(Point(0.5, 0));
        reduB->setPosition(Point(enemy->getContentSize().width/2, enemy->getContentSize().height/2));
        // reduB->setPosition(enemy->getPosition());
        
        enemy->addChild(reduB);
        
        enemy->addChild(tx);
        ActionInterval *a_jianxue=CCMoveTo::create(0.45/Time, Point(reduB->getPosition().x, reduB->getPosition().y+80));
        // ActionInterval * set_small=CCScaleBy::create(0, 0);
        ActionInterval * set_big=CCScaleTo::create(0.4/Time, 1.5);
        //ActionInterval * set_nor=CCScaleTo::create(0.4/Time, 1);
        FadeOut *a_jiaxue_fadeout=FadeOut::create(0.5f/Time);
        // CallFunc * fun3=CallFunc::create(this, callfunc_selector(Fire::removeSprite));
        CallFunc * reduceBlood=CallFunc::create(this, callfunc_selector(Fire::changeBlood));//changeBlood
        FiniteTimeAction *jianxueaction=Sequence::create(set_big,a_jianxue,a_jiaxue_fadeout,reduceBlood,NULL);
        reduB->runAction(jianxueaction);
        
        zhenping(enemy);
        //    CCShaky3D *shake=CCShaky3D::create(0.3/Time, Size(2, 2), 5, false);
        //    enemy->runAction(shake);
    }
    else if(_actionId==98)
    {
        
        this->removeChildByTag(8078,true);
        const char * texiaoname1=sk->skills(_skillId);
        //        char txname1[50]="";
        //        sprintf(txname1, "%s.xml",texiaoname1);
        //        AnimatePacker :: getInstance()->freeAnimations(txname1);
        //texiao->removeFromParent();
        //normalAttack->removeFromParent();
        
        //skillList * sk=new skillList();
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
        
        ActionInterval * delay=DelayTime::create(1);        //ActionInterval *a_jianxue=CCMoveTo::create(0.45, Point(reduB1->getPosition().x, reduB1->getPosition().y+80));
        CallFunc * reduceBlood=CallFunc::create(this, callfunc_selector(Fire::changeBlood));
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
void Fire::MeasureEneDead(Ref * eneTag){
    
    
    if (_actionId==98) {
        enemy->removeChildByTag(9098,true);
        //mz->removeFromParentAndCleanup(true);
        
    }else if(_actionId==99){
        enemy->removeChildByTag(9099,true);
        //tx->removeFromParentAndCleanup(true);
    }
    if(changeHp+currHp<=0){
        ActionInterval * fadeout=FadeOut::create(0.2);  //FadeOut 作用：创建一个渐变消失的动作 参数是时间
        CallFunc * func=CallFunc::create(this, callfunc_selector(Fire::removeit));
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
void Fire::MutileMeasureEneDead(Node * sender){
    log("%d",sender->getTag());
    
    for (int i=0; i<_length; i++) {
        if(_eneBattId[i]==sender->getTag()){
            log("%d",i);
            if(_eneChanHp[i]+_eneCurrHp[i]>0){
                if (max==1) {
                    max=2;
                    this->SimpleAttack();
                }
                
                
                
            }else{
                
                sender->removeFromParentAndCleanup(true);
            }
        }
    }
}
void Fire::MutileChangeBlood(){
    
    
}
void Fire::changeBlood(){
    log("_eneCurrentPower %d",_eneCurrentPower);
    if (_actionId==98) {
        enemy->removeChildByTag(9098,true);
        reduB1->removeFromParentAndCleanup(true);
        const char * texiaoname=sk->skills(_skillId);
    }else if(_actionId==99){
        enemy->removeChildByTag(9099,true);
        reduB->removeFromParentAndCleanup(true);
    }
    Sprite * blood=(Sprite *)enemy->getChildByTag(1000+eneBID);
    double percent;
    log("cur %d  change %d",currHp,changeHp);
    if(currHp+changeHp<=0){
        ActionInterval *  scal=CCScaleTo::create(0.75/Time, 0, 1);
        CallFunc * func=CallFunc::create(this, callfunc_selector(Fire::MeasureEneDead));
        
        FiniteTimeAction *Action=Sequence::create(scal,func,NULL);
        blood->runAction(Action);
        
    }else if(currHp+changeHp>0){
        
        percent=((double)(currHp+changeHp)/(double)totalHp);
        
        log("%f",percent);
        // cout<<currHp/totalHp<<endl;
        //currHp=currHp+changeHp;
        ActionInterval *  scal=CCScaleTo::create(0.75/Time, percent, 1);
        // ActionInterval * delay=DelayTime::create(0.2);
        CallFunc * func=CallFunc::create(this, callfunc_selector(Fire::MeasureEneDead));
        FiniteTimeAction *Action=Sequence::create(scal,func,NULL);
        blood->runAction(Action);
    }
    
}
void Fire::enemiesLoad(){
    
    //敌人武将头像初始化
    
}
void Fire::playerLoad(){
    //玩家武将头像初始化
    
}
void Fire::jsonData(char *json){
    //此处将server端发送的总json数据进行解析
    Json::Reader read;
    Json::Value value;
    if (read.parse(json, value)) {
        std::string out=value["message"].asCString();
        cout<<out<<endl;
        Json::Value data=value["data"];
        Json::Value setData=data["setData"];
        log("%s",json);
        CData::getCData()->setFireJson(setData);
        this->setJson(setData);
        Json::Value startValue=data["startData"];
        Json::Value array;
        
        const char * name;
        int nengliang;
        int battleId;
        int pinzhi;
        int level;
        float chaCurrentHp;
        float chaTotalHp;
        int icon;
        int chaId;
        
        char tag[2];
        for (int i=0; i<startValue.size(); i++) {
            pos=startValue[i]["chaPos"].GetInt();
            
            battleId=startValue[i]["chaBattleId"].GetInt();
            
            direction=startValue[i]["chaDirection"].GetInt();
            
            level=startValue[i]["chaLevel"].GetInt();
            icon=startValue[i]["chaIcon"].GetInt();
            pinzhi=startValue[i]["difficulty"].GetInt();
            name=startValue[i]["chaName"].asCString();
            nengliang=startValue[i]["chaCurrentPower"].GetInt();
            chaTotalHp=startValue[i]["chaTotalHp"].asDouble();
            chaCurrentHp=startValue[i]["chaCurrentHp"].asDouble();
            chaId=startValue[i]["chaId"].GetInt();
            
            
            this->setBlood(chaCurrentHp, chaTotalHp, pos,direction);
            log("%d",pinzhi);
            sprintf(tag, "%d%d",direction,pos);
            cout<<name<<endl;
            if(direction==1){
                log("%d",pinzhi);
                if(pos>=1&&pos<=3){
                    log("%d",pinzhi);
                    
                    
                    Sprite *player1 = Sprite::create();
                    
                    switch (pinzhi) {
                        case 1:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 2:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 3:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 4:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                        default:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                    }
                    
                    
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    Sprite *player111=Sprite::create(iconname);
                    //                    Sprite *player111=Sprite::create("qs_0001.png");
                    player111->setScale(0.38);
                    player111->setAnchorPoint(Point(0, 0));
                    player1->setTag(direction*10+pos);
                    player111->setPosition(Point(0, 5));
                    player1->setPosition(Point(size.width/2+(pos-2)*150, size.height/2-70));
                    player1->addChild(player111);
                    char  pinz[40]="";

                    this->addChild(player1);
                    
                    Sprite * xuetiao =Sprite::create("PK_blood.png");
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setAnchorPoint(Point(0, 1));
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setPosition(Point(2, 5));
                    player1->addChild(xuetiao,2);
                    player1->setScale(0.6);
                    
                }
                
                if (pos>3&&pos<=6) {
                    
                    
                    
                    Sprite *player1 = Sprite::create();
                    
                    switch (pinzhi) {
                        case 1:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 2:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 3:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 4:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                        default:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                    }
                    
                    
                    
                    
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    //                    Sprite *player111=Sprite::create("qs_0001.png");
                    Sprite *player111=Sprite::create(iconname);
                    player111->setScale(0.38);
                    player111->setAnchorPoint(Point(0, 0));
                    player1->setTag(direction*10+pos);
                    player1->setPosition(Point(size.width/2+(pos-5)*150, size.height/2-190));
                    player1->addChild(player111);
                    char  pinz[40]="";
                    this->addChild(player1);
                    
                    Sprite * xuetiao =Sprite::create("PK_blood.png");
                    xuetiao->setAnchorPoint(Point(0, 1));
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setPosition(Point(2, 5));
                    player1->addChild(xuetiao,2);
                    player1->setScale(0.6);
                    
                }
                if(pos>6&&pos<=9){
                    
                    
                    Sprite *player1 = Sprite::create();
                    
                    switch (pinzhi) {
                        case 1:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 2:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 3:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                        case 4:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                        default:
                            player1->initWithFile("common_qs_bkg_1.png");
                            break;
                            
                    }
                    
                    
                    
                    
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    //                    Sprite *player111=Sprite::create("qs_0001.png");
                    Sprite *player111=Sprite::create(iconname);
                    player111->setScale(0.38);
                    player1->setTag(direction*10+pos);
                    player1->setPosition(Point(size.width/2+(pos-8)*150, size.height/2-310));
                    player111->setAnchorPoint(Point(0, 0));
                    player1->addChild(player111);
                    char  pinz[40]="";
                    this->addChild(player1);
                    
                    Sprite * xuetiao =Sprite::create("PK_blood.png");
                    xuetiao->setAnchorPoint(Point(0, 1));
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setPosition(Point(2, 5));
                    player1->addChild(xuetiao,2);
                    player1->setScale(0.6);
                    
                }
                
            }else if(direction==2){
                
                
                
                Sprite *ene1 = Sprite::create();
                
                switch (pinzhi) {
                    case 1:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                    case 2:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                    case 3:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                    case 4:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                        
                    default:
                        ene1->initWithFile("common_qs_bkg_1.png");
                        break;
                        
                }
                
                ene1->setScale(0.9);
                
                if(pos>=1&&pos<=3){
                    
                    
                    
                    
                    
                    
                    
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    //                    Sprite *  ene111=Sprite::create("qs_0001.png");
                    Sprite *  ene111=Sprite::create(iconname);
                    ene111->setScale(0.38);
                    ene1->setTag(direction*10+pos);
                    
                    ene1->setPosition(Point(size.width/2+(pos-2)*150, size.height/2+65));
                    ene111->setAnchorPoint(Point(0, 0));
                    ene1->addChild(ene111);
                    char  pinz[40]="";
                    this->addChild(ene1);
                    Sprite * xuetiao =Sprite::create("PK_blood.png");
                    xuetiao->setAnchorPoint(Point(0, 1));
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setPosition(Point(2, 5));
                    ene1->addChild(xuetiao,2);
                    ene1->setScale(0.6);
                    
                }
                if (pos>3&&pos<=6) {
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    
                    //                    Sprite * ene111=Sprite::create("qs_0001.png");
                    Sprite * ene111=Sprite::create(iconname);
                    ene111->setScale(0.38);
                    ene1->setTag(direction*10+pos);
                    
                    ene1->setPosition(Point(size.width/2+(pos-5)*150, size.height/2+190));
                    ene111->setAnchorPoint(Point(0, 0));
                    ene1->addChild(ene111);
                    this->addChild(ene1);
                    char  pinz[40]="";
                    Sprite * xuetiao =Sprite::create("PK_blood.png");
                    xuetiao->setAnchorPoint(Point(0, 1));
                    xuetiao->setTag(1000+direction*10+pos);
                    xuetiao->setScaleX(chaCurrentHp/chaTotalHp+0.1);
                    xuetiao->setPosition(Point(2, 5));
                    ene1->addChild(xuetiao,2);
                    ene1->setScale(0.6);
                }
                if(pos>6&&pos<=9){
                    char iconname[30]="";
                    sprintf(iconname, "qs_%04d.png",icon);
                    //                    Sprite *   ene111=Sprite::create("qs_0001.png");
                    Sprite *   ene111=Sprite::create(iconname);
                    ene111->setScale(0.38);
                    ene1->setTag(direction*10+pos);
                    
                    ene1->setPosition(Point(size.width/2+(pos-8)*150, size.height/2+310));
                    ene111->setAnchorPoint(Point(0, 0));
                    ene1->addChild(ene111);
                    this->addChild(ene1);
                    char  pinz[40]="";
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
    }
}
void Fire::setBlood(float curB, float nowB, int i,int dir){
    //此处初始化敌方武将血条
}
void Fire::removeSprite(Node *sender){
    sender->removeFromParent();
}
void  Fire::setJson(Json::Value json){
    _json=json;
    int coin;
    
    coin=json["star"].GetInt();
    log("%d %d",coin,_json["star"].GetInt());
}
Json::Value  Fire::getJson(){
    int star=_json["star"].GetInt();
    log("%d",star);
    return _json;
}
int Fire::getStar(){
    return NULL;
}
int Fire::result(){
    return battleresult;
}

Sprite * Fire::moveup(){
    updown=Sprite::create("smalljiantou.png");
    ActionInterval * up=CCMoveBy::create(0.5/Time, Point(updown->getPosition().x, updown->getPosition().y+20));
    ActionInterval * down=CCMoveBy::create(0.5/Time, Point(updown->getPosition().x, updown->getPosition().y-20));
    FiniteTimeAction * final=Sequence::create(up,down,NULL);
    CCRepeatForever * rep=CCRepeatForever::create((ActionInterval *)final);
    updown->runAction(rep);
    return updown;
}



skill * Fire::returnskills(int skillId){
    //    const char * path=CCFileUtils::sharedFileUtils()->fullPathForFilename("skill.json").c_str();
    //    ifstream ifs;
    //    ifs.open(path);
    //    assert(ifs.is_open());
    Json::Reader read;
    Json::Value root;
    Json::Value data;
    Json::Value row;
    char skillss[40]="";
    sprintf(skillss, "%d",skillId);
    skill * skills=new skill();
    skills->autorelease();
    
    
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("skill.json");
    CCString* str = CCString::createWithContentsOfFile(path.c_str());
    
    
    if(read.parse(str->getCString(), root)){
        data=root[skillss];
        
        
        skills->releaseEffect=data["releaseEffect"].GetInt();
        skills->throwEffectId=data["throwEffectId"].GetInt();
        skills->bearEffect=data["bearEffect"].GetInt();
    }
    //    ifs.close();
    return skills;
}


void Fire::onExit()
{
    AnimatePacker :: getInstance()->freeAnimations ("qishouTX.xml");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName ("result_attacked.plist");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName ("jn_name.plist");
    SpriteFrameCache::getInstance()->removeSpriteFrameByName ("begin1.plist");
    
    CCLayer::onExit();
    
    //    player_dic->removeAllObjects();
    //    player_dic->release();
    
}

void Fire::recv_4501(){
    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(4501);
    CData::getCData()->m_dictionary->removeObjectForKey(4501);
    
    if(revMsg){
        
        this->unschedule(schedule_selector(Fire::recv_4501));
        char* data=revMsg->data;
        Json::Reader read;
        Json::Value value;
        if(read.parse(data, value))
        {
            
            if (value["result"].asBool()) {
                CData::getCData()->setdata(data);
                CData::getCData()->setczorzy(true);
                initFireData();
            }
            else
            {

            }
            
            log("%s",data);
        }
    }
    
}





