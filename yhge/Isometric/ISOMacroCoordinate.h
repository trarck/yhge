/*
 *  ISOCoordinate.h
 *  
 *  使用基于2的幂次方的数值，乘除直接使用位移操作
 *  每个游戏的tile大小都是固定的，直接定义好，可以提高效率
 *  Created by trarck trarck on 11-11-8.
 *  Copyright 2011 yitengku.com. All rights reserved.
 *
 */

#ifndef YHGE_ISOMETRIC_ISOMACROCOORDINATE_H_
#define YHGE_ISOMETRIC_ISOMACROCOORDINATE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

//tile width 
#ifndef TileWidth
#define TileWidth 64
#endif
//tile height
#ifndef TileHeight
#define TileHeight 32
#endif

//MapUnit，一个地图坐标单元的地图坐标像素值
#ifndef MapUnit
#define MapUnit TileHeight 
#endif

//XUnit,YUnit,ZUnit都是屏幕坐标值
#ifndef XUnit
#define XUnit TileWidth/2 
#endif

#ifndef YUnit
#define YUnit TileHeight
#endif

#ifndef HalfYUnit
#define HalfYUnit YUnit/2
#endif

#ifndef ZUnit
#define ZUnit TileHeight 
#endif
//tileWidth=64,tileHeight=32

NS_CC_YHGE_BEGIN

//==============使用传值的方式==========================//
static inline CCPoint isoViewToGame2F(float x,float y)
{
	CCPoint p;
	x=x/TileWidth;//x=x/64
	y=y/TileHeight;//y=y/32
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
	p.x=sx*XUnit;//sx*32
	p.y=sy*HalfYUnit-z*ZUnit;//sy*16-z*32
	return p;
}

static inline CCPoint isoGameToView2F(float x, float y)
{
	double sx=x-y,sy=x+y;
	CCPoint p;
	p.x=sx*XUnit;//sx*32
	p.y=sy*HalfYUnit;//sy*16
	return p;
}

static inline CCPoint isoGameToViewPoint(const CCPoint&  point)
{
	return isoGameToView2F(point.x,point.y);
}

//只取得y方向的值,通常用于遮挡值
static inline float isoGameToViewY3F(float x ,float y ,float z)
{
	double sy=x+y;
	sy=sy*HalfYUnit-z*ZUnit;//sy*16-z*32
	return sy;
}

//只取得y方向的值,通常用于遮挡值
static inline float isoGameToViewY2F(float x, float y)
{
	return (x+y)*HalfYUnit;//sy=x+y;sy*16
}

//只取得y方向的值,通常用于遮挡值
static inline float isoGameToViewYPoint(const CCPoint&  point)
{
	return isoGameToViewY2F(point.x,point.y);
}

//==============使用传址的方式=====================//

static inline void isoViewToGame2FP(float x,float y,CCPoint* destPoint)
{
	x=x/TileWidth;//x=x/64
	y=y/TileHeight;//y=y/32
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
	destPoint->x=sx*XUnit;//sx*32
	destPoint->y=sy*HalfYUnit-z*ZUnit;//sy*16-z*32
}

static inline void isoGameToView2FP(float x, float y,CCPoint* destPoint)
{
	double sx=x-y,sy=x+y;
	destPoint->x=sx*XUnit;//sx*32
	destPoint->y=sy*HalfYUnit;//sy*16
}

static inline void isoGameToViewPointP(const CCPoint&  point,CCPoint* destPoint)
{
	isoGameToView2FP(point.x,point.y,destPoint);
}

NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOMACROCOORDINATE_H_