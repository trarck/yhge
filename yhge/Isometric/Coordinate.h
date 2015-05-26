#ifndef YHGE_ISOMETRIC_COORDINATE_H_
#define YHGE_ISOMETRIC_COORDINATE_H_

#include "cocos2d.h"
#include "IsometricMacros.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

class Coordinate : public Ref {

public:
    
    Coordinate();
    ~Coordinate(void);
    
	static Coordinate* sharedCoordinate();
	static Coordinate* create();
	static Coordinate* create(float width,float height);
	static Coordinate* create(float xUnit,float yUnit,float zUnit);

    inline bool init(){
		return true;
	}
   	inline bool init(float width,float height)
	{
		setTileSize(width ,height);
		return true;
	}

	inline bool init(float xUnit,float yUnit,float zUnit){
		setCoordinateUnit(xUnit ,yUnit ,zUnit);
		return true;
	}

	void setTileSize(float width ,float height);
	void setCoordinateUnit(float xUnit ,float yUnit ,float zUnit);
	void setCoordinateUnit(float xUnit ,float yUnit);

	//==============使用传值的方式==========================//
	inline Vec2 isoViewToGame2F(float x,float y)
	{
		Vec2 p;
		x=x/_tileWidth;//x=x/64
		y=y/_tileHeight;//y=y/32
		p.x=x+y;
		p.y=y-x;
		return p;
	}
    
	inline Vec2 isoViewToGamePoint(const Vec2& point)
	{
		return isoViewToGame2F(point.x,point.y);
	}
    
	inline Vec2 isoViewToGameGrid2F (float x,float  y)
	{
		Vec2 p=isoViewToGame2F(x,y);
		p.x=floor(p.x);
		p.y=floor(p.y);
		return p;
	}
    
	inline Vec2 isoViewToGameGridPoint (const Vec2& point)
	{
		return isoViewToGameGrid2F(point.x,point.y);
	}
    
	inline Vec2 isoViewToGameCell2F (float x,float  y)
	{
		Vec2 p=isoViewToGame2F(x,y);
		p.x=(int)p.x;
		p.y=(int)p.y;
		return p;
	}
    
    
	inline Vec2 isoGameToView3F(float x ,float y ,float z)
	{
		double sx=x-y,sy=x+y;
		Vec2 p;
		p.x=sx*_xUnit;//sx*32
		p.y=sy*_halfYUnit-z*_zUnit;//sy*16-z*32
		return p;
	}
    
	inline Vec2 isoGameToView2F(float x, float y)
	{
		double sx=x-y,sy=x+y;
		Vec2 p;
		p.x=sx*_xUnit;//sx*32
		p.y=sy*_halfYUnit;//sy*16
		return p;
	}
    
	inline Vec2 isoGameToViewPoint(const Vec2&  point)
	{
		return isoGameToView2F(point.x,point.y);
	}
    
	//==============使用传址的方式=====================//
    
	inline void isoViewToGame2FP(float x,float y,Vec2* destPoint)
	{
		x=x/_tileWidth;//x=x/64
		y=y/_tileHeight;//y=y/32
		destPoint->x=x+y;
		destPoint->y=y-x;
	}
    
	inline void isoViewToGamePointP(const Vec2& point,Vec2* destPoint)
	{
		isoViewToGame2FP(point.x,point.y,destPoint);
	}
    
	inline void isoViewToGameGrid2FP(float x,float  y,Vec2* destPoint)
	{
		isoViewToGame2FP(x,y,destPoint);
		destPoint->x=floor(destPoint->x);
		destPoint->y=floor(destPoint->y);
	}
    
	inline void isoViewToGameGridPointP (const Vec2& point,Vec2* destPoint)
	{
		isoViewToGameGrid2FP(point.x,point.y,destPoint);
	}
    
	inline void isoViewToGameCell2FP(float x,float  y,Vec2* destPoint)
	{
		isoViewToGame2FP(x,y,destPoint);
		destPoint->x=(int)destPoint->x;
		destPoint->y=(int)destPoint->y;
	}
    
    
	inline void isoGameToView3FP(float x ,float y ,float z,Vec2* destPoint)
	{
		double sx=x-y,sy=x+y;
		destPoint->x=sx*_xUnit;//sx*32
		destPoint->y=sy*_halfYUnit-z*_zUnit;//sy*16-z*32
	}
    
	inline void isoGameToView2FP(float x, float y,Vec2* destPoint)
	{
		double sx=x-y,sy=x+y;
		destPoint->x=sx*_xUnit;//sx*32
		destPoint->y=sy*_halfYUnit;//sy*16
	}
    
	inline void isoGameToViewPointP(const Vec2&  point,Vec2* destPoint)
	{
		isoGameToView2FP(point.x,point.y,destPoint);
	}

    //==============其它工具方法=====================//
    /**
     * 物体在地图坐标的大小转成屏幕坐标大小
     */
    Size mapToScreenSize(int l ,int b ,int h);
    
    /**
     * 根据物体在地图坐标的大小计算其在显示的时候屏幕坐标的锚点
     * 如果是opengl坐标系，则对齐点在中下，和屏幕坐标系统不同。如果是opengl，则不需要转换锚点。
     */
    Vec2 mapToScreenAnchor(int l ,int b ,int h);
    
private:
	float _xUnit;
	float _yUnit;
	float _zUnit;
	float _halfYUnit;
	
	float _tileWidth;
	float _tileHeight;
};





NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_COORDINATE_H_
