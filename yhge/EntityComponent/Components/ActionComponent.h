#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_ACTIONCOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_ACTIONCOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

class RendererComponent;

/**
 * 效果组件
 * 一个entity同时可以有多个效果组件，这些特效的功能最好是不一样的。
 * 一个效果组件可以有多个特效，但是定义在同一个key里。
 */
class ActionComponent : public Component
{
public:
    
	ActionComponent();
    
	~ActionComponent();
    
	virtual bool init();
	virtual bool init(const std::string&  file);
    virtual bool init(CCDictionary* data);
    
    /**
     * 设置
     */
    virtual void setup();
    
    /**
     * 消除
     */
    virtual void cleanup();

    virtual bool registerMessages();
    virtual void cleanupMessages();

    /**
     * 按名称取得动画
     */
	CCAction* actionForName(const std::string& name);
	CCAction* actionForName(const std::string& name ,int index);
	CCAction* actionForName(const std::string& name ,const std::string& key);
    
    /**
     * 按名称取得动画列表
     */
	CCArray* actionListForName(const std::string& name);
    
    /**
     * 按名称取得动画字典
     */
	CCDictionary* actionMapForName(const std::string& name);

    /**
     * 添加一个动画
     */
	void addAction(CCAction* action, const std::string& name);
    
    /**
     * 添加一个动画列表
     */
	void addActionList(CCArray* actionList ,const std::string& name);
    
    /**
     * 添加一个动画字典
     */
	void addActionMap(CCDictionary* actionMap,const std::string& name);
    
    /**
     * 移除一个动画
     */
	void removeActionNamed(const std::string& name);

    /**
     * 播放一个动画
     */
    void runAction(CCAction* action);

    /**
     * 播放一个动画
     */
    inline void runAction(const std::string& name)
    {
        runAction(actionForName(name));
    }

    /**
     * 播放一个动画
     */
    inline void runAction(const std::string& name,int index)
    {
        runAction(actionForName(name,index));
    }

    /**
     * 播放一个动画
     */
    inline void runAction(const std::string& name,const std::string& key)
    {
        runAction(actionForName(name,key));
    }

    /**
     * 处理动画改变事件
     */
    void onChangeAction(Message* message);
    
    /**
     * 处理动画播放完成
     */
    void onActionComplete();
    
    /**
     * 从定义里创建action action
     */
    CCAction* createActionFromDefine(CCAction* action);
    
public:
    
    inline void setEffects(CCDictionary* actions)
    {
        CC_SAFE_RETAIN(actions);
        CC_SAFE_RELEASE(m_actions);
        m_actions = actions;
    }
    
    inline CCDictionary* getEffects()
    {
        return m_actions;
    }
    
    inline void setLastActions(CCArray* lastActions)
    {
        CC_SAFE_RETAIN(lastActions);
        CC_SAFE_RELEASE(m_lastActions);
        m_lastActions = lastActions;
    }
    
    inline CCArray* getLastActions()
    {
        return m_lastActions;
    }
    
protected:
    //效果定义库
	CCDictionary* m_actions;
    
    //上次执行的效果
    CCArray* m_lastActions;

    //保留的渲染组件的引用
    RendererComponent* m_rendererComponent;
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_COMPONENTS_ACTIONCOMPONENT_H_
