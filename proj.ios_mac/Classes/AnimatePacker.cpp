#include "AnimatePacker.h"

class AnimateSaxDelegator : public SAXDelegator
{
public:
	enum{
		STATE_NONE,
		STATE_PLIST,
		STATE_ANIMATION,
		STATE_NAME,
		STATE_DELAY,
		STATE_FLIP_X,
		STATE_FLIP_Y,
		STATE_SPRITE_FRAME
	}state;

	void startElement(void *ctx, const char *name, const char **atts) ;
	void endElement(void *ctx, const char *name) ;
	void textHandler(void *ctx, const char *s, int len) ;

	vector<string> plists;//All plist name
	vector<MyAnimate> animates;//All animate data
};

void AnimateSaxDelegator::startElement( void *ctx, const char *name, const char **atts )
{
	string tag((char*)name);

	if (tag=="plist")
	{
		state=STATE_PLIST;
	} 
	else if (tag=="animation")
	{
		state=STATE_ANIMATION;
        animates.push_back(MyAnimate());
	}
	else if (tag=="name")
	{
		state=STATE_NAME;
	}
	else if (tag=="delay")
	{
		state=STATE_DELAY;
	}
	else if (tag=="spriteFrame")
	{
		state=STATE_SPRITE_FRAME;
	}
	else if (tag=="flipX")
	{
		state=STATE_FLIP_X;
	}
	else if (tag=="flipY")
	{
		state=STATE_FLIP_Y;
	}
	else
	{
		state=STATE_NONE;
	}
}

void AnimateSaxDelegator::endElement( void *ctx, const char *name )
{
	string tag((char*)name);

	if (tag=="plist")
	{
	} 
	else if (tag=="animation")
	{
	}
	else if (tag=="name")
	{
	}
	else if (tag=="delay")
	{
	}
	else if (tag=="spriteFrame")
	{
	}
	else if (tag=="flipX")
	{
	}
	else if (tag=="flipY")
	{
	}
	else
	{
	}

	state = STATE_NONE;
}

void AnimateSaxDelegator::textHandler( void *ctx, const char *ch, int len )
{
	if (state == STATE_NONE)
	{
		return;
	}

	string text((char*)ch,0,len);
	int index;
	float delay;

	switch (state)
	{
	case STATE_PLIST:
		plists.push_back(text);
		break;
	case STATE_ANIMATION:
		break;
	case STATE_NAME:
		index=animates.size()-1;
            
		animates[index].name=text;
		break;
	case STATE_DELAY:
		index=animates.size()-1;
		delay=atof(text.c_str());
		animates[index].delay=delay;
		break;
	case STATE_SPRITE_FRAME:
		index=animates.size()-1;
		animates[index].spriteFrames.push_back(text);
		break;
	case STATE_FLIP_X:
		index=animates.size()-1;
		animates[index].flipX=(text=="true");
		break;
	case STATE_FLIP_Y:
		index=animates.size()-1;
		animates[index].flipY=(text=="true");
		break;
	default:
		break;
	}

}

void AnimatePacker::loadAnimations(const char *path )
{
    string pszPath = FileUtils::getInstance()->fullPathForFilename(path);
    
    
	SAXParser parser;
	AnimateSaxDelegator delegator;

	if (false == parser.init("UTF-8"))
	{
		//TODO
		return;
	}
	parser.setDelegator(&delegator);
	parser.parse(pszPath.c_str());

	//load plist
	vector<string> plists=delegator.plists;
	for (unsigned int i=0;i<plists.size();i++)
	{
	    string plistPath =FileUtils::getInstance()->fullPathFromRelativeFile(plists[i].c_str(), pszPath.c_str());
     
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath.c_str());
        
	}

	//load animate
	vector<MyAnimate> animates=delegator.animates;
//	CCArray *spriteFramesArray = new CCArray();
//    CCArray *spriteFramesArray=CCArray::create();
    Vector<SpriteFrame*> spriteFramesArray;
	set<string> animateNames;
	for (unsigned int i=0;i<animates.size();i++)
	{
		MyAnimate animate=animates[i];
		vector<string> spriteFrames=animate.spriteFrames;
        log("%lu",spriteFrames.size());
		for (unsigned int j=0;j<spriteFrames.size();j++)
		{
			animateNames.insert(spriteFrames[j]);
            log("%s",spriteFrames[j].c_str());
			SpriteFrame *spriteFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrames[j].c_str());
			spriteFramesArray.pushBack(spriteFrame);
		}

        log("%lu",spriteFramesArray.size());
		Animation *animation=Animation::createWithSpriteFrames(spriteFramesArray,animate.delay);
		AnimationCache::getInstance()->addAnimation(animation,animate.name.c_str());

		spriteFramesArray.clear();
	}
	
	//record animate
	for(unsigned int i=0;i<animates.size();i++){
		MyAnimate animate=animates[i];
		nameToAnimateMap[animate.name]=animate;
	}

	//record plist
	pathToPlistsMap[path]=plists;

	//record CCAnimate name
	pathToNameMap[path]=animateNames;
}

Animate* AnimatePacker::getAnimate(const char *name )
{
	Animation* animation=AnimationCache::getInstance()->getAnimation(name);

	if(animation)
	{
		return CCAnimate::create(animation);
	}
	return NULL;
}

void AnimatePacker::freeAnimations(const char *path){
	string pszPath =FileUtils::getInstance()->fullPathForFilename(path);
    //CCFileUtils::fullPathFromRelativePath(path);

	vector<string> plists=pathToPlistsMap[path];
	for (unsigned int i=0;i<plists.size();i++)
	{
	    string plistPath =FileUtils::getInstance()->fullPathFromRelativeFile(plists[i].c_str(), pszPath.c_str());
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plistPath.c_str());
	}
	pathToPlistsMap.erase(path);
	
	set<string> animateNames=pathToNameMap[path];
	for (set<string>::iterator strItr=animateNames.begin();strItr!=animateNames.end();++strItr)
	{
		AnimationCache::getInstance()->removeAnimation((*strItr).c_str());
		nameToAnimateMap.erase((*strItr));
	}
	pathToNameMap.erase(path);

}

Sequence* AnimatePacker::getSequence(const char *name){
	Animation* animation=AnimationCache::getInstance()->getAnimation(name);

	if(animation)
	{
		MyAnimate animate=nameToAnimateMap[name];

        Vector<Ref *> actions;
		//CCArray *actions=CCArray::create();//actionWithFlipX(animate.flipX)
		actions.pushBack(FlipX::create(animate.flipX));
		actions.pushBack(FlipY::create(animate.flipY));
		actions.pushBack(Animate::create(animation));

		Sequence *sequence= createSequence(actions);
		actions.clear();

		return sequence;
	}
	return NULL;
}

Sequence *AnimatePacker::createSequence(Vector<Ref*> actions)
{
	CC_ASSERT(actions.size()>1);
	Sequence *seq = Sequence::create((FiniteTimeAction*)actions.at(0),
		(FiniteTimeAction*)actions.at(1), NULL);
	for (unsigned int i = 2; i < actions.size(); ++i) {
		seq = Sequence::create(seq, (FiniteTimeAction*)actions.at(i), NULL);
	}
	return seq;
}

Sequence *AnimatePacker::createSequence(FiniteTimeAction *pAction1, FiniteTimeAction *pAction2, ...)
{
	va_list params;
	va_start(params, pAction2);

	Sequence *pPrev = Sequence::create(pAction1, pAction2, NULL);
	FiniteTimeAction *pNow = NULL;  

	while( pPrev ) {
		pNow = va_arg(params, FiniteTimeAction*);
		if (pNow)
		{
			pPrev = CCSequence::create(pPrev, pNow, NULL);
		}
		else
		{
			break;
		}
	}  
	va_end(params);
	return pPrev;
}