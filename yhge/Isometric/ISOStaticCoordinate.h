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
#include "IsometricMacros.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 @brief formulae
 x,y,z is space coord.left handle coord system.x point left,y point top,z point front
 x',y' is pix coord
 ux,uy,uz is space unit to pix
 
 x'=x*ux-z*uz;
 y'=y*uy+(x*ux+z*uz)/2;
 
 x=(x'/2+y'-y)/ux;
 z=(-x'/2+y'-y)/uz
 
 如果单位坐标值相等
 x=x'/TileWidth+y'/TileHeight;
 z=-x'/TileWidth+y'/TileHeight;
 */
class ISOStaticCoordinate:public Ref
{
public:

	static void initTileSize(float tileWidth,float tileHeight);
 
    /**
     *@brief 通常各分轴单位是一样的。
     */
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

	static inline CCPoint isoViewToGameCell2F (float x,float  y)
	{
		CCPoint p=isoViewToGame2F(x,y);
		p.x=floor(p.x);
		p.y=floor(p.y);
		return p;
	}

	static inline CCPoint isoViewToGameCellPoint (const CCPoint& point)
	{
		return isoViewToGameCell2F(point.x,point.y);
	}

	static inline CCPoint isoGameToView3F(float x ,float y ,float z)
	{
		double sx=x-y,sy=x+y;
		CCPoint p;
		p.x=sx*sXUnit;//sx*32
		p.y=sy*sHalfYUnit-z*sZUnit;//sy*16-z*32
		return p;
	}

	static inline CCPoint isoGameToView2F(float x, float y)
	{
		double sx=x-y,sy=x+y;
		CCPoint p;
		p.x=sx*sXUnit;//sx*32
		p.y=sy*sHalfYUnit;//sy*16
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

	static inline void isoViewToGameCell2FP(float x,float  y,CCPoint* destPoint)
	{
		isoViewToGame2FP(x,y,destPoint);
		destPoint->x=floor(destPoint->x);
		destPoint->y=floor(destPoint->y);
	}

	static inline void isoViewToGameCellPointP (const CCPoint& point,CCPoint* destPoint)
	{
		isoViewToGameCell2FP(point.x,point.y,destPoint);
	}

	static inline void isoGameToView3FP(float x ,float y ,float z,CCPoint* destPoint)
	{
		double sx=x-y,sy=x+y;
		destPoint->x=sx*sXUnit;//sx*32
		destPoint->y=sy*sHalfYUnit-z*sZUnit;//sy*16-z*32
	}

	static inline void isoGameToView2FP(float x, float y,CCPoint* destPoint)
	{
		double sx=x-y,sy=x+y;
		destPoint->x=sx*sXUnit;//sx*32
		destPoint->y=sy*sHalfYUnit;//sy*16
	}

	static inline void isoGameToViewPointP(const CCPoint&  point,CCPoint* destPoint)
	{
		isoGameToView2FP(point.x,point.y,destPoint);
	}

public:

	static float sTileWidth;
	static float sTileHeight;
    //空间坐标的单位，对应空间的像素值。正常坐标系下，x,y,z单位值是一致的。
	static float sXUnit;
	static float sYUnit;
	static float sZUnit;
    static float sHalfYUnit;
};

NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOSTATICCOORDINATE_H_