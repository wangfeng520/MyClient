
#include "CustomPop.h"
#include <limits>

static CustomPop* pop = NULL;
CustomPop ::CustomPop(){
    
}

bool CustomPop::init(){
    if(!LayerColor::initWithColor(Color4B(0, 0, 0, 180))){
        return false;
    }
    
    setTouchEnabled(true);
    
    
    Size size=Director::getInstance()->getWinSize();
    this->setContentSize(size);
    
    
    Sprite *bkg = Sprite::create("common_pop_bkg.png");
    bkg->setPosition(Point(size.width/2, size.height/2)); 
    this->addChild(bkg);
    Size sz = bkg->getContentSize();
    
    Color3B black1 = Color3B(236, 190, 108);
    Color3B black = Color3B(27, 18, 6);
    
    Label* title = Label::create("提  示", "hycc.ttf", 28);
    title->setColor(black);
    title->setAnchorPoint(Point(0.5, 1));
    title->setPosition(Point(sz.width/2+1, sz.height-23));
    bkg->addChild(title);
    Label* title1 = Label::create("提  示", "hycc.ttf", 28);
    title1->setColor(black1);
    title1->setAnchorPoint(Point(0.5, 1));
    title1->setPosition(Point(sz.width/2, sz.height-22));
    bkg->addChild(title1);
    
    desc = Label::create("消 除", "hycc.ttf", 25); //, Size(400, 0), kCCTextAlignmentCenter);
    
    desc->setColor(black);
//    desc->setAnchorPoint(Point(0.5, 1));
    desc->setPosition(Point(sz.width/2, sz.height/2+10));
    bkg->addChild(desc);
    
    auto closeItem = MenuItemImage::create(
                                           "common_btn_ok_1.png",
                                           "common_btn_ok_2.png",
                                           CC_CALLBACK_0(CustomPop::close, this));
    
    
    auto *bz = MenuItemImage::create(
                                           "common_btn_ok_1.png",
                                           "common_btn_ok_2.png",
                                           CC_CALLBACK_0(CustomPop::close, this));
    
//    MenuItemImage* bz = MenuItemImage::create("common_btn_ok_1.png", "common_btn_ok_2.png", this, menu_selector(CustomPop::close));
//    bz->setAnchorPoint(Point(0,0));
    
  //  bz->setPosition(Point(sz.width/2, 30));
    bz->setScale(1.3);
    
    btnsMenu = Menu::create(bz, NULL);
    btnsMenu->setPosition(Point(sz.width/2,80));
    
    bkg->addChild(btnsMenu);
//    bkg->addChild(closeItem);

    return true;
}

void CustomPop::show(const char* str)
{
    if(pop == NULL)
    {
        pop = CustomPop::create();
    }
    
    Director::getInstance()->getRunningScene()->addChild(pop);
    pop->desc->setString(str);
}

void CustomPop::close()
{
//    Director::getInstance()->~Director();
    pop->removeFromParentAndCleanup(true);
    pop=NULL;
    
}

CustomPop::~CustomPop()
{
    
    log("CustomPop destroy");

}



bool CustomPop::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    istouch=btnsMenu->onTouchBegan(touch, event);
    
    // 因为回调调不到了，所以resume写在了这里
    //   CCLog("loading layer");
    return true;
}

void CustomPop::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(istouch){
        
        btnsMenu->onTouchMoved(touch, event);
    }
}
void CustomPop::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    if (istouch) {
        btnsMenu->onTouchEnded(touch, event);
        
        istouch=false;
        
    }
}
