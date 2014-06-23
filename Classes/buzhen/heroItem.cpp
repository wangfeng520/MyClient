 #include "heroItem.h"

#include "CData.h"
bool heroItem::init()
{
    
    if (!Sprite::init()) {
        return false;
    }
    
   
    itemdata = NULL;
    
    bkg = Sprite::create("common_item_bkg1.png");
    bkg->setAnchorPoint(Point(0, 0));
    this->addChild(bkg);
    
    this->setContentSize(bkg->getContentSize());
    
    
    return true;
}



void heroItem::setData(heroItemData *obj)
{
    bkg->removeChild(datasp,true);
    bkg->removeChild(qualitybkg, true);
    
    itemdata = obj;
    if(itemdata == NULL)
    {
        return;
    }
    
    qualitybkg = Sprite::create();
    
    if (itemdata->tpid == 1 || itemdata->tpid == 2)//主公 好友 特殊处理
    {
        if(itemdata->tempid == 1)
        {
            datasp = Sprite::create("qs_0001.png");
        }
        else if(itemdata->tempid == 2)
        {
            datasp = Sprite::create("qs_0002.png");
        }
        else
        {
            datasp = Sprite::create("qs_0003.png");
        }
 
        qualitybkg->create("common_qs_bkg_4.png");
//        qualitybkg->initWithFile("common_qs_bkg_4.png");
        
    }
    else{
        
        configHeroItem* goodsitem = CData::getCData()->getConfigOfHero(itemdata->tempid);
        
        char itemicon[40]="";
//        sprintf(itemicon, "s_wj_icon_%04d.png",goodsitem->icon);
        
        sprintf(itemicon, "qs_%04d.png",goodsitem->icon);
        datasp = Sprite::create(itemicon);
        switch (goodsitem->baseQuality) {
            case 1:
                qualitybkg->create("common_qs_bkg_1.png");
                break;
            case 2:
                qualitybkg->create("common_qs_bkg_2.png");
                break;
            case 3:
                qualitybkg->create("common_qs_bkg_3.png");
                break;
            case 4:
                qualitybkg->create("common_qs_bkg_4.png");
                break;
                
            default:
                qualitybkg->create("common_qs_bkg_1.png");
                break;
        }
        
    }
    
    Size sz = bkg->getContentSize();

    qualitybkg->setScale(0.5);
    qualitybkg->setPosition(Point(sz.width/2, sz.height/2));
    bkg->addChild(qualitybkg);
    
    
    datasp->setScale(0.19);
    datasp->setPosition(Point(sz.width/2, sz.height/2));
    bkg->addChild(datasp);
    
    
    
}

void heroItem::clData()
{
    setData(NULL);
}

//void heroItem::onExit()
//{
//    CCLog("heroItem onExit");
//}


heroItem::~heroItem()
{
   log("heroItem destroy");
}






