#ifndef __wx__LevelMap__
#define __wx__LevelMap__

#include <iostream>

#include "cocos2d.h"

#include "popwindow.h"
#include "CData.h"

USING_NS_CC;
using namespace std;

class LevelMap:public Layer
{
public:
    CREATE_FUNC(LevelMap);
    
private:
    
    ~LevelMap();
    virtual bool init();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchMoved(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
    
    
    void adjustMap(bool isResetLevel);
    
    void clkBuilding(Ref * building);
    
    Size size;
    Sprite* mapSp;
    Sprite* mapLayer;
    
    Point startP;
    Point movingP;
    Point endP;
    Point distanceP;
    
    double offsetY;
    
    Menu* levelsMenu;
    bool isTouchMenu;
    
    int currentLevelId;
    
    
    int currentMap;
    int mapNum;
    
    Map<int, MenuItemSprite *> levelSpDic;
    
    buildingpop* buildpop;
    
    rapidjson::Value data;
};

#endif /* defined(__wx__LevelMap__) */
