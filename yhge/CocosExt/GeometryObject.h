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

class PointObject : public Ref
{
public:
	inline PointObject()
	:_point(Vec2(0,0))
	{
		
	}
	
    inline PointObject(const Vec2& tPoint)
	: _point(tPoint)
    {
    }
    
    inline PointObject(float x,float y)
    {
        setPoint(x, y);
    }
    
    inline PointObject(const PointObject& other)
	{
	    this->setPoint(other.getPoint());
	}
    
    PointObject& operator= (const PointObject& other);
    
    inline void setPoint(float x, float y)
    {
		_point.x = x;
		_point.y = y;
    }
    
	inline void setPoint(const Vec2 &tPoint)
    {
		_point = tPoint;
    }
    
	inline const Vec2& getPoint() const
    {
		return _point;
    }
    
	
	inline static PointObject* create(const Vec2& point)
	{
		PointObject* pRet=new PointObject(point);
		pRet->autorelease();
		return pRet;
	}
	
	inline static PointObject* create(float x,float y)
	{
		PointObject* pRet=new PointObject(x,y);
		pRet->autorelease();
		return pRet;
	}
    
private:
	Vec2 _point;
};

class SizeObject : public Ref
{
public:
    inline SizeObject()
    :_size(Size(0,0))
	{
		
	}
	
    inline SizeObject(float width, float height)
    :_size(Size(width,height))
	{
		
	}
	
	inline SizeObject(const Size& size)
	: _size(size)
	{
		
	}
	
    inline SizeObject(const SizeObject& other)
    :_size(other.getSize())
	{
		
	}
	
    SizeObject& operator= (const SizeObject& other);
    
	inline void setSize(float width, float height){
    	_size.width=width;
		_size.height=height;
    }
	inline void setSize(const Size& size){
		_size=size;
	}
    
	inline const Size& getSize() const
    {
		return _size;
	}
	
	inline static SizeObject* create(const Size& size)
	{
		SizeObject* pRet=new SizeObject(size);
		pRet->autorelease();
		return pRet;
	}
	
	inline static SizeObject* create(float width,float height)
	{
		SizeObject* pRet=new SizeObject(width,height);
		pRet->autorelease();
		return pRet;
	}
    
private:
    Size _size;
};

class RectObject : public Ref
{
    
public:
    inline RectObject()
    :_rect(Rect(0,0,0,0))
    {
        
    }
    
    inline RectObject(float x, float y, float width, float height)
	: _rect(Rect(x, y, width, height))
    {
        
    }
    
	inline RectObject(const Rect& rect)
    :_rect(rect)
    {
        
    }
    
    inline RectObject(const RectObject& other)
    :_rect(other.getRect())
    {
        
    }
    
    RectObject& operator= (const RectObject& other);
	
    inline void setRect(float x, float y, float width, float height)
	{
		_rect.origin.x=x;
		_rect.origin.y=y;
		_rect.size.width=width;
		_rect.size.height=height;
	}
    
    inline void setRect(const Rect& rect)
	{
		_rect=rect;
	}
	
	inline const Rect& getRect() const
    {
		return _rect;
	}
    
   
    inline static RectObject* create(const Rect& rect)
    {
        RectObject* pRet=new RectObject(rect);
        pRet->autorelease();
        return pRet;
    }
    
    inline static RectObject* create(float x,float y,float width,float height)
    {
        RectObject* pRet=new RectObject(x,y,width,height);
        pRet->autorelease();
        return pRet;
    }
    
private:
    Rect _rect;
};

NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCGEOMETRYVAULE_H_
