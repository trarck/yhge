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

	bool init(const std::string&  file);
    bool init(CCDictionary* data);

	CCObject* animationForName(const std::string& name);
	CCAction* actionForName(const std::string& name);
	CCAction* actionForName(const std::string& name ,int index);
	CCAction* actionForName(const std::string& name ,const std::string& key);

	CCArray* actionListForName(const std::string& name);
	CCDictionary* actionMapForName(const std::string& name);

	void addAction(CCAction* action, const std::string& name);
	void addActionList(CCArray* actionList ,const std::string& name);
	void addActionMap(CCDictionary* actionMap,const std::string& name);
	void addAnimation(CCObject* animation ,const std::string& name);
	void removeAnimationNamed(const std::string& name);

	static CCArray* eightDirectionActionListWithFile(const char* file ,int frameCount ,CCSize frameSize ,float delay);
	static CCArray* eightDirectionActionListWithDir(const char* dir ,int frameCount ,CCSize frameSize ,float delay,const char* pathFormat);

	void changeAction(CCDictionary* pData);

	CCAction* getLastAction()
	{
		return m_lastAction;
	}

	void setLastAction(CCAction* action)
	{
		CC_SAFE_RETAIN(action);
		CC_SAFE_RELEASE(m_lastAction);
		m_lastAction=action;
	}

	CCAction* moveAction();
	void moveActoin(CCAction* action);

	CCArray* actionArray();
	void actionArray(CCArray* actionArray);

	CCDictionary* animations();
	void animations(CCDictionary* animations);

protected:
	CCDictionary* m_animations;
    
    CCAction* m_lastAction;
};

NS_CC_YHGE_END

#endif // YHGE_COMPONENTS_ANIMATIONCOMPONENT_H_
