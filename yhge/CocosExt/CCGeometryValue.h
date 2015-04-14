/****************************************************************************
扩展CCPoint 对于2.1版之后的几何类取消继承Ref
****************************************************************************/

#ifndef YHGE_COCOSEXT_CCGEOMETRYVAULE_H_
#define YHGE_COCOSEXT_CCGEOMETRYVAULE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>


NS_CC_YHGE_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CCPointValue : public cocos2d::Ref
{
public:
	inline CCPointValue()
    :_tPoint(cocos2d::CCPointZero)
	{
		
	}
	
    inline CCPointValue(const cocos2d::CCPoint& tPoint)
    :_tPoint(tPoint)
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
        _tPoint.x = x;
        _tPoint.y = y;
    }
    
	inline void setPoint(const cocos2d::CCPoint &tPoint)
    {
        _tPoint=tPoint;
    }
    
	inline const cocos2d::CCPoint& getPoint() const
    {
        return _tPoint;
    }
    
    virtual cocos2d::Ref* copyWithZone(cocos2d::CCZone* pZone);
	
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
	cocos2d::CCPoint _tPoint;
};

class CCSizeValue : public cocos2d::Ref
{
public:
    inline CCSizeValue()
    :_tSize(cocos2d::CCSizeZero)
	{
		
	}
	
    inline CCSizeValue(float width, float height)
    :_tSize(width,height)
	{
		
	}
	
	inline CCSizeValue(const cocos2d::CCSize& tSize)
    :_tSize(tSize)
	{
		
	}
	
    inline CCSizeValue(const CCSizeValue& other)
    :_tSize(other.getSize())
	{
		
	}
	
    CCSizeValue& operator= (const CCSizeValue& other);
    
	inline void setSize(float width, float height){
    	_tSize.width=width;
		_tSize.height=height;
    }
	inline void setSize(const cocos2d::CCSize& tSize){
		_tSize=tSize;
	}
    
	inline const cocos2d::CCSize& getSize() const
    {
		return _tSize;
	}
    virtual Ref* copyWithZone(cocos2d::CCZone* pZone);
	
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
    cocos2d::CCSize _tSize;
};

class CCRectValue : public cocos2d::Ref
{
    
public:
    inline CCRectValue()
    :_tRect(cocos2d::CCRectZero)
    {
        
    }
    
    inline CCRectValue(float x, float y, float width, float height)
    :_tRect(x,y,width,height)
    {
        
    }
    
	inline CCRectValue(const cocos2d::CCRect& tRect)
    :_tRect(tRect)
    {
        
    }
    
    inline CCRectValue(const CCRectValue& other)
    :_tRect(other.getRect())
    {
        
    }
    
    CCRectValue& operator= (const CCRectValue& other);
	
    inline void setRect(float x, float y, float width, float height)
	{
		_tRect.origin.x=x;
		_tRect.origin.y=y;
		_tRect.size.width=width;
		_tRect.size.height=height;
	}
    
    inline void setRect(const cocos2d::CCRect &tRect)
	{
		_tRect=tRect;
	}
	
	inline const cocos2d::CCRect& getRect() const
    {
		return _tRect;
	}
    
    virtual Ref* copyWithZone(cocos2d::CCZone* pZone);
    
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
    cocos2d::CCRect _tRect;
};

NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCGEOMETRYVAULE_H_
