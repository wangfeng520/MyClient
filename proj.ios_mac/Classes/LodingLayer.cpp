//
//  LodingLayer.cpp
//  client1
//
#include "LodingLayer.h"
bool Loading::init(){
    if(!LayerColor::initWithColor(Color4B(0, 0, 0, 100))){
        return false;
    }
    setTouchEnabled(true);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loading.plist");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    Size size=Director::getInstance()->getWinSize();
    
    char str[64] = {0};
    for(int i = 1; i <=12; i++)
    {
        sprintf(str,"load%d.png", i);
        
        SpriteFrame* frame = cache->getSpriteFrameByName(str);

        sf_vec.pushBack(frame);

    }
    animation = Animation::createWithSpriteFrames(sf_vec, 0.1f);
    Sprite *sp=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("load1.png"));
    sp->setPosition(Point(size.width/2, size.height/2));
    this->addChild(sp);
    ActionInterval* action=Animate::create(animation);
    go=RepeatForever::create(action);
    sp->runAction(go);
    go->retain();
    return true;
}

bool Loading::onTouchBegan(Touch *touch, Event *event)
{
    // 因为回调调不到了，所以resume写在了这里
    log("loading layer");
    return true;
}
void Loading::onTouchMoved(Touch *touch, Event *event)
{
    
}
void Loading::onTouchEnded(Touch *touch, Event *event)
{
    
}
Loading::~Loading()
{   
    go->release();
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("loading.plist");
    //CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    TextureCache::getInstance()->removeTextureForKey("loading.png");

}
