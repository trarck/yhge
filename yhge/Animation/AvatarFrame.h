#ifndef YHGE_ANIMATION_AVATARFRAME_H_
#define YHGE_ANIMATION_AVATARFRAME_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "AnimationInterface.h"
#include "Frame.h"
#include "DisplayProperty.h"

NS_CC_YHGE_BEGIN

class FrameElement:public Ref
{
public:

    FrameElement();
    ~FrameElement();
    
    inline void setDisplayProperty(DisplayProperty* displayProperty)
    {
        CC_SAFE_RETAIN(displayProperty);
        CC_SAFE_RELEASE(_displayProperty);
        _displayProperty = displayProperty;
    }
    
    inline DisplayProperty* getDisplayProperty()
    {
        return _displayProperty;
    }
    
    inline void setCharacterId(int characterId)
    {
        _characterId = characterId;
    }
    
    inline int getCharacterId()
    {
        return _characterId;
    }
    
    inline void setZOrder(int zOrder)
    {
        _zOrder = zOrder;
    }
    
    inline int getZOrder()
    {
        return _zOrder;
    }

protected:
    
    DisplayProperty* _displayProperty;
    
    int _characterId;
    
    int _zOrder;
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
//        CC_SAFE_RELEASE(_elements);
//        _elements = elements;
//    }
//    
//    inline CCArray* getElements()
//    {
//        return _elements;
//    }
//    
//protected:
//
//    //sort by zorder
//    CCArray* _elements;
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
        CC_SAFE_RELEASE(_elements);
        _elements = elements;
    }
    
    inline CCDictionary* getElements()
    {
        return _elements;
    }
    
protected:
    
    CCDictionary* _elements;
};

NS_CC_YHGE_END

#endif //YHGE_ANIMATION_AVATARFRAME_H_