/*
 *  CISOCoordinate.h
 *  
 *  使用基于2的幂次方的数值，乘除直接使用位移操作
 *  每个游戏的tile大小都是固定的，直接定义好，可以提高效率
 *  Created by trarck trarck on 11-11-8.
 *  Copyright 2011 yitengku.com. All rights reserved.
 *
 */

#ifndef YHGE_ISOMETRIC_ISOCOORDINATE_H_
#define YHGE_ISOMETRIC_ISOCOORDINATE_H_

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

#ifndef XUnit
#define XUnit TileWidth/2 
#endif

#ifndef YUnit
#define YUnit TileHeight/2 
#endif

#ifndef ZUnit
#define ZUnit TileHeight 
#endif
//tileWidth=64,tileHeight=32

NS_CC_YHGE_BEGIN

typedef struct T_CCPointF{
	float x;
    float y;
} ISOPointF;

typedef struct T_CCPointI{
	int x;
    int y;
} ISOPointI;

static int sTileWidth=0,sTileHeight=0,sXUnit=0,sYUnit=0,sZUnit=0;

static inline void initTileSize(int tileWidth,int tileHeight)
{
	sTileWidth=tileWidth;
	sTileHeight=tileHeight;

	sXUnit=tileWidth/2;
	sYUnit=tileHeight/2;
	sZUnit=tileHeight;
}

static inline void initCoordinateUnit(int xUnit,int yUnit,int zUnit)
{
	sXUnit=xUnit;
	sYUnit=yUnit;
	sZUnit=zUnit;

	sTileWidth=xUnit*2;
	sTileHeight=yUnit*2;
}

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
	p.y=sy*YUnit-z*ZUnit;//sy*16-z*32
	return p;
}

static inline CCPoint isoGameToView2F(float x, float y)
{
	double sx=x-y,sy=x+y;
	CCPoint p;
	p.x=sx*XUnit;//sx*32
	p.y=sy*YUnit;//sy*16
	return p;
}

static inline CCPoint isoGameToViewPoint(const CCPoint&  point)
{
	return isoGameToView2F(point.x,point.y);
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
	destPoint->y=sy*YUnit-z*ZUnit;//sy*16-z*32
}

static inline void isoGameToView2FP(float x, float y,CCPoint* destPoint)
{
	double sx=x-y,sy=x+y;
	destPoint->x=sx*XUnit;//sx*32
	destPoint->y=sy*YUnit;//sy*16
}

static inline void isoGameToViewPointP(const CCPoint&  point,CCPoint* destPoint)
{
	isoGameToView2FP(point.x,point.y,destPoint);
}

NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOCOORDINATE_H_