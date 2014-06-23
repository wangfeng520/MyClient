#include "CData.h"
//#include "CCFileUtils.h"
#include "SimpleAudioEngine.h"
static CData *cdata;
CData::CData()
{
    selectwjID=0;
    m_tunshi_dic=CCDictionary::create();
    m_tunshi_dic->retain();
    m_dictionary = cocos2d::CCDictionary::create();
    m_dictionary->retain();
    m_newlevel_dic=CCDictionary::create();
    m_newlevel_dic->retain();
    
    m_config_goods_dic = CCDictionary::create();
    m_config_goods_dic->retain();
    
    //    m_config_hero_dic = CCDictionary::create();
    //    m_config_hero_dic->retain();
    //
    //    m_config_monster_dic = CCDictionary::create();
    //    m_config_monster_dic->retain();
    //
    //    m_config_map_level_dic = CCDictionary::create();
    //    m_config_map_level_dic->retain();
    
    index=0;
    JH=0;
    is_yy = true;
    is_yx = true;
    battleCityId = -1;
    levelMapOffsetY = 1;
    isArenaFire = false;
    
}
void CData::writeFile(std::string filename, std::string value)
{
    std::string Background = value;
    const char * groundName = Background.c_str();
    std::string doPath = "";//CCFileUtils::sharedFileUtils()->getWriteablePath();
    std::string filenamea = filename;
    std::string filepath = doPath + filename;
    FILE *fp = fopen(filepath.c_str(),"w");
    fputs(groundName,fp);
    fclose(fp);
}
void CData::setmidindex(int mid){
    _mid=mid;
}
int CData::getmidindex(){
    return _mid;
}
//根据关键字读取手机中的内容
std::string CData::readFile(std::string filename)
{
    std::string doPath ="";// CCFileUtils::sharedFileUtils()->getWriteablePath();
    std::string filenamea = filename;
    std::string filepath = doPath + filename;
    FILE *fp1 = fopen(filepath.c_str(),"r");
    char* pchBuf = NULL;
    
    int len = 0;
    if (fp1 == NULL) {
        return "nologin";
    }
    fseek(fp1 , 0, SEEK_END);
    len = ftell(fp1);
    
    rewind(fp1);
    pchBuf = (char*)malloc(sizeof(char)*len+1);
    
    if (!pchBuf)
        
    {
        //        CCLOG("内存不够!\n");
        exit(0);
    }
    
    len = fread(pchBuf,sizeof(char),len,fp1);
    pchBuf[len] = '\0';
    std::string getground = pchBuf;
    fclose(fp1);
    free(pchBuf);
    
    std::stringstream ss(getground);
    std::string pucter;
    //    std::string aaaaaa = "6";
    for (int i=0 ;i < 1 ;i++)
    {
        getline(ss,pucter,',');
    }
    return pucter.c_str() ;
    
}
void CData::setChatFlag(bool flag){
    _chatFlag=flag;
}
bool CData::getChatFlag(){
    return _chatFlag;
}
void CData::setczorzy(bool flag){
    _flag=flag;
}
void CData::setSZnum(int level){
    if(level>=1&&level<3){
        _sznum=1;
    }else if(level>=3&&level<5){
        _sznum=2;
    }else if(level>=5&&level<10){
        _sznum=3;
    }else if(level>=10&&level<15){
        _sznum=4;
    }else if(level>=15&&level<20){
        _sznum=5;
    }else if(level>=20&&level<25){
        _sznum=6;
    }else if(level>=25&&level<30){
        _sznum=7;
    }else if(level>=30&&level<=100){
        _sznum=8;
    }
    
}
int CData::backSZnum(){
    return _sznum;
}
bool CData::getczorzy(){
    return _flag;
}

CData* CData::getCData()
{
    if(!cdata)
        cdata = new CData();
    
    return cdata;
}
void CData::setdata(char *data)
{
    this->data = data;
}
void CData::setZGBagInfo(const char *str){
    zgjson=str;
    
}

configMonsterItem* CData::getConfigOfMonster(int tempid)
{
    rapidjson::Document d2;
    if(m_config_monster_dic.size() < 1)
    {
        
        rapidjson::Value items;
        rapidjson::Reader reader;
        rapidjson::Value root;
        
        rapidjson::Value::MemberIterator it;
        
        //        std::string data=FileUtils::getInstance()->getStringFromFile("monster.json");
        //        d2.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
        string path = FileUtils::getInstance()->fullPathForFilename("monster.json");
        string content = FileUtils::getInstance()->getStringFromFile(path.c_str());
        d2.Parse<rapidjson::kParseDefaultFlags>(content.c_str());
        
      //  reader.Parse<rapidjson::kParseDefaultFlags>(content, root);
//        rapidjson::Value &d=d2[SizeType(0)].onBegin();
        int i = 0;
        for (rapidjson::Value::ConstMemberIterator itr = d2.MemberonBegin(); itr != d2.MemberonEnd(); ++itr){
             printf("Type of member %s \n", itr->name.GetString());
           
            printf("Type of member %s \n", itr->value["nickname"].GetString());
//        }
//        
//        for(unsigned int i=0;i< 5;i++)
//        {
            
//            if (v.HasMember("nickname")){
//                
//            }
//            
            configMonsterItem * item= new configMonsterItem();
            char inttostr[20]="";
            sprintf(inttostr, "%d",tempid);
            
            item->id = itr->value["id"].GetInt();
            item->nickname =itr->value["nickname"].GetString();//" : "蛮夷邪士",
            m_config_monster_dic.insert(item->id, item);
//
        //    it++;
            
        }
        
    }
    
    
    return (configMonsterItem*)m_config_monster_dic.at(tempid);
    
}

configHeroItem*  CData::getConfigOfHero(int tempid)
{
    rapidjson::Document d2;
    if(m_config_hero_dic.size() < 1)
    {
        //   const char * path=CCFileUtils::sharedFileUtils()->fullPathForFilename("hero.json").c_str();
        //        ifstream ifs;
        //        ifs.open(path);
        //        assert(ifs.is_open());
        rapidjson::Value items;
        
        rapidjson::Value::MemberIterator it;
        
        std::string data=FileUtils::getInstance()->getStringFromFile("hero.json");
        d2.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
        
//        //判断读取成功与否 和 是否为数组类型
//        if (d2.HasParseError() || !d2.IsArray())
//        {
//            log("hero get json data err!");
//            return false;
//        }
        
        for(unsigned int i=0;i<d2.Size();i++)
        {
            rapidjson::Value &v=d2[i];
            
            configHeroItem * item= new configHeroItem();
            char inttostr[20]="";
            sprintf(inttostr, "%d",tempid);
            
            item->DexGrowth = v[A2U("DexGrowth")].GetInt();//" : 970,
            item->StrGrowth = v[A2U("StrGrowth")].GetInt();//" : 2925,
            item->VitGrowth = v[A2U("VitGrowth")].GetInt();//" : 2100,
            item->WisGrowth = v[A2U("WisGrowth")].GetInt();//" : 1026,
            item->attrType = v[A2U("attrType")].GetInt();//" : 3,
            item->baseQuality = v[A2U("baseQuality")].GetInt();//" : 5,
            item->coin = v[A2U("coin")].GetInt();//" : 50000,
            item->descript = v[A2U("descript")].GetString();//" : "会释放邪恶法术的士兵，攻击力较高防御较低，擅长远程群体攻击。",
            item->icon = v[A2U("icon")].GetInt();//" : 378,
            item->id = v[A2U("id")].GetInt();// : 35107,
            item->level = v[A2U("level")].GetInt();//" : 103,
            item->nickname = v[A2U("nickname")].GetString();//" : "蛮夷邪士",
            item->ordSkill = v[A2U("ordSkill")].GetInt();//" : 5107,
            item->resourceid = v[A2U("resourceid")].GetInt();//" : 5107,
            item->skill = v[A2U("skill")].GetInt();//" : 710303,
            item->soulcount = v[A2U("soulcount")].GetInt();//" : 100,
            item->soulrequired = v[A2U("soulrequired")].GetInt();//" : 41004094,
            item->type = v[A2U("type")].GetInt();//" : 220000,
            item->xy = v[A2U("xy")].GetInt();//" : -1
            
            m_config_hero_dic.insert(item->id, item);
            
            //                item->bodytype=items["bodyType")].GetInt();
            //                item->name=items["name")].GetString();
            //                item->pinzhi=items["baseQuality")].GetInt();
            //                item->des=items["description")].GetString();
            //                item->tempid = items["id")].GetInt();
            //                item->bodytype = items["bodytype")].GetInt();
            //
            //                m_config_goods_dic->setObject(item, item->tempid);
            
            it++;
            
            
            //            ifs.close();
            
        }
        
    }
    
    
    return (configHeroItem*)m_config_hero_dic.at(tempid);
    
}

int CData::getLevelMapNum()
{
    if(m_config_map_level_dic.size() <1)
    {
        getConfigOfMapLevel(1000);
    }
    
    int num = ceil(( m_config_map_level_dic.size() )/3);
    
    return num;
}

MapItem* CData::getConfigOfMapLevel(int levelid)
{
    
    if(m_config_map_level_dic.size()<1)
    {
        rapidjson::Document d2;
        rapidjson::Value items;
        rapidjson::Value data;
        rapidjson::Value list;
        rapidjson::Reader reader;
        rapidjson::Value root;
        
        string path = FileUtils::getInstance()->fullPathForFilename("map.json");
        string content = FileUtils::getInstance()->getStringFromFile(path.c_str());
        int sz = 0;
        
        
        d2.Parse<rapidjson::kParseDefaultFlags>(content.c_str());
        rapidjson::Value &v=d2["data"];
        data = v;
        sz = data.Size();
        
        
        for (int i = 0; i < sz; i++) {
            
            
            MapItem *item = new MapItem();
            //            item->autorelease();
            item->nickname = data[i][("name")].GetString();
            item->desc = data[i]["desc"].GetString();
            item->bid = data[i]["id"].GetInt();
            item->exp = data[i]["exp"].GetInt();
            item->coin = data[i]["coin"].GetInt();
            //  item->itemId = root[i]["dropicon")].GetInt();
            
            
            
            list = data[i]["mconfig"];
            // CCDictionary* dic = CCDictionary::create();
            Map<string, configMonsterItem*> map;
            
            int  len =list.Size();
            for (int ei = 0; ei < len; ei++)
            {
                int iiiiid = list[ei].GetInt();
                configMonsterItem* hitem =   CData::getCData()->getConfigOfMonster(iiiiid);
                if(hitem != NULL)
                {
                    map.insert(hitem->nickname, hitem);
                    
                }
                else{
                    char iii[100] = "";
                    sprintf(iii, "怪物id不存在  %d",iiiiid);
                    //    log(iii);
                }
                
            }
            
            char chars[500] = "";
            
            //                int how = map.size();
            //                Vector<string*> arr = map->ge
            //                // Array* arr = dic->allKeys();
            //                switch (how) {
            //                    case 1:
            //                        sprintf(chars, "【%s】",((char *)(arr.at(0))));
            //                        break;
            //                    case 2:
            //                        sprintf(chars, "【%s】\n【%s】",((char*)(arr.at(0))),
            //                                ((char *)(arr.at(1))));
            //                        break;
            //                    case 3:
            //                        sprintf(chars, "【%s】  【%s】\n【%s】",((char*)(arr.at(0))),
            //                                ((char*)(arr.at(1))),
            //                                ((char*)(arr.at(2))));
            //                        break;
            //
            //                    default:
            //                        if(how >= 4)
            //                        {
            //                            sprintf(chars, "【%s】  【%s】\n【%s】  【%s】",((char*)(arr.at(0))),
            //                                    ((char*)(arr.at(1))),
            //                                    ((char*)(arr.at(2))),
            //                                    ((char*)(arr.at(3))));
            //                        }
            //                        break;
            //                }
            
            item->enemydesc = chars;
            
            //log(item->enemydesc.c_str());
            
            
            m_config_map_level_dic.insert(item->bid, item);
        }
        
        
        
    }
    
    return (MapItem*)m_config_map_level_dic.at(levelid);
    
}


configGoodsItem*  CData::getConfigOfGoods(int tempid)
{
    
    //    if(m_config_goods_dic->count() < 1)
    //    {
    //        //        const char * path=CCFileUtils::sharedFileUtils()->fullPathForFilename("itemconfig.json").c_str();
    //        //        ifstream ifs;
    //        //        ifs.open(path);
    //        //        assert(ifs.is_open());
    //        rapidjson::Document d2;
    //        rapidjson::Value items;
    //        rapidjson::Value data;
    //
    //
    //        rapidjson::Value::MemberIterator it;
    //
    //        std::string d=FileUtils::getInstance()->getStringFromFile("item.json");
    //        d2.Parse<rapidjson::kParseDefaultFlags>(d.c_str());
    //
    //        //判断读取成功与否 和 是否为数组类型
    //        if (d2.HasParseError() || !d2.IsArray())
    //        {
    //            log("get json data err!");
    //            return false;
    //        }
    
    //        Json::Reader reader;
    //        Json::Value root;
    //        Json::Value items;
    //
    //        Json::Value::Members members;
    //
    //        //        Json::Value::iterator it;
    //        Json::Value::Members::iterator it;
    
    //        string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("item.json");
    //        std::string* str = String::createWithContentsOfFile(path.c_str());
    
    //        for(unsigned int i=0;i<d2.Size();i++)
    //        {
    //            rapidjson::Value &v=d2[i];
    //            it = v->be;
    //            while (it != members.end()) {
    //
    //                items = root[std::string(*it)];
    //
    //                configGoodsItem * item= new configGoodsItem();
    //                char inttostr[20]="";
    //                sprintf(inttostr, "%d",tempid);
    //
    //                item->bodytype=items["bodyType")].GetInt();
    //                item->name=items["name")].GetString();
    //                item->pinzhi=items["baseQuality")].GetInt();
    //                item->des=items["description")].GetString();
    //                item->tempid = items["id")].GetInt();
    //                item->icon = items["icon")].GetInt();
    //                item->maxexp = items["maxexp")].GetInt();
    //                item->growTemp = items["growTemp")].GetInt();
    //                item->comprice = items["comprice")].GetInt();
    //                item->compound = items["compound")].GetInt();
    //
    //
    //                m_config_goods_dic->setObject(item, item->tempid);
    //
    //                it++;
    //            }
    //
    //            //   ifs.close();
    //
    //        }
    //
    //    }
    //
    
    //    return (configGoodsItem*)m_config_goods_dic->objectForKey(tempid);
    //
}

void CData::setEquipInfo(const char *str)
{
    equipjson = str;
}
void CData::setZGZB(int tag){
    _tag=tag;
}
void CData::setfirstLogin(int login){
    _firstLogin=login;
}
int CData:: getfirstLogin(){
    return _firstLogin;
}
//void CData::sethomepage(){
//
//}
int CData::getZGZB(){
    return _tag;
}
const char * CData::getZGBagInfo(){
    return zgjson;
}
const char * CData::getEquipInfo()
{
    return equipjson;
}
void CData::setFireJson(rapidjson::Value json){
    _json=json;
}
//rapidjson::Value CData::getFireJson(){
//    return _json;
//}
void CData::setFireResult(int result){
    _result=result;
}
int CData::getFireResult(){
    return _result;
}
char* CData::getdata()
{
    return data;
}
void CData::setgold(int gold){
    this->gold=gold;
}
int CData::getgold(){
    return gold;
}
void CData::setcoin(int coin){
    this->coin=coin;
}
int CData::getcoin(){
    return coin;
}
void CData::setExp(int exp){
    this->exp=exp;
}
int CData::getExp(){
    return exp;
}
void CData::setMaxExp(int exp){
    this->maxexp=exp;
}
int CData::getMaxExp(){
    return maxexp;
}
void CData::setLevel(int level){
    this->level=level;
}
int CData::getLevel(){
    return level;
}
void CData::setIndex(int index){
    this->index=index;
}
int CData::getIndex(){
    return index;
}
void CData::setjianghu(cocos2d::Node *jianghu){
    this->JH=jianghu;
}
Node * CData::getjianghu(){
    return JH;
}

void CData::setSendVal(char *val)
{
    sendVal = val;
    
}

int CData::getSex()
{
    
    rapidjson::Document d2;
    rapidjson::Value items;
    rapidjson::Value data;
    rapidjson::Value list;
    
    std::string d=FileUtils::getInstance()->getStringFromFile("monster.json");
    d2.Parse<rapidjson::kParseDefaultFlags>(d.c_str());
    int count = d2.Size();
    
    //    int characterId;
    
    for(unsigned int i=0;i< count;i++)
    {
        rapidjson::Value &v=d2[i];
        data = v["data"].MemberonBegin();
        _sex = data["profession"].GetInt();
        
    }
    
    return _sex;
}

char* CData::getSendVal()
{
    return sendVal;
}

void CData::setyinyue(const char *yinyue)
{
    //    if(readFile("yinyue")=="YES")
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(yinyue, true);
    }
}
void CData::setyinxiao()
{
    //    if(readFile("yinxiao")=="YES")
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("yx.mp3");
    }
}
void CData::setFiremusic(){
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("battleAttacked.mp3");
    }
}
void CData::setTFiremusic(){
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("battleAttack.mp3");
    }
}
void CData::settzyy()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
void CData::setCZ_Fire_data(char *jsondata){
    cz_fire_data=jsondata;
}
char * CData::getCZ_Fire_data(){
    return cz_fire_data;
}
void CData::setCZ_info(char *jsondata){
    cz_info=jsondata;
}
char * CData::getCZ_info(){
    return cz_info;
}


int CData::getCharactorId()
{
    return _charactorId;
}
void CData::setCharactorId(int cid)
{
    _charactorId = cid;
}

int CData::getUserId()
{
    return _userId;
}
void CData::setUserId(int uid)
{
    _userId = uid;
}

