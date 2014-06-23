#include "startAnimate.h"
//#include "xuanren.h"

bool startAnimate::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("guild.plist");
    Size winSize=Director::getInstance()->getWinSize();
    str1=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgk1.png"));
    str1->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(str1);
    
    str2=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("words.png"));
    str2->setPosition(Point(winSize.width/2-60, winSize.height/2+160));
    str2->setVisible(false);
    this->addChild(str2);
    
    str3=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("words1.png"));
    str3->setPosition(Point(winSize.width/2-10, winSize.height/2+90));
    str3->setVisible(false);
    this->addChild(str3);
    
    str4=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgk2.png"));
    str4->setPosition(Point(winSize.width/2, winSize.height/2));
    str4->setVisible(false);
    this->addChild(str4);
    
    str7=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("words2.png"));
    str7->setPosition(Point(winSize.width/2-60, winSize.height/2+160));
    str7->setVisible(false);
    this->addChild(str7);
    
    str5=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgk3.png"));
    str5->setPosition(Point(winSize.width/2, winSize.height/2));
    str5->setVisible(false);
    this->addChild(str5);
    
    str8=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("words3.png"));
    str8->setPosition(Point(winSize.width/2-60, winSize.height/2+160));
    str8->setVisible(false);
    this->addChild(str8);
    
    str6=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgk4.png"));
    str6->setPosition(Point(winSize.width/2, winSize.height/2));
    str6->setVisible(false);
    this->addChild(str6);
    
    CCMenuItemImage *item=CCMenuItemImage::create("start_xr.png", "start_xr1.png", this, SEL_MenuHandler(&startAnimate::callbackSelectRole));
    CCMenu *menu=CCMenu::create();
    menu->addChild(item);
    menu->setPosition(Point(winSize.width/2, 70));
    this->addChild(menu);
    round=0;
    
    ActionInterval *fadein=FadeIn::create(1.5);
    CallFunc * func=CallFunc::create(this, callfunc_selector(startAnimate::animateDesc));
    FiniteTimeAction * final=CCSequence::create(fadein,func,NULL);
    str1->runAction(final);
    
    return true;
}

void startAnimate::kong()
{
    str1->setVisible(true);
}

void startAnimate::animateDesc()
{
    
    if(round==0)
    {
        str2->setVisible(true);
        ActionInterval *fin=FadeIn::create(2);
        str2->runAction(fin);
        ActionInterval *fadeout=FadeOut::create(0.7);
        ActionInterval *delay=CCDelayTime::create(0.7);
        ActionInterval *moveTo=CCMoveTo::create(0.7, Point(str2->getPosition().x, str2->getPosition().y));
        CallFunc * func=CallFunc::create(this, callfunc_selector(startAnimate::animateDesc));
        FiniteTimeAction * final=CCSequence::create(delay,moveTo,fadeout,func,NULL);
        str2->runAction(final);
    }
    else if(round==1)
    {
        ActionInterval * fadeout=FadeOut::create(0.1);
        str3->setVisible(true);
        ActionInterval * delay=CCDelayTime::create(1.5);
        ActionInterval * moveto=CCMoveTo::create(0.7, Point(str3->getPosition().x, str3->getPosition().y));
        CallFunc * func=CallFunc::create(this, callfunc_selector(startAnimate::animateTwo));
        FiniteTimeAction * final=CCSequence::create(delay,moveto,fadeout,func,NULL);
        str3->runAction(final);
    }
    round++;
}

void startAnimate::animateTwo()
{
    FadeOut *out=FadeOut::create(1.0);
    str1->runAction(out);
    str4->setVisible(true);
    ActionInterval *fadein=FadeIn::create(1);
    str4->runAction(fadein);
    
    ActionInterval *fadeout=FadeOut::create(1.5);
    ActionInterval *delay=CCDelayTime::create(1.5);
    str7->setVisible(true);
    ActionInterval *moveTo=CCMoveTo::create(0.7, Point(str7->getPosition().x, str7->getPosition().y));
    CallFunc * func=CallFunc::create(this, callfunc_selector(startAnimate::animateThree));
    FiniteTimeAction * final=CCSequence::create(delay,moveTo,fadeout,func,NULL);
    str7->runAction(final);
    
}

void startAnimate::animateThree()
{
    FadeOut *out=FadeOut::create(1.0);
    str4->runAction(out);
    str5->setVisible(true);
    FadeIn *fadein=FadeIn::create(2.5);
    str5->runAction(fadein);
    str8->setVisible(true);
    FadeIn *in=FadeIn::create(1.0);
    str8->runAction(in);
    ActionInterval * fadeout=FadeOut::create(2);
    ActionInterval * delay=CCDelayTime::create(1.5);
    
    CallFunc * func=CallFunc::create(this, callfunc_selector(startAnimate::animateFour));
    FiniteTimeAction * final=CCSequence::create(delay,fadeout,func,NULL);
    str8->runAction(final);
}

void startAnimate::animateFour()
{
    FadeOut *out=FadeOut::create(2.0);
    str5->runAction(out);
    str6->setVisible(true);
    FadeIn *fadein=FadeIn::create(1.0);
    str6->runAction(fadein);
    //    FadeOut *fadeout=FadeOut::create(2.5);
    //    ActionInterval *delay=CCDelayTime::create(2);
    // auto *func=CallFunc::create(CC_CALLBACK_0(startAnimate::callbackSelectRole, this));
    //  FiniteTimeAction *final=CCSequence::create(delay,fadeout,func,NULL);
    //    str6->runAction(final);
}

void startAnimate::callbackSelectRole(Ref *pSender)
{
    //    CCScene *scene=CCScene::create();
    //    CCLayer *xr=xuanren::create();
    //    scene->addChild(xr);
    //    Director::sharedDirector()->replaceScene(scene);
}

startAnimate::~startAnimate()
{
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("guild.plist");
    Director::getInstance()->getTextureCache()->removeTextureForKey("guild.png");
}
