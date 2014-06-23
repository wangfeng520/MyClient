#include "LevelMap.h"

#include "CustomPop.h"

LevelMap::~LevelMap()
{
    log("LevelMap destroy");
}

bool LevelMap::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    this->setTouchEnabled(true);
    

    currentMap = 0;
    
    size = Director::getInstance()->getWinSize();
    mapLayer = Sprite::create();
    
    
    Sprite* m1 = Sprite::create("map3.png");
    m1->setAnchorPoint(Point(0, 0));
    m1->setPosition(Point(0, 0));
    
    Sprite* m2 = Sprite::create("map1.png");
    m2->setAnchorPoint(Point(0, 0));
    m2->setPosition(Point(0, 441));
    
    Sprite* m3 = Sprite::create("map2.png");
    m3->setAnchorPoint(Point(0, 0));
    m3->setPosition(Point(0, 441*2));
    
    Sprite* m4 = Sprite::create("map3.png");
    m4->setAnchorPoint(Point(0, 0));
    m4->setPosition(Point(0, 441*3));
    
    Sprite* m5 = Sprite::create("map1.png");
    m5->setAnchorPoint(Point(0, 0));
    m5->setPosition(Point(0, 441*4));
    
    
    mapLayer->addChild(m1);
    mapLayer->addChild(m2);
    mapLayer->addChild(m3);
    mapLayer->addChild(m4);
    mapLayer->addChild(m5);
    mapLayer->setAnchorPoint(Point(0, 0));
    mapLayer->setPosition(Point(0, 0));
    
    mapSp = Sprite::create();
    mapSp->addChild(mapLayer);
    mapSp->setAnchorPoint(Point(0, 0));
    mapSp->setPosition(Point(0, 0));
    this->addChild(mapSp);
    
    
    levelsMenu = Menu::create();
    levelsMenu->setAnchorPoint(Point(0, 0));
    levelsMenu->setPosition(Point(0, 0));
    this->addChild(levelsMenu);
    
    Sprite* bkg = Sprite::create("zjm_bkg.png");
    bkg->setAnchorPoint(Point(0, 0));
    bkg->setPosition(Point(0, 0));
    this->addChild(bkg);
    
    
    for (int i = 0; i < 9; i++)
    {
        auto *leveltmp = MenuItemImage::create("zjm_building_1.png",
                                               "zjm_building_2.png",
                                               "zjm_building_2.png",
                                               this, menu_selector(LevelMap::clkBuilding));
                                               //CC_CALLBACK_1(LevelMap::clkBuilding, this));
        
        int num = floor(i/3);
        
        leveltmp->setPosition(Point((i-3*num)%2==1?140:size.width-130, (130)*(i%3) + 442*(int)floor(i/3) +240));//160
        levelSpDic.insert(i, leveltmp);
        levelsMenu->addChild(leveltmp);
        
        
        const Color3B color3 = {255,175,100};
        const Color3B colorbg = {255,175,51};
        
        Size tmpsz = leveltmp->getContentSize();
        
        Label * name11=Label::create("", "hy.ttf", 20);
        name11->setDimensions(200, 0);
        name11->setHorizontalAlignment(TextHAlignment::CENTER);
        name11->setVerticalAlignment(TextVAlignment::TOP);
        name11->setPosition(Point(tmpsz.width/2-1, 35));
        
        name11->setColor(colorbg);
       // leveltmp->addChild(name11);
        leveltmp->addChild(name11, 10);
        
        name11->setTag(1002);
        
    }
    
    
    
        char * json=CData::getCData()->cityData;
        //Json::Reader read;
        //Json::Value  root;
//        rapidjson::Reader reader;
//        rapidjson::Value root;
    
//    
//        if(read.parse(json, root))
//        {
//            data=root["data"];
//        }
//        if(reader.Parse<rapidjson::kParseDefaultFlags>(json, root)){
//            data=root["data"];
//        };
    
//        currentLevelId = data["cityid"].GetInt();
//    
//        if (CData::getCData()->levelMapOffsetY > 0)
//        {
//            offsetY = -((int)ceil((currentLevelId-1000)/3))*442;
//            //size.height;
//        }
//        else
//        {
//            offsetY = CData::getCData()->levelMapOffsetY;
//        }
//    
//    
//        //    offsetY = 0;
//    
//    
//        mapNum = CData::getCData()->getLevelMapNum();
//    
    
    adjustMap(true);
    
    return true;
}

void LevelMap::clkBuilding(Ref *building)
{
    MenuItemSprite* b = (MenuItemSprite* )building;
    
    MapItem *item = (MapItem*)b->getUserObject();
    
    if(item == NULL)
    {
        CustomPop::show("关卡信息为空！");
        return;
    }
    
    buildpop = buildingpop ::create();
    buildpop->setPosition(0,0);
    
    this->getParent()->addChild(buildpop,100);
    buildpop->show(item);
    
}

bool LevelMap::onTouchBegan(Touch *touch, Event *event)
{
    
    
    startP =  convertTouchToNodeSpace(touch);
    
    isTouchMenu=levelsMenu->onTouchBegan(touch, event);
    
    Point touchPoint = convertTouchToNodeSpace(touch);
    
    
    if (touchPoint.y < 80 || touchPoint.y > size.height - 180) {
        return false;
    }
    
    return true;
}

void LevelMap::onTouchMoved(Touch *touch, Event *event)
{
    
    movingP = convertTouchToNodeSpace(touch);
    distanceP = movingP - startP;
    log("移动%f,%f",distanceP.x, distanceP.y);
    Point tmpP = mapLayer->getPosition();
    
    if(offsetY + distanceP.y > 0)
    {
        
        offsetY = 0;
        CData::getCData()->levelMapOffsetY = offsetY;
    }
    else if (offsetY + distanceP.y < -442*(mapNum-1))
    {
        
        offsetY =  -442*(mapNum-1);
        CData::getCData()->levelMapOffsetY = offsetY;
    }
    else
    {
        offsetY +=  distanceP.y;
        CData::getCData()->levelMapOffsetY = offsetY;
    }
    adjustMap(true);
    startP = movingP;
    
    if(isTouchMenu){
        
        levelsMenu->onTouchMoved(touch, event);
    }
}

void LevelMap::onTouchEnded(Touch *touch, Event *event)
{
    
    
    
    if (isTouchMenu) {
        levelsMenu->onTouchEnded(touch, event);
        
        isTouchMenu=false;
        
    }
    
    
    adjustMap(true);
    
}

void LevelMap::adjustMap(bool isResetLevel)
{
    int num = floor(offsetY/442);
    
    currentMap = -num;
    
    int offnum = num%3;
    float tmpoff = offsetY - num*442;
    mapLayer->setPosition(Point(0, (offnum-1)*442 + tmpoff));
    
    if(isResetLevel)
    {
        
        int offlevel = 1000 + currentMap*3 -3;
        
        for (int i = 0; i < 9 ; i++)
        {
            MapItem* tmpLevelItemData = new MapItem();
//            //            item->autorelease();
//            tmpLevelItemData->nickname = "测试";
//            tmpLevelItemData->desc = "打败佣兵向我们证明你的实力";
//            tmpLevelItemData->bid = 1000;
//            tmpLevelItemData->exp = 124;
//            tmpLevelItemData->coin = 248;
            
            tmpLevelItemData = CData::getCData()->getConfigOfMapLevel(offlevel + i);
            
            
            MenuItemSprite* tmp = (MenuItemSprite*)levelSpDic.at(i);
            tmp->removeChildByTag(9999);
            
            if (tmpLevelItemData!= NULL )//&& tmpLevelItemData->bid < currentLevelId)
            {
                Size tmpsz = tmp->getContentSize();
                Sprite* ssp = Sprite::create();
                
//                int num = data["citylist"][tmpLevelItemData->bid - 1000].GetInt();
                for (int k = 0; k<3; k++)
                {
                    Sprite * star = Sprite::create("zjm_star.png");
                    star->setPosition(Point(k*30, 0));
                    ssp->addChild(star);
                    
                }
                ssp->setPosition(Point(tmpsz.width/2-15*num+15, 0));
                ssp->setTag(9999);
                tmp->addChild(ssp, 0);
            }
          
            if(tmpLevelItemData != NULL)
            {
                
                if(tmpLevelItemData->bid > currentLevelId)
                {
                    tmp->setEnabled(false);
                }
                else
                {
                    tmp->setEnabled(true);
                }
                
                tmp->setUserObject(tmpLevelItemData);
                
            }
//            
//            for (int j = 1001; j<=1005; j++)
//            {
                Label* tmpName = (Label*)(tmp->getChildByTag(1002));
//                LabelTTF* tmpName = (LabelTTF*)(tmp->getChildByTag(1002));
                if(tmpLevelItemData)
                {
                    string temp = tmpLevelItemData->nickname.c_str();
                    log("%s", temp.c_str());
                    tmpName->setString(temp.c_str());
 
                }
//            }
            
            
        }
        
    }
    
    levelsMenu->setPosition(Point(0, -442 + tmpoff));
    
}



