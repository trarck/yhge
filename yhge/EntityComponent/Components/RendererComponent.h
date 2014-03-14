#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_RENDERERCOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_RENDERERCOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN


class RendererComponent : public Component 
{
public:
    
    RendererComponent();
    
    ~RendererComponent();
        
    virtual bool registerMessages();
    
    virtual void cleanupMessages();
    
    virtual CCNode* getRenderer();
    
    virtual void setRenderer(CCNode* renderer);
    
    /**
     * 执行action
     */
    virtual void runAction(CCAction* action);
    
    /**
     * 停止action
     */
    virtual void stopAction(CCAction* action);
    
    /**
     * 停止action by tag
     */
    virtual void stopActionByTag(int tag);

    /**
     * 响应执行action
     */
    virtual void onRunAction(Message* message);
    
    /**
     * 响应停止action
     */
    virtual void onStopAction(Message* message);
    
    /**
     * 响应停止action by tag
     */
    virtual void onStopActionByTag(Message* message);
    
    //==============对animation的特殊支持==============//
    /**
     * 执行animation
     */
    virtual void runAnimate(CCAction* animate);
    
    /**
     * 停止animation
     */
    virtual void stopAnimate(CCAction* animate);
    
    /**
     * 停止animation
     */
    virtual void stopAnimateByTag(int tag);
    
    /**
     * 响应执行animation
     */
    virtual void onRunAnimate(Message* message);
    
    /**
     * 响应停止animation
     */
    virtual void onStopAnimate(Message* message);
    
    /**
     * 响应停止animation by tag
     */
    virtual void onStopAnimateByTag(Message* message);
    
protected:
    
    CCNode* m_renderer;
    
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_RENDERERCOMPONENT_H_
