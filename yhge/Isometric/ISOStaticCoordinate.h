/*
 *  
 *  使用基于2的幂次方的数值，乘除直接使用位移操作
 *  每个游戏的tile大小都是固定的，直接定义好，可以提高效率
 *  Created by trarck trarck on 11-11-8.
 *  Copyright 2011 yitengku.com. All rights reserved.
 *
 */

#ifndef YHGE_ISOMETRIC_ISOSTATICCOORDINATE_H_
#define YHGE_ISOMETRIC_ISOSTATICCOORDINATE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>


NS_CC_YHGE_BEGIN

class ISOStaticCoordinate:public CCObject
{
public:

	static void initTileSize(float tileWidth,float tileHeight);
 
	static void initCoordinateUnit(float xUnit,float yUnit,float zUnit);

	//==============使用传值的方式==========================//
	static inline CCPoint isoViewToGame2F(float x,float y)
	{
		CCPoint p;
		x=x/sTileWidth;//x=x/64
		y=y/sTileHeight;//y=y/32
		p.x=x+y;
		p.y=y-x;
		return p;
	}

	static inline CCPoint isoViewToGamePoint(const CCPoint& point)
	{
		return isoViewToGame2F(point.x,point.y);
	}

	static inline CCPoint isoViewToGameGrid2F (float x,float  y)
	{
		CCPoint p=isoViewToGame2F(x,y);
		p.x=floor(p.x);
		p.y=floor(p.y);
		return p;
	}

	static inline CCPoint isoViewToGameGridPoint (const CCPoint& point)
	{
		return isoViewToGameGrid2F(point.x,point.y);
	}

	static inline CCPoint isoViewToGameCell2F (float x,float  y)
	{
		CCPoint p=isoViewToGame2F(x,y);
		p.x=(int)p.x;
		p.y=(int)p.y;
		return p;
	}


	static inline CCPoint isoGameToView3F(float x ,float y ,float z)
	{
		double sx=x-y,sy=x+y;
		CCPoint p;
		p.x=sx*sXUnit;//sx*32
		p.y=sy*sYUnit-z*sZUnit;//sy*16-z*32
		return p;
	}

	static inline CCPoint isoGameToView2F(float x, float y)
	{
		double sx=x-y,sy=x+y;
		CCPoint p;
		p.x=sx*sXUnit;//sx*32
		p.y=sy*sYUnit;//sy*16
		return p;
	}

	static inline CCPoint isoGameToViewPoint(const CCPoint&  point)
	{
		return isoGameToView2F(point.x,point.y);
	}

	//==============使用传址的方式=====================//

	static inline void isoViewToGame2FP(float x,float y,CCPoint* destPoint)
	{
		x=x/sTileWidth;//x=x/64
		y=y/sTileHeight;//y=y/32
		destPoint->x=x+y;
		destPoint->y=y-x;
	}

	static inline void isoViewToGamePointP(const CCPoint& point,CCPoint* destPoint)
	{
		isoViewToGame2FP(point.x,point.y,destPoint);
	}

	static inline void isoViewToGameGrid2FP(float x,float  y,CCPoint* destPoint)
	{
		isoViewToGame2FP(x,y,destPoint);
		destPoint->x=floor(destPoint->x);
		destPoint->y=floor(destPoint->y);
	}

	static inline void isoViewToGameGridPointP (const CCPoint& point,CCPoint* destPoint)
	{
		isoViewToGameGrid2FP(point.x,point.y,destPoint);
	}

	static inline void isoViewToGameCell2FP(float x,float  y,CCPoint* destPoint)
	{
		isoViewToGame2FP(x,y,destPoint);
		destPoint->x=(int)destPoint->x;
		destPoint->y=(int)destPoint->y;
	}


	static inline void isoGameToView3FP(float x ,float y ,float z,CCPoint* destPoint)
	{
		double sx=x-y,sy=x+y;
		destPoint->x=sx*sXUnit;//sx*32
		destPoint->y=sy*sYUnit-z*sZUnit;//sy*16-z*32
	}

	static inline void isoGameToView2FP(float x, float y,CCPoint* destPoint)
	{
		double sx=x-y,sy=x+y;
		destPoint->x=sx*sXUnit;//sx*32
		destPoint->y=sy*sYUnit;//sy*16
	}

	static inline void isoGameToViewPointP(const CCPoint&  point,CCPoint* destPoint)
	{
		isoGameToView2FP(point.x,point.y,destPoint);
	}

public:

	static float sTileWidth;
	static float sTileHeight;
	static float sXUnit;
	static float sYUnit;
	static float sZUnit;
};

NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOSTATICCOORDINATE_H_