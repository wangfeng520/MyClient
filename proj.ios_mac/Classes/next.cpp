
#include "next.h"
#include "FireWork.h"
bool nextLayer::init(){
    if(!LayerColor::initWithColor(Color4B(0, 0, 0, 100))){
        return false;
    }
    setTouchEnabled(true);
    return true;
}


bool nextLayer::onTouchBegan(Touch* touch, Event* event){
    return true;
}
void nextLayer::onTouchMoved(Touch* touch, Event* event){
    
}
void nextLayer::onTouchEnded(Touch* touch, Event* event){
    log("sdfqwe");
    Fire * fir=(Fire *)this->getParent();
    fir->nextchat();
}