#ifndef YHGE_ANIMATION_AVATARFRAME_H_
#define YHGE_ANIMATION_AVATARFRAME_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "AnimationInterface.h"
#include "Frame.h"
#include "DisplayProperty.h"

NS_CC_YHGE_BEGIN

class FrameElement:public CCObject
{
public:
    
    inline void setDisplayProperty(DisplayProperty* displayProperty)
    {
        CC_SAFE_RETAIN(displayProperty);
        CC_SAFE_RELEASE(m_displayProperty);
        m_displayProperty = displayProperty;
    }
    
    inline DisplayProperty* getDisplayProperty()
    {
        return m_displayProperty;
    }
    
    inline void setCharacterId(int characterId)
    {
        m_characterId = characterId;
    }
    
    inline int getCharacterId()
    {
        return m_characterId;
    }
    
    inline void setZOrder(int zOrder)
    {
        m_zOrder = zOrder;
    }
    
    inline int getZOrder()
    {
        return m_zOrder;
    }

protected:
    
    DisplayProperty* m_displayProperty;
    
    int m_characterId;
    
    int m_zOrder;
};


//class AvatarFrame:public Frame
//{  
//public:
//
//    AvatarFrame();
//
//    ~AvatarFrame();
//    
//    virtual bool init();
//
//    void addElement(FrameElement* element);
//    
//    void removeElement(FrameElement* element);
//    
//    void removeElementByZOrder(int zOrder);
//    
//public:
//
//    inline void setElements(CCArray* elements)
//    {
//        CC_SAFE_RETAIN(elements);
//        CC_SAFE_RELEASE(m_elements);
//        m_elements = elements;
//    }
//    
//    inline CCArray* getElements()
//    {
//        return m_elements;
//    }
//    
//protected:
//
//    //sort by zorder
//    CCArray* m_elements;
//};

/**
 * 组成帧的元素的角色id唯一
 */
class AvatarFrame:public Frame
{
public:
    
    AvatarFrame();
    
    ~AvatarFrame();
    
    virtual bool init();
    
    void addElement(FrameElement* element);
    
    void removeElement(FrameElement* element);
    
    void removeElementByZOrder(int zOrder);
    
public:
    
    inline void setElements(CCDictionary* elements)
    {
        CC_SAFE_RETAIN(elements);
        CC_SAFE_RELEASE(m_elements);
        m_elements = elements;
    }
    
    inline CCDictionary* getElements()
    {
        return m_elements;
    }
    
protected:
    
    CCDictionary* m_elements;
};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_AVATARFRAME_H_