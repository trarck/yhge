#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_EIGHTDIRECTIONANIMATIONCOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_EIGHTDIRECTIONANIMATIONCOMPONENT_H_

#include "cocos2d.h"
#include "AnimationComponent.h"

NS_CC_YHGE_BEGIN

class SpriteRendererComponent;

/**
 * 8方向动画组件。
 */
class EightDirectionAnimationComponent : public AnimationComponent
{
public:
    
	EightDirectionAnimationComponent();
    
	~EightDirectionAnimationComponent();
    
    /**
     * 处理动画改变事件
     */
    void onChangeAnimation(Message* message);
    
    /**
     * 从文件中取得8方向动画
     * 关键帧在一张图片里。根据名子来确定方向
     */
	static CCArray* eightDirectionActionListWithFile(const char* file ,int frameCount ,CCSize frameSize ,float delay,int loops=-1);
	
    /**
     * 从目录中取得8方向动画
     * 关键帧是一张张图片。根据名子来确定方向
     */
    static CCArray* eightDirectionActionListWithDir(const char* dir ,int frameCount ,CCSize frameSize ,float delay,const char* pathFormat,int loops=-1);

    /**
     * 从目录中取得8方向动画
     * 关键帧是一张张图片。根据名子来确定方向
     */
    static CCArray* eightDirectionActionListWithDirResource(const char* resource ,int frameCount ,CCSize frameSize ,float delay,int loops=-1);
    
    /**
     * 从集合里创建8方向动画
     * 关键帧是一张张图片。根据名子来确定方向
     */
    static CCArray* createDirectionActionListWithResource(const char* resource,const char* filenameFormat,int directionCount ,int frameCount ,float delay,int loops=-1);
    
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_COMPONENTS_EIGHTDIRECTIONANIMATIONCOMPONENT_H_
