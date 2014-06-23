#ifndef Client_LayerLogin_h
#define Client_LayerLogin_h
#include"cocos2d.h"
#include"cocos-ext.h"
#include "SocketClient.h"
#include "CData.h"
#include "LoadingLayer.h"
#include "TeXiao.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;
using namespace rapidjson;

class LayerLogin:public Layer
{
    
public:
    
    CREATE_FUNC(LayerLogin);
    virtual bool init();
    virtual void onExit();
    ~LayerLogin();
    
    Sprite * texiao;
    bool hasRole;
    Loading * load;

    Sprite * logo;
    Size winSize;
    
    const char * denglu1;
    
    void removeLoader();
   
    void receiveLoginData(float dt);
    void sendPersonalData();
    void receivePersonalData(float dt);
    
    void receiveCityData(float dt);
    void jiumiaoshanyou();
    void firefly();
    void callNull1();
    void callNull2();
    void zhenping();
    const char * sendData;
private:
    
    void initUI();
    void loadRes();
    
    // bool init();
   
    void menuItemCallbackLogin(Ref* pSender);
    void menuItemCallbackStart(Ref* pSender);
    void menuItemCallbackSelector(Ref* pSender);
       
    //CCLabelTTF *label1;
    //CCLabelTTF *label2;
    MenuItemImage *url1,*url2;
    Sprite *pSpriteDialogLogin;
    EditBox* editBoxUsername;
    EditBox* editBoxPassword;
    
};
#endif
