#ifndef YHGE_COMPONENTS_ISOPositionComponent_H_
#define YHGE_COMPONENTS_ISOPositionComponent_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN


class ISOPositionComponent : public Component 
{
public:
    
    ISOPositionComponent();
    
    ~ISOPositionComponent();
    
    virtual bool init();
    
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
    
protected:
    
    CCNode* m_renderer;
    
};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_ISOPositionComponent_H_
