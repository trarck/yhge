/****************************************************************************
扩展CCPoint 对于2.1版之后的几何类取消继承CCObject
****************************************************************************/

#ifndef YHGE_COCOSEXT_CCGEOMETRYVAULE_H_
#define YHGE_COCOSEXT_CCGEOMETRYVAULE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"


NS_CC_YHGE_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CCPointValue : public cocos2d::CCObject
{
public:
	inline CCPointValue()
    :m_tPoint(cocos2d::CCPointZero)
	{
		
	}
	
    inline CCPointValue(const cocos2d::CCPoint& tPoint)
    :m_tPoint(tPoint)
    {
    }
    
    inline CCPointValue(float x,float y)
    {
        setPoint(x, y);
    }
    
    inline CCPointValue(const CCPointValue& other)
	{
	    this->setPoint(other.getPoint());
	}
    
    CCPointValue& operator= (const CCPointValue& other);
    
    inline void setPoint(float x, float y)
    {
        m_tPoint.x = x;
        m_tPoint.y = y;
    }
    
	inline void setPoint(const cocos2d::CCPoint &tPoint)
    {
        m_tPoint=tPoint;
    }
    
	inline const cocos2d::CCPoint& getPoint() const
    {
        return m_tPoint;
    }
    
    virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);
	
	inline static CCPointValue* create(const cocos2d::CCPoint& tPoint)
	{
		CCPointValue* pRet=new CCPointValue(tPoint);
		pRet->autorelease();
		return pRet;
	}
	
	inline static CCPointValue* create(float x,float y)
	{
		CCPointValue* pRet=new CCPointValue(x,y);
		pRet->autorelease();
		return pRet;
	}
    
private:
	cocos2d::CCPoint m_tPoint;
};

class CCSizeValue : public cocos2d::CCObject
{
public:
    inline CCSizeValue()
    :m_tSize(cocos2d::CCSizeZero)
	{
		
	}
	
    inline CCSizeValue(float width, float height)
    :m_tSize(width,height)
	{
		
	}
	
	inline CCSizeValue(const cocos2d::CCSize& tSize)
    :m_tSize(tSize)
	{
		
	}
	
    inline CCSizeValue(const CCSizeValue& other)
    :m_tSize(other.getSize())
	{
		
	}
	
    CCSizeValue& operator= (const CCSizeValue& other);
    
	inline void setSize(float width, float height){
    	m_tSize.width=width;
		m_tSize.height=height;
    }
	inline void setSize(const cocos2d::CCSize& tSize){
		m_tSize=tSize;
	}
    
	inline const cocos2d::CCSize& getSize() const
    {
		return m_tSize;
	}
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
	
	inline static CCSizeValue* create(const cocos2d::CCSize& tSize)
	{
		CCSizeValue* pRet=new CCSizeValue(tSize);
		pRet->autorelease();
		return pRet;
	}
	
	inline static CCSizeValue* create(float width,float height)
	{
		CCSizeValue* pRet=new CCSizeValue(width,height);
		pRet->autorelease();
		return pRet;
	}
    
private:
    cocos2d::CCSize m_tSize;
};

class CCRectValue : public cocos2d::CCObject
{
    
public:
    inline CCRectValue()
    :m_tRect(cocos2d::CCRectZero)
    {
        
    }
    
    inline CCRectValue(float x, float y, float width, float height)
    :m_tRect(x,y,width,height)
    {
        
    }
    
	inline CCRectValue(const cocos2d::CCRect& tRect)
    :m_tRect(tRect)
    {
        
    }
    
    inline CCRectValue(const CCRectValue& other)
    :m_tRect(other.getRect())
    {
        
    }
    
    CCRectValue& operator= (const CCRectValue& other);
	
    inline void setRect(float x, float y, float width, float height)
	{
		m_tRect.origin.x=x;
		m_tRect.origin.y=y;
		m_tRect.size.width=width;
		m_tRect.size.height=height;
	}
    
    inline void setRect(const cocos2d::CCRect &tRect)
	{
		m_tRect=tRect;
	}
	
	inline const cocos2d::CCRect& getRect() const
    {
		return m_tRect;
	}
    
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
    
    inline static CCRectValue* create(const cocos2d::CCRect& rect)
    {
        CCRectValue* pRet=new CCRectValue(rect);
        pRet->autorelease();
        return pRet;
    }
    
    inline static CCRectValue* create(float x,float y,float width,float height)
    {
        CCRectValue* pRet=new CCRectValue(x,y,width,height);
        pRet->autorelease();
        return pRet;
    }
    
private:
    cocos2d::CCRect m_tRect;
};

NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCGEOMETRYVAULE_H_
