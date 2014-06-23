#include "popwindow.h"
//#include "FireWork.h"
//#include "SocketClient.h"
//#include "LayerLogin.h"
//#include "message.h"

#include "homePage.h"
//#include "SocketManager.h"

#include "CustomPop.h"

bool buildingpop::init(){
    if(!LayerColor::initWithColor(Color4B(0, 0, 0, 128))){
        
        
        return false;
    }
  
    //this->setTouchEnabled(true);
    
    
    Size size=Director::getInstance()->getWinSize();
    this->setContentSize(size);
    
    lock = false;
    
    Sprite *bkg = Sprite::create("popbuilding_buzhen_bkg.png");
    bkg->setAnchorPoint(Point(0, 0));
    
    
    
    bkg->setPosition(Point(size.width/2, size.height/2));
    
    this->addChild(bkg);
    //bkg->setScale(1.2);

    size = bkg->getContentSize();
    
    name = CCLabelTTF::create("", "hycc.ttf", 18);
    name->setAnchorPoint(Point(0, 1));
    //name->setHorizontalAlignment(kCCTextAlignmentLeft);
    name->setVerticalAlignment(TextVAlignment::TOP);
    name->setDimensions(Size(60, 0));
//    name->setAnchorPoint(Point(1, 1));
    name->setPosition(Point(53, size.height-225));
    const Color3B color1 = {121,96,67};
    name->setColor(color1);
    bkg->addChild(name);
    
    namedesc = CCLabelTTF::create("", "hycc.ttf", 18);
    namedesc->setAnchorPoint(Point(0, 1));
    namedesc->setDimensions(Size(300, 0));
    namedesc->setHorizontalAlignment(TextHAlignment::LEFT);
    namedesc->setVerticalAlignment(TextVAlignment::TOP);
    namedesc->setPosition(Point(140, size.height-220));
    const Color3B color2 = {36,24,6};
    namedesc->setColor(color2);
    bkg->addChild(namedesc);
    
    name1 = CCLabelTTF::create("敌人", "hycc.ttf", 18);
    name1->setAnchorPoint(Point(0, 1));
    name1->setHorizontalAlignment(TextHAlignment::LEFT);
    name1->setVerticalAlignment(TextVAlignment::TOP);
    name1->setDimensions(Size(60, 0));
    name1->setAnchorPoint(Point(1, 1));
    name1->setPosition(Point(70, size.height-335));
   // const Color3B color1 = {255,255,255};
    name1->setColor(color1);
    bkg->addChild(name1);
    
    namedesc1 = CCLabelTTF::create("", "hycc.ttf", 18);
    namedesc1->setAnchorPoint(Point(0, 1));
    namedesc1->setDimensions(Size(300, 0));
    namedesc1->setHorizontalAlignment(TextHAlignment::LEFT);
    namedesc1->setVerticalAlignment(TextVAlignment::TOP);
    namedesc1->setPosition(Point(135, size.height-328));
//    const ccColor3B color2 = {0,255,0};
    namedesc1->setColor(color2);
    bkg->addChild(namedesc1);

    
//    name2 = CCLabelTTF::create("奖励", "hycc.ttf", 18);
//    name2->setAnchorPoint(Point(0, 1));
//    name2->setHorizontalAlignment(kCCTextAlignmentLeft);
//    name2->setVerticalAlignment(kCCVerticalTextAlignmentTop);
//    name2->setDimensions(Size(400, 0));
//    //    name1->setAnchorPoint(Point(1, 1));
//    name2->setPosition(Point(40, size.height-213));
//    //    const ccColor3B color1 = {255,255,255};
//    name2->setColor(color1);
//    bkg->addChild(name2);
    
    cl= MenuItemImage::create("common_btn_close_1.png",
                              "common_btn_close_2.png",
                              CC_CALLBACK_0(buildingpop::close, this));
    cl->setPosition(Point(453, 650));
    bz = MenuItemImage::create("popbuilding_buzhen_1.png", "popbuilding_buzhen_2.png",CC_CALLBACK_0(buildingpop::buzhen, this));//buildingpop::close,buildingpop::buzhen
   
//    cl->setAnchorPoint(Point(0,0));
    bz->setPosition(Point(152, 207));
    
    ft = MenuItemImage::create("popbuilding_fire_1.png", "popbuilding_fire_2.png","popbuilding_fire_3.png", CC_CALLBACK_0(buildingpop::fight, this));
    ft->setAnchorPoint(Point(0,0));
    ft->setPosition(Point(243, 180));
    //ft->setScale(1.3);
    
//    bz = MenuItemImage::create("", "", CC_CALLBACK_0(buildingpop::buzhen));
//    bz->setAnchorPoint(Point(0,0));
//    bz->setPosition(Point(40, 30));
    //bz->setScale(1.3);
    
    btnsMenu = CCMenu::create(cl,ft,bz,NULL);
    
    btnsMenu->setAnchorPoint(Point(0,0));
    btnsMenu->setPosition(Point(0,0));
    
    bkg->addChild(btnsMenu);
    
    Sprite* gold = Sprite::create("popbuilding_gold.png");
    gold->setPosition(Point(195, 300));
    bkg->addChild(gold);
    goldlabel = LabelTTF::create("", "hycc.ttf", 18, Size(150, 0), TextHAlignment::LEFT);
    goldlabel->setAnchorPoint(Point(0, 0.5));
    goldlabel->setPosition(Point(215, 300));
    goldlabel->setColor(color2);
    bkg->addChild(goldlabel);
    
    Sprite* wei = Sprite::create("popbuilding_wei.png");
    wei->setPosition(Point(80, 300));
    bkg->addChild(wei);
    weilabel = LabelTTF::create("", "hycc.ttf", 18, Size(150, 0), TextHAlignment::LEFT);
    weilabel->setAnchorPoint(Point(0, 0.5));
    weilabel->setPosition(Point(100, 300));
    weilabel->setColor(color2);
    bkg->addChild(weilabel);
    
    
    Sprite* wu = Sprite::create("popbuilding_wu.png");
    wu->setPosition(Point(320, 300));
    bkg->addChild(wu);
    wulabel = LabelTTF::create("", "hycc.ttf", 18, Size(250, 0), TextHAlignment::LEFT);
    wulabel->setAnchorPoint(Point(0, 0.5));
    wulabel->setPosition(Point(340, 300));
    wulabel->setColor(color2);
    bkg->addChild(wulabel);
    
    
//    this->setTouchPriority((std::numeric_limits<int>::min()));
    
    
    return true;
}

void buildingpop::buzhen()
{
//    newBuZhen * sp = newBuZhen::create();
//    this->getParent()->addChild(sp);
    ((homePage*)(this->getParent()))->openNewBuZhen();
    this->removeFromParent();
}

void buildingpop::close(){
    this->hide();
}
//
void buildingpop::fight(){
    if(lock)
    {
        return;
    }
    lock = true;
    
//    load=Loading::create();
//    addChild(load,9999);
    

//    CData::getCData()->battleCityId = this->item->bid;
//    CCScene *scene=Fire::scene();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, scene));
//
//    return;

    


    
//    Json::FastWriter writer;
//    Json::Value root;
//    
//    root["characterId"]=CData::getCData()->getCharactorId();
//    root["zjid"]= this->item->bid;
//    
//    CData::getCData()->battleCityId = this->item->bid;
//    
//    std::string json_file_zhandou=writer.write(root);
//    SocketManager::getInstance()->sendMessage(json_file_zhandou.c_str(), 4501);
//       this->schedule(schedule_selector(buildingpop::receiveFireData),0.2);
    
    
}

void buildingpop::receiveFireData(){
//    Message *revMsg=(Message *)CData::getCData()->m_dictionary->objectForKey(4501);
//    CData::getCData()->m_dictionary->removeObjectForKey(4501);
//    
//    if(revMsg){
//        
//        this->unschedule(schedule_selector(buildingpop::receiveFireData));
//       char* data=revMsg->data;
//        
//        
//        Json::Reader read;
//        Json::Value value;
//        if(read.parse(data, value))
//        {
//            
//            if (value["result"].asBool()) {
//                
//                CData::getCData()->setdata(data);
//                CData::getCData()->setczorzy(true);
//                CData::getCData()->battleCityId = this->item->bid;
//            CCScene *scene=Fire::scene();
//                
//            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, scene));
//            load->removeFromParent();
//                
//            }
//            else
//            {
//                CustomPop::show(value["message"].asString().c_str());
//            }
//            
//            this->hide();
//        }
    
        
        
        
        
        
//        CCLog("%s",data);
//        if(data){
//            CData::getCData()->setdata(data);
//            CData::getCData()->setczorzy(true);
//        
//            
//            
//            
//            CData::getCData()->battleCityId = this->item->bid;
//            CCScene *scene=Fire::scene();
//            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, scene));
//            
//
//            this->hide();
//        }
//    }

}


void buildingpop::show(MapItem *item){
    lock = false;
    this->setVisible(true);
        this->item = item;
    
    
    
//    char * json=CData::getCData()->cityData;
//    Json::Reader read;
//    Json::Value  root;
//    Json::Value  data;
//    
//    
//    if(read.parse(json, root))
//    {
//        data=root["data"];
//    }
//    
    
//    int curCityID = data["cityid"].asInt();
//    if (item->bid <= curCityID) {
//        ft->setEnabled(true);
//    }
//    else
//    {
//        ft->setEnabled(false);
//    }
    
    name->setString(item->nickname.c_str());
    namedesc->setString(item->desc.c_str());

    namedesc1->setString(item->enemydesc.c_str());
//    log("%s",namedesc1);
    char tmp[50]= "";
    sprintf(tmp, "钱 +%d",item->coin);
    goldlabel->setString(tmp);
    
    char tmp1[50]= "";
    sprintf(tmp1, "威 +%d",item->exp);
    weilabel->setString(tmp1);
    
    if (item->itemId == 0) {
        wulabel->setString("无掉落物品");
    }
    else
    {
        char tmp2[50]= "";
 //       configGoodsItem* gitem = CData::getCData()->getConfigOfGoods(item->itemId);
 //       sprintf(tmp2, "物 【%s】",gitem->name.c_str());
        wulabel->setString(tmp2);
    }
   
    
    
}
void buildingpop::hide()
{
    this->setVisible(false);
    this->removeAllChildren();
    this->getParent()->removeChild(this, true);
}

//void buildingpop::onExit()
//{
//    CCLog("buildingpop onExit");
//    
//    LayerColor::onExit();
//    
//}

buildingpop::~buildingpop()
{
    log("buildingpop destroy");
}

//void buildingpop::registerWithTouchDispatcher()
//{
//    
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,(std::numeric_limits<int>::min()), true);
//    CCLayer::registerWithTouchDispatcher();
//}

bool buildingpop::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    istouch=btnsMenu->onTouchBegan(touch, event);
    
    // 因为回调调不到了，所以resume写在了这里
    //   CCLog("loading layer");
    return true;
}

void buildingpop::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(istouch){
        
        btnsMenu->onTouchMoved(touch, event);
    }
}
void buildingpop::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    if (istouch) {
        btnsMenu->onTouchEnded(touch, event);
        
        istouch=false;
        
    }
}

