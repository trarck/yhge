#ifndef YHGE_COMPONENTS_ANIMATIONCOMPONENT_H_
#define YHGE_COMPONENTS_ANIMATIONCOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

class AnimationComponent : public Component
{
public:
    
	AnimationComponent();
    
	~AnimationComponent();
    
	//extend from parent
	virtual bool init();
	virtual bool init(const std::string&  file);
    virtual bool init(CCDictionary* data);
    
    virtual bool registerMessages();
    virtual void cleanupMessages();

    /**
     * 按名称取得动画
     */
	CCAnimation* animationForName(const std::string& name);
	CCAnimation* animationForName(const std::string& name ,int index);
	CCAnimation* animationForName(const std::string& name ,const std::string& key);
    
    /**
     * 按名称取得动画列表
     */
	CCArray* animationListForName(const std::string& name);
    
    /**
     * 按名称取得动画字典
     */
	CCDictionary* animationMapForName(const std::string& name);

    /**
     * 添加一个动画
     */
	void addAnimation(CCAnimation* animation, const std::string& name);
    
    /**
     * 添加一个动画列表
     */
	void addAnimationList(CCArray* animationList ,const std::string& name);
    
    /**
     * 添加一个动画字典
     */
	void addAnimationMap(CCDictionary* animationMap,const std::string& name);
    
    /**
     * 移除一个动画
     */
	void removeAnimationNamed(const std::string& name);
    
    
    void onChangeAnimation(Message* message);
    
    /**
     * 从动画里创建action
     */
    static CCAction* createActionFromAnimation(CCAnimation* animation);

    /**
     * 从文件中取得8方向动画
     * 关键帧在一张图片里。根据名子来确定方向
     */
	static CCArray* eightDirectionActionListWithFile(const char* file ,int frameCount ,CCSize frameSize ,float delay);
	
    /**
     * 从目录中取得8方向动画
     * 关键帧是一张张图片。根据名子来确定方向
     */
    static CCArray* eightDirectionActionListWithDir(const char* dir ,int frameCount ,CCSize frameSize ,float delay,const char* pathFormat);
    
public:
    
    inline void setAnimations(CCDictionary* animations)
    {
        CC_SAFE_RETAIN(animations);
        CC_SAFE_RELEASE(m_animations);
        m_animations = animations;
    }
    
    inline CCDictionary* getAnimations()
    {
        return m_animations;
    }
    
    inline void setLastAnimation(CCAnimation* lastAnimation)
    {
//        CC_SAFE_RETAIN(lastAnimation);
//        CC_SAFE_RELEASE(m_lastAnimation);
        m_lastAnimation = lastAnimation;
    }
    
    inline CCAnimation* getLastAnimation()
    {
        return m_lastAnimation;
    }
    
    inline void setLastAction(CCAction* lastAction)
    {
        CC_SAFE_RETAIN(lastAction);
        CC_SAFE_RELEASE(m_lastAction);
        m_lastAction = lastAction;
    }
    
    inline CCAction* getLastAction()
    {
        return m_lastAction;
    }
    
protected:
    
	CCDictionary* m_animations;
    
    CCAnimation* m_lastAnimation;
    
    CCAction* m_lastAction;
};

NS_CC_YHGE_END

#endif // YHGE_COMPONENTS_ANIMATIONCOMPONENT_H_
