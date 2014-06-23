#include "homePage.h"
//#include "CCScrollView.h"
//#include "zhuangtaiLoad.h"
//#include "json.h"
//#include "LayerLogin.h"
//#include "SocketManager.h"
#include "CustomPop.h"



void homePage::onExit()
{
    log("homePage onExit");
    CCLayer::onExit();
}

homePage::~homePage(){
    
    log("homePage destroy");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}
bool homePage::init(){
    if(!CCLayer::init()){
        return false;
    }
    
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    
    //    load=Loading::create();
    //    this->addChild(load,9999);
    //
    //    int characterId=CData::getCData()->getCharactorId();
    //    CCLog("%d",characterId);
    //    Json::FastWriter writer;
    //    Json::Value sendMessage;
    //    sendMessage["characterId"]=characterId;
    //    sendMessage["index"]=0;
    //    std::string json_file_jianghu=writer.write(sendMessage);
    //    CCLog("%s",json_file_jianghu.c_str());
    //    SocketManager::getInstance()->sendMessage(json_file_jianghu.c_str(), 4500);
    //    this->schedule(schedule_selector(homePage::rec_4500));
    
    
    
    size = Director::getInstance()->getWinSize();
    
    
    //    Sprite* bkg = Sprite::create("zjm_bkg.png");
    //    bkg->setAnchorPoint(Point(0.5, 0.5));
    //    bkg->setContentSize(size);
    //    bkg->setPosition(Point(0, 0));
    //    this->addChild(bkg, 1);
    
    this->zhuangtaiLoad();
    this->btnsLoading();
    this->downBtnLoading();
    
    return true;
}
void homePage::initTitle(){
   
}

//加载中部地图
void homePage::btnsLoading(){
    layerMainMap= LevelMap::create();//  Btns::create();
    layerMainMap->setAnchorPoint(Point(0, 0));
    this->addChild(layerMainMap,0);
    //
}
void homePage::zhuangtaiLoad(){
    zhuangtai1 =zhuangtai::create();
    zhuangtai1->setVisible(true);
    zhuangtai1->setPosition(Point(0, size.height-100));
    this->addChild(zhuangtai1,1);
    
}

void homePage::openPersonal()
{
    
    //    this->removelayers();
    //    btnEmployFriends->setVisible(false);
    //    btnHeCheng->setVisible(false);
    //    layerPersonInfo = personalinfo::create();
    //    this->addChild(layerPersonInfo);
    
    
}

void homePage::removelayers()
{
        this->removeChild(layerMainMap, true);
//        this->removeChild(layerPersonInfo,true);
//       this->removeChild(layerNewBuZhen, true);
//       this->removeChild(compound,true);
          //this->removeChild(layerFriend);
}

void homePage::openArenaWindow()
{
        CustomPop::show("敬请期待");
    //    this->removelayers();
    //    btnEmployFriends->setVisible(false);
    //    btnHeCheng->setVisible(false);
    //    layerArena = ArenaWindow::create();
    //    this->addChild(layerArena);
    
}

void homePage::openMailWindow()
{
    //    this->removelayers();
    //    btnEmployFriends->setVisible(false);
    //    btnHeCheng->setVisible(false);
    //    layerMail = MailWindow::create();
    //    this->addChild(layerMail);
    
    CustomPop::show("敬请期待");
    
}

void homePage::employFriends()
{
    CustomPop::show("敬请期待");
}

void homePage::recharge()
{
    
    CustomPop::show("尚未开通");
}

//下部功能按钮
void homePage::downBtnLoading(){
    
    btnHeCheng = MenuItemImage::create("zjm_hc_1.png",
                                       "zjm_hc_2.png",
                                       CC_CALLBACK_1(homePage::openHeCheng, this));
    
    btnHeCheng->setPosition(Point(70, size.height-165));
    
    btnEmployFriends = MenuItemImage::create("zjm_employfriends_1.png",
                                             "zjm_employfriends_2.png",
                                             CC_CALLBACK_0(homePage::employFriends, this));
    
    btnEmployFriends->setPosition(Point(size.width - 60, size.height-165));
    
    
    btnPersonal = MenuItemImage::create("zjm_personal_1.png",
                                        "zjm_personal_1.png",
                                        CC_CALLBACK_0(homePage::openPersonal, this));
    btnPersonal->setAnchorPoint(Point(0.5, 0.5));
    btnPersonal->setPosition(Point(size.width/2, 733));
    
    linkFecharge = MenuItemImage::create("zjm_linkrecharge_1.png", "zjm_linkrecharge_2.png",
                                         CC_CALLBACK_0(homePage::recharge, this));
    linkFecharge->setAnchorPoint(Point(0, 0));
    linkFecharge->setPosition(Point(50, 25));
    
    btnMail = MenuItemImage::create("zjm_mail_1.png",
                                    "zjm_mail_2.png",
                                    CC_CALLBACK_0(homePage::openMailWindow, this));
    btnMail->setAnchorPoint(Point(0, 0));
    btnMail->setPosition(Point(150, 25));
    
    btnArena = MenuItemImage::create("zjm_arena_1.png", "zjm_arena_2.png",CC_CALLBACK_0(homePage::openArenaWindow, this));
    btnArena->setAnchorPoint(Point(0, 0));
    btnArena->setPosition(Point(240, 25));
    
    
    homeLink = MenuItemImage::create("zjm_linkhome_1.png", "zjm_linkhome_2.png",CC_CALLBACK_0(homePage::mainView, this));
    homeLink->setAnchorPoint(Point(1, 0));
    homeLink->setPosition(Point(size.width-45,25));
    
    
    menu=CCMenu::create(btnHeCheng,btnEmployFriends,btnPersonal,linkFecharge,homeLink,btnMail,btnArena,NULL);
    menu->setAnchorPoint(Point(0, 0));
    menu->setPosition(Point(0, 0));
    
    this->addChild(menu,6,1878);
    
}
void homePage::mainView(){
    
    
    this->removelayers();
    btnEmployFriends->setVisible(true);
    btnHeCheng->setVisible(true);
    layerMainMap= LevelMap::create();//  Btns::create();
    layerMainMap->setAnchorPoint(Point(0, 0));
    this->addChild(layerMainMap,0);
    //
    //    CData::getCData()->setyinxiao();
    //     zhuangtai1->upData();
    
    
}

void homePage::openNewBuZhen()
{
    CustomPop::show("敬请期待");
//    this->removelayers();
//    btnEmployFriends->setVisible(false);
//    btnHeCheng->setVisible(false);
    //    layerNewBuZhen = newBuZhen::create();
    //    this->addChild(layerNewBuZhen);
}



void homePage::openHeCheng(Ref *building)
{
   
  //  CustomPop::show("敬请期待");
    ODSocket* socket = new ODSocket();
	socket->Init();
	socket->Create(AF_INET,SOCK_STREAM,0);
	bool isConnet = socket->Connect("127.0.0.1",9998);
    
	
		if (isConnet)
		{
            //CustomPop::show("连接成功！");
            char recvBuf[1024] = "*";
            std::string testmsg="{'id':1,'msgType':1101,'name':'wangfeng','QQNum':'972341215'}";
			
            socket->Send(testmsg.c_str(),strlen(testmsg.c_str()) + 1,0);
            
            bool a = true;
            while (a) {
               int b = socket->Recv(recvBuf,1024,0);
                a = b < 0;
                log("Rev%d", a);
            }
            
           string sp=prepareChar(recvBuf);
            
            cout<<sp<<endl;
           // log("接收:%s", sp->);
		}
		else
		{
			CustomPop::show("连接失败！");
		}
}

string homePage::prepareChar(char *ps){

    while (ps[0] != '{')
    {
        ps++;
    }
    std::string str(ps);

    return str;
}

void homePage::rec_4500()
{
    //    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(4500);
    //    CCLog("%s",revMsg);
    //    CData::getCData()->m_dictionary->removeObjectForKey(4500);
    //
    //    if(revMsg)
    //    {
    //        this->unschedule(schedule_selector(homePage::rec_4500));//删除刷新
    //        CData::getCData()->cityData = revMsg->data;
    //        CCLog("%s",revMsg->data);
    //        load->removeFromParent();
    //
    //        this->initTitle();//加载标题
    //        this->btnsLoading();//加载中部按钮
    //        this->zhuangtaiLoad();//加载状态栏
    //        this->downBtnLoading();//加载底部按钮
    //        
    //       zhuangtai1->upData();
    //        
    //       if (CData::getCData()->isArenaFire) {
    //              this->openArenaWindow();
    //          }
    //
    //        
    //        
    //    }
    
}


