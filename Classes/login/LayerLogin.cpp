#include "LayerLogin.h"
#include "homePage.h"
#include "SocketClient.h"
#include "message.h"
#include "MessageQueue.h"
#include "zhuangtaiLoad.h"
#include "startAnimate.h"
#include "Singleton.h"
#include "AnimatePacker.h"
#include "SocketManager.h"
#include "CData.h"
#include "CustomPop.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"

#include "json.h"


bool LayerLogin::init()
{
    if(!Layer::init())
    {
        return false;
    }
    const char *bgMusic="bg.mp3";
    CData::getCData()->setyinyue(bgMusic);
    SocketManager::getInstance()->startSocket();
    loadRes();
    initUI();
    
    return true;
}

void LayerLogin::firefly()
{
    if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    {
       
    }
}

void LayerLogin::jiumiaoshanyou()
{
    if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    {
       
    }
}

void LayerLogin::initUI()
{
    winSize = Director::getInstance()->getWinSize();
    Sprite *bg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_bkg.png"));
    bg->setPosition(Point(winSize.width*0.5,winSize.height*0.5));
    this->addChild(bg);
    if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    {
        url1=CCMenuItemImage::create("ns-1.png", "ns-2.png", CC_CALLBACK_0(LayerLogin::jiumiaoshanyou, this));
        url1->setPosition(Point(winSize.width-120, winSize.height-55));
        url2=CCMenuItemImage::create("ff-1.png", "ff-2.png", CC_CALLBACK_0(LayerLogin::firefly,this));
        url2->setPosition(Point(winSize.width-45, winSize.height-55));
        Menu *urlMenu=Menu::create(url1,url2,NULL);
        urlMenu->setPosition(Point::ZERO);
        urlMenu->setAnchorPoint(Point(0,0));
        this->addChild(urlMenu);
    }
    else
    {
        url1=CCMenuItemImage::create("ns-1.png", "ns-2.png", CC_CALLBACK_0(LayerLogin::callNull1, this));
        url1->setPosition(Point(winSize.width-120, winSize.height-55));
        url2=CCMenuItemImage::create("ff-1.png", "ff-2.png",CC_CALLBACK_0(LayerLogin::callNull2, this));
        url2->setPosition(Point(winSize.width-45, winSize.height-55));
        Menu *urlMenu=Menu::create(url1,url2,NULL);
        urlMenu->setPosition(Point::ZERO);
        urlMenu->setAnchorPoint(Point(0,0));
        this->addChild(urlMenu);

    }
    this->zhenping();

    sendData=denglu1;

}

void LayerLogin::loadRes()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui_login.plist");
}

void LayerLogin::callNull1()
{
    
}
void LayerLogin::callNull2()
{
    
}
void LayerLogin::zhenping(){
    pSpriteDialogLogin = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_input.png"));//spriteFrameByName("login_input.png"));//Sprite::create("login_bg_en.png");
    pSpriteDialogLogin->setPosition(Point(winSize.width*0.5,winSize.height *0.5-100));
    this->addChild(pSpriteDialogLogin);
    MenuItemImage* btn_login = MenuItemImage::create();
    btn_login->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_login_1.png"));
    btn_login->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_login_2.png"));
    btn_login->setTarget(this, SEL_MenuHandler(&LayerLogin::menuItemCallbackLogin));
    Label *version=Label::create("V1.4", "hycc.ttf", 18);
    version->setColor(Color3B(28,42,52));
    version->setPosition(Point(winSize.width*0.5,winSize.height *0.5-290));
    this->addChild(version);
    Menu *pMenu = Menu::create();
    pMenu->alignItemsHorizontally();
    pMenu->addChild(btn_login);
    //pMenu->setPosition(pSpriteDialogLogin->getContentSize().width-75,pSpriteDialogLogin->getContentSize().height/2-10);
    pMenu->setPosition(Point(winSize.width/2-30, winSize.height/2-460));
    //pMenu->setTouchPriority(1);
    pSpriteDialogLogin->addChild(pMenu);

    Scale9Sprite* editbkg = Scale9Sprite::create();
    
    editBoxUsername = EditBox::create(Size(210,50),editbkg);
    editBoxUsername->setReturnType(EditBox::KeyboardReturnType::DEFAULT);//setReturnType(kKeyboardReturnTypeDone);
    editBoxUsername->setFontSize(12);
    editBoxUsername->setText("");
    editBoxUsername->setFontColor(Color3B(158, 122, 83));
    editBoxUsername->setMaxLength(8);
    editBoxUsername->setPosition(Point(winSize.width/2-10,96));//160,100
    pSpriteDialogLogin->addChild(editBoxUsername,2);
    
    Scale9Sprite* editbkg1 = Scale9Sprite::create();
    editBoxPassword = EditBox::create(Size(190, 50),editbkg1);
    editBoxPassword->setReturnType(EditBox::KeyboardReturnType::DONE);
    editBoxPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
    editBoxPassword->setFontColor(Color3B(158, 122, 83));
    editBoxPassword->setMaxLength(8);
    editBoxPassword->setFontSize(8);
    editBoxPassword->setText("");
    editBoxPassword->setPosition(Point(winSize.width/2-22,45));//160,60
    
    pSpriteDialogLogin->addChild(editBoxPassword,2);

}

void LayerLogin::onExit()
{
    log("LayerLogin onExit");
    Layer::onExit();
}

LayerLogin::~LayerLogin()
{
    log("LayerLogin destroy");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("ui_login.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("ui_login.png");
}

void LayerLogin::menuItemCallbackLogin(Ref* pSender)
{
    if(strcmp(editBoxUsername->getText(), "")&&strcmp(editBoxPassword->getText(), ""))
    {
        const char  *  userName=editBoxUsername->getText();
        const char *   password=editBoxPassword->getText();
        int i=0,j=0,uIllegal=0,pIllegal=0;
        while((userName[i]!='\0'))
        {
            if((userName[i]>='0'&&userName[i]<='9')||(userName[i]>='a'&&userName[i]<='z')||(userName[i]>='A'&&userName[i]<='Z'))
            {
                i++;
                continue;
            }
            else
            {
                i++;
                uIllegal++;
            }
        }
        while(password[j]!='\0')
        {
            if((password[j]>='0'&&password[j]<='9')||(password[j]>='a'&&password[j]<='z')||(password[j]>='A'&&password[j]<='Z'))
            {
                j++;
                continue;
            }
            else
            {
                j++;
                pIllegal++;
            }
        }
        if(uIllegal>0||pIllegal>0)
        {
            CustomPop::show("用户名或密码包含非法字符!~");
        }
        else
        {
            load=Loading::create();
            addChild(load,9999);
          
            Json::FastWriter  writer;
            Json::Value person;
            person["login"]=userName;
            person["psw"]=password;
           // std::string  json_file=writer.write(person);
           // log("%s",json_file.c_str());
            
            SocketManager::getInstance()->sendMessage(person, 101);
            this->schedule(schedule_selector(LayerLogin::receiveLoginData), 0.2);
        }
    }
    else
    {
        CustomPop::show("帐号或密码不能为空！~");
    }
}
void LayerLogin::receiveLoginData(float dt){
    Message* revMsg2 = (Message *)CData::getCData()->m_dictionary->objectForKey(101);
    CData::getCData()->m_dictionary->removeObjectForKey(101);

    if(revMsg2){
        
        
        this->unschedule(schedule_selector(LayerLogin::receiveLoginData));
        
        const char * denglu=revMsg2->data;
        log("%s",denglu);
        CData::getCData()->setSendVal(denglu1);
        rapidjson::Document d;
        rapidjson::Value data;
        int type;
        bool result;
        if(denglu){
            d.Parse<rapidjson::kParseDefaultFlags>(denglu);
            data = d["data"];
            type = d["type"].GetInt();
            result = d["ok"].GetBool();
            if (result){
                
                int userId = data["userId"].GetInt();
                std::string name=data["name"].GetString();
                
                if(type > 0)
                {
                    //CData::getCData()->setCharactorId(data["characterId"].asInt());
                    CData::getCData()->setUserId(userId);
//                    if(hasRole)
//                    {
//                        CData::getCData()->setfirstLogin(2);
//                        this->schedule(schedule_selector(LayerLogin::sendPersonalData), 0.2);
//                    }
//                    else
//                    {
                        CData::getCData()->setfirstLogin(1);
                        Scene *scene=Scene::create();
                        Layer *slayer=startAnimate::create();
                        scene->addChild(slayer);
                        load->removeFromParent();
                        Director::getInstance()->replaceScene(scene);
//                    }
                }
                else
                {
                    CustomPop::show(denglu);
                    load->removeFromParent();
                }
 
            }
            
        }
    }
}

void LayerLogin::sendPersonalData(){
    
}
/*
void LayerLogin::sendPersonalData(){
    this->unschedule(schedule_selector(LayerLogin::sendPersonalData));
    
    this->schedule(schedule_selector(LayerLogin::receivePersonalData), 0.2);
    Json::FastWriter  write;
    
    Json::Value person1;
    
    person1["userId"]= CData::getCData()->getUserId();
    person1["characterId"]=CData::getCData()->getCharactorId();
    
    std::string  json_file1=write.write(person1);
    
    SocketManager::getInstance()->sendMessage(json_file1.c_str(), 103);
    
    
    Json::Value citymsg;
    citymsg["userId"] = CData::getCData()->getUserId();
    citymsg["characterId"] = CData::getCData()->getCharactorId();
    citymsg["index"] = 0;
    std::string json_file_city = write.write(citymsg);

    return;
    
    SocketManager::getInstance()->sendMessage(json_file_city.c_str(), 4500);
    
    
    this->schedule(schedule_selector(LayerLogin::receiveCityData), 0.2);
    
    
}
*/

void LayerLogin::receiveCityData(float dt)
{
    
    Message* msg = (Message*)CData::getCData()->m_dictionary->objectForKey(4500);
    CData::getCData()->m_dictionary->removeObjectForKey(4500);
    if(msg)
    {
        this->unschedule(schedule_selector(LayerLogin::receiveCityData));
       // CData::getCData()->cityData = msg->data;
        printf("%s\n",CData::getCData()->cityData);
        
        this->schedule(schedule_selector(LayerLogin::receivePersonalData), 0.2);
    }
    
}


void LayerLogin::receivePersonalData(float dt){
    
    Message* revMsg1 = (Message *)CData::getCData()->m_dictionary->objectForKey(103);
    CData::getCData()->m_dictionary->removeObjectForKey(103);
    if(revMsg1){
        this->unschedule(schedule_selector(LayerLogin::receivePersonalData));
        denglu1=revMsg1->data;
        
//      CData::getCData()->setSendVal(denglu1);
        log("------%s\n",denglu1);
        pSpriteDialogLogin->removeFromParent();
        url1->setVisible(false);
        url2->setVisible(false);
        load->removeFromParent();
        
        MenuItemImage *pMenuItemStart = MenuItemImage::create();
        pMenuItemStart->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("login_start_1.png"));
        pMenuItemStart->setSelectedSpriteFrame(CCSpriteFrameCache::getInstance()->getSpriteFrameByName("login_start_2.png"));
        pMenuItemStart->setTarget(this, SEL_MenuHandler(&LayerLogin::menuItemCallbackStart));
        Menu *pMenu = Menu::create(pMenuItemStart,NULL);
        this->addChild(pMenu,2);
        Size winSize = Director::getInstance()->getWinSize();
        pMenu->setPosition(winSize.width/2, 180);
        
    }
}
void LayerLogin::removeLoader(){
}


void LayerLogin::menuItemCallbackStart(Ref *pSender)
{   
    log("start");
    
    Scene *container=CCScene::create();//homepage  beginAni
    homePage * homePage = homePage::create();
    container->addChild(homePage);
    Director::getInstance()->replaceScene(CCTransitionFade::create(2, container));

    
}
void LayerLogin::menuItemCallbackSelector(Ref *pSender)
{
    
}

