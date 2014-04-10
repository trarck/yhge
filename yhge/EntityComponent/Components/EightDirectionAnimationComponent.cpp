#include "EightDirectionAnimationComponent.h"
#include <yhge/Base/Log.h>
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include "ComponentMessageDefine.h"
#include "ComponentConsts.h"
#include "SpriteRendererComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN


EightDirectionAnimationComponent::EightDirectionAnimationComponent()
{
    
}

EightDirectionAnimationComponent::~EightDirectionAnimationComponent()
{

}

void EightDirectionAnimationComponent::onChangeAnimation(Message *message)
{
    CCDictionary* data=message->getDictionary();
    int direction=0;
    
    CCString* animationName=(CCString*)data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NAME);
    
    CCInteger* directionValue=((CCInteger*) data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_DIRECTION));
    if (directionValue) {
        direction=directionValue->getValue();
    }
    
    bool needCompleteAction=false;
    
    CCBool* needCompleteAcionValue=static_cast<CCBool*>(data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_NEEDCOMPLETEACTION));
    if(needCompleteAcionValue){
        needCompleteAction=needCompleteAcionValue->getValue();
    }
    
    YHDEBUG("direction:%d name:%s",direction,animationName->getCString());
    
    CCAnimation* animation= animationForName(animationName->getCString(),direction);
    
    if(animation){
        
        runAnimation(animation,needCompleteAction);
        
        CCBool* showFirstFrameValue=static_cast<CCBool*>(data->objectForKey(COMPONENT_ANIMATION_CHANGE_PARAM_SHOW_FIRST_FRAME));
        if(showFirstFrameValue && showFirstFrameValue->getValue()){
            
            displayFirstFrame(animation);
        }

    }else {
        YHERROR("unknow animation name %s action is null",animationName->getCString());
    }
}

/**
 * 从文件中取得8方向动画
 * 关键帧在一张图片里。根据名子来确定方向
 */
CCArray* EightDirectionAnimationComponent::eightDirectionActionListWithFile(const char* file ,int frameCount ,CCSize frameSize ,float delay,int loops)
{
	CCTexture2D *texture=CCTextureCache::sharedTextureCache()->addImage(file);
	
	CCArray* animations=CCArray::createWithCapacity(8);

	//move action
	for (int i=0; i<8; i++) {
		CCArray* animFrames=new CCArray();
		animFrames->initWithCapacity(frameCount);
		for (int j=0; j<frameCount; j++) {
			CCSpriteFrame *frame=CCSpriteFrame::createWithTexture(texture ,CCRectMake(j*frameSize.width, i*frameSize.height, frameSize.width, frameSize.height));
			animFrames->addObject(frame);
		}
        
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames,delay);
        animation->setLoops(loops);
        
        animFrames->release();
        
        animations->addObject(animation);
		
	}
	return animations;
}

/**
 * 从目录中取得8方向动画
 * 关键帧是一张张图片。根据名子来确定方向
 */
CCArray* EightDirectionAnimationComponent::eightDirectionActionListWithDir(const char* dir ,int frameCount ,CCSize frameSize ,float delay,const char* pathFormat,int loops)
{
	CCArray* animations=CCArray::createWithCapacity(8);
	
	//move action
	char str[255] = {0};
	for (int i=0; i<8; i++) {
		CCAnimation* animation = CCAnimation::create();
		for (int j=0; j<frameCount; j++) {
			sprintf(str,pathFormat,dir,i,j);//"%s/%02d%03d.png"
			animation->addSpriteFrameWithFileName(str);
		}
		animation->setDelayPerUnit(delay);
		animation->setRestoreOriginalFrame(true);
        animation->setLoops(loops);
		//animation.delay=delay;
        animations->addObject(animation);
	}
	return animations;
}

/**
 * 从目录中取得8方向动画
 * 关键帧是一张张图片。根据名子来确定方向
 */
CCArray* EightDirectionAnimationComponent::eightDirectionActionListWithDirResource(const char* resource ,int frameCount ,CCSize frameSize ,float delay,int loops)
{
    CCArray* animations=CCArray::createWithCapacity(8);
	
	//move actiongit
	char str[255] = {0};
	for (int i=0; i<8; i++) {
		CCAnimation* animation = CCAnimation::create();
		for (int j=0; j<frameCount; j++) {
			sprintf(str,resource,i,j);//"xxx/xx/%02d%03d.png"
			animation->addSpriteFrameWithFileName(str);
		}
		animation->setDelayPerUnit(delay);
		animation->setRestoreOriginalFrame(true);
        animation->setLoops(loops);
		//animation.delay=delay;
        animations->addObject(animation);
	}
	return animations;
}

/**
 * 从目录中取得8方向动画
 * 关键帧是一张张图片。根据名子来确定方向
 */
CCArray* EightDirectionAnimationComponent::createDirectionActionListWithResource(const char* resource ,const char* filenameFormat,int directionCount,int frameCount,float delay,int loops)
{
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    frameCache->addSpriteFramesWithFile(resource);
    
    CCArray* animations=CCArray::createWithCapacity(directionCount);
	
    CCSpriteFrame *spriteFrame =NULL;
    
	//move actiongit
	char str[255] = {0};
	for (int i=0; i<directionCount; i++) {
        
		CCAnimation* animation = CCAnimation::create();
        
		for (int j=0; j<frameCount; j++) {
			sprintf(str,filenameFormat,i,j);//"xxx-xx-%02d%03d.png"
            spriteFrame = frameCache->spriteFrameByName(str);
            if (!spriteFrame) {
                YHERROR("EightDirectionAnimationComponent::createDirectionActionListWithResource no fined %s",str);
            }
			animation->addSpriteFrame(spriteFrame);
		}
        
		animation->setDelayPerUnit(delay);
		animation->setRestoreOriginalFrame(true);
        animation->setLoops(loops);
		//animation.delay=delay;
        animations->addObject(animation);
        
	}
    
	return animations;
}

NS_CC_YHGE_END