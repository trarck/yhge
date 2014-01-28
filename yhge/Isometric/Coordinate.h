#ifndef YHGE_ISOMETRIC_COORDINATE_H_
#define YHGE_ISOMETRIC_COORDINATE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class Coordinate : public CCObject {

public:
    
    Coordinate();
    ~Coordinate(void);
    
	static Coordinate* sharedCoordinate();
	static Coordinate* create();
	static Coordinate* create(int width,int height);
	static Coordinate* create(int xUnit,int yUnit,int zUnit);

    bool init(){
		return true;
	}
   	bool init(int width,int height)
	{
		setTileSize(width ,height);
		return true;
	}

	bool init(int xUnit,int yUnit,int zUnit){
		setCoordinateUnit(xUnit ,yUnit ,zUnit);
		return true;
	}

	void setTileSize(int width ,int height);
	void setCoordinateUnit(int xUnit ,int yUnit ,int zUnit);
	void setCoordinateUnit(int xUnit ,int yUnit);

	//==============使用传值的方式==========================//
	inline CCPoint isoViewToGame2F(float x,float y)
	{
		CCPoint p;
		x=x/m_tileWidth;//x=x/64
		y=y/m_tileHeight;//y=y/32
		p.x=x+y;
		p.y=y-x;
		return p;
	}
    
	inline CCPoint isoViewToGamePoint(const CCPoint& point)
	{
		return isoViewToGame2F(point.x,point.y);
	}
    
	inline CCPoint isoViewToGameGrid2F (float x,float  y)
	{
		CCPoint p=isoViewToGame2F(x,y);
		p.x=floor(p.x);
		p.y=floor(p.y);
		return p;
	}
    
	inline CCPoint isoViewToGameGridPoint (const CCPoint& point)
	{
		return isoViewToGameGrid2F(point.x,point.y);
	}
    
	inline CCPoint isoViewToGameCell2F (float x,float  y)
	{
		CCPoint p=isoViewToGame2F(x,y);
		p.x=(int)p.x;
		p.y=(int)p.y;
		return p;
	}
    
    
	inline CCPoint isoGameToView3F(float x ,float y ,float z)
	{
		double sx=x-y,sy=x+y;
		CCPoint p;
		p.x=sx*m_xUnit;//sx*32
		p.y=sy*m_yUnit-z*m_zUnit;//sy*16-z*32
		return p;
	}
    
	inline CCPoint isoGameToView2F(float x, float y)
	{
		double sx=x-y,sy=x+y;
		CCPoint p;
		p.x=sx*m_xUnit;//sx*32
		p.y=sy*m_yUnit;//sy*16
		return p;
	}
    
	inline CCPoint isoGameToViewPoint(const CCPoint&  point)
	{
		return isoGameToView2F(point.x,point.y);
	}
    
	//==============使用传址的方式=====================//
    
	inline void isoViewToGame2FP(float x,float y,CCPoint* destPoint)
	{
		x=x/m_tileWidth;//x=x/64
		y=y/m_tileHeight;//y=y/32
		destPoint->x=x+y;
		destPoint->y=y-x;
	}
    
	inline void isoViewToGamePointP(const CCPoint& point,CCPoint* destPoint)
	{
		isoViewToGame2FP(point.x,point.y,destPoint);
	}
    
	inline void isoViewToGameGrid2FP(float x,float  y,CCPoint* destPoint)
	{
		isoViewToGame2FP(x,y,destPoint);
		destPoint->x=floor(destPoint->x);
		destPoint->y=floor(destPoint->y);
	}
    
	inline void isoViewToGameGridPointP (const CCPoint& point,CCPoint* destPoint)
	{
		isoViewToGameGrid2FP(point.x,point.y,destPoint);
	}
    
	inline void isoViewToGameCell2FP(float x,float  y,CCPoint* destPoint)
	{
		isoViewToGame2FP(x,y,destPoint);
		destPoint->x=(int)destPoint->x;
		destPoint->y=(int)destPoint->y;
	}
    
    
	inline void isoGameToView3FP(float x ,float y ,float z,CCPoint* destPoint)
	{
		double sx=x-y,sy=x+y;
		destPoint->x=sx*m_xUnit;//sx*32
		destPoint->y=sy*m_yUnit-z*m_zUnit;//sy*16-z*32
	}
    
	inline void isoGameToView2FP(float x, float y,CCPoint* destPoint)
	{
		double sx=x-y,sy=x+y;
		destPoint->x=sx*m_xUnit;//sx*32
		destPoint->y=sy*m_yUnit;//sy*16
	}
    
	inline void isoGameToViewPointP(const CCPoint&  point,CCPoint* destPoint)
	{
		isoGameToView2FP(point.x,point.y,destPoint);
	}

    //==============其它工具方法=====================//
    /**
     * 物体在地图坐标的大小转成屏幕坐标大小
     */
    CCSize mapToScreenSize(int l ,int b ,int h);
    
    /**
     * 根据物体在地图坐标的大小计算其在显示的时候屏幕坐标的锚点
     * 如果是opengl坐标系，则对齐点在中下，和屏幕坐标系统不同。如果是opengl，则不需要转换锚点。
     */
    CCPoint mapToScreenAnchor(int l ,int b ,int h);
    
private:
	int m_xUnit;
	int m_yUnit;
	int m_zUnit;
	
	int m_tileWidth;
	int m_tileHeight;
};





NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_COORDINATE_H_
