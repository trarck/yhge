#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_EFFECTCOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_EFFECTCOMPONENT_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

class RendererComponent;

class CCEffect:public CCObject
{
    
};

/**
 * 效果组件
 * 一个entity同时可以有多个效果组件，这些特效的功能最好是不一样的。
 * 一个效果组件可以有多个特效，但是定义在同一个key里。
 */
class EffectComponent : public Component
{
public:
    
	EffectComponent();
    
	~EffectComponent();
    
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
	CCEffect* effectForName(const std::string& name);
	CCEffect* effectForName(const std::string& name ,int index);
	CCEffect* effectForName(const std::string& name ,const std::string& key);
    
    /**
     * 按名称取得动画列表
     */
	CCArray* effectListForName(const std::string& name);
    
    /**
     * 按名称取得动画字典
     */
	CCDictionary* effectMapForName(const std::string& name);

    /**
     * 添加一个动画
     */
	void addEffect(CCEffect* effect, const std::string& name);
    
    /**
     * 添加一个动画列表
     */
	void addEffectList(CCArray* effectList ,const std::string& name);
    
    /**
     * 添加一个动画字典
     */
	void addEffectMap(CCDictionary* effectMap,const std::string& name);
    
    /**
     * 移除一个动画
     */
	void removeEffectNamed(const std::string& name);

    /**
     * 播放一个动画
     */
    void runEffect(CCEffect* effect);

    /**
     * 播放一个动画
     */
    inline void runEffect(const std::string& name)
    {
        runEffect(effectForName(name));
    }

    /**
     * 播放一个动画
     */
    inline void runEffect(const std::string& name,int index)
    {
        runEffect(effectForName(name,index));
    }

    /**
     * 播放一个动画
     */
    inline void runEffect(const std::string& name,const std::string& key)
    {
        runEffect(effectForName(name,key));
    }

    /**
     * 处理动画改变事件
     */
    void onChangeEffect(Message* message);
    
    /**
     * 处理动画播放完成
     */
    void onEffectComplete();
    
    /**
     * 从定义里创建effect action
     */
    CCAction* createActionFromEffect(CCEffect* effect);
    
public:
    
    inline void setEffects(CCDictionary* effects)
    {
        CC_SAFE_RETAIN(effects);
        CC_SAFE_RELEASE(m_effects);
        m_effects = effects;
    }
    
    inline CCDictionary* getEffects()
    {
        return m_effects;
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
	CCDictionary* m_effects;
    
    //上次执行的效果
    CCArray* m_lastActions;

    //保留的渲染组件的引用
    RendererComponent* m_rendererComponent;
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_COMPONENTS_EFFECTCOMPONENT_H_
