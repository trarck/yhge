﻿/*
 *  
 * 使用标准的计算公式。
 * 适用游戏世界坐标各单位分量不相等。这种情况基本不会遇到
 *
 */

#ifndef YHGE_ISOMETRIC_ISOSTATICCOORDINATEFORMULAE_H_
#define YHGE_ISOMETRIC_ISOSTATICCOORDINATEFORMULAE_H_

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
 
 x=(x'/2+y'-y*uy)/ux;
 z=(-x'/2+y'-y*uy)/uz
 
 如果单位坐标值相等
 x=x'/TileWidth+y'/TileHeight;
 z=-x'/TileWidth+y'/TileHeight;
 */
class ISOStaticCoordinateFormulae:public Ref
{
public:

	static void initTileSize(float tileWidth,float tileHeight);
 
    /**
     *@brief 通常各分轴单位是一样的。
     */
	static void initCoordinateUnit(float xUnit,float yUnit,float zUnit);

	//==============使用传值的方式==========================//
    static inline Vec2 viewToGame3F(float x,float y,float gameZ)
	{
		Vec2 p;
		p.x=(x*0.5+y-gameZ*sZUnit)/sXUnit;//x=(x'/2+y'-z*uz)/ux;
		p.y=(y-0.5*x-gameZ*sZUnit)/sYUnit;//y=(-x'/2+y'-z*uz)/uy
		return p;
	}
    
	static inline Vec2 viewToGame2F(float x,float y)
	{
		Vec2 p;
		p.x=(x*0.5+y)/sXUnit;//x=(x'/2+y'-z*uz)/ux;
		p.y=(y-0.5*x)/sYUnit;//y=(-x'/2+y'-z*uz)/uy
		return p;
	}

	static inline Vec2 viewToGamePoint(const Vec2& point)
	{
		return viewToGame2F(point.x,point.y);
	}

	static inline Vec2 viewToGameCell2F (float x,float  y)
	{
		Vec2 p=viewToGame2F(x,y);
		p.x=floor(p.x);
		p.y=floor(p.y);
		return p;
	}

	static inline Vec2 viewToGameCellPoint (const Vec2& point)
	{
		return viewToGameCell2F(point.x,point.y);
	}

	static inline Vec2 gameToView3F(float x ,float y ,float z)
	{
		Vec2 p;
		p.x=(x*sXUnit-y*sYUnit);//x'=x*ux-y*uy;
		p.y=(0.5*(x*sXUnit+y*sYUnit)+z*sZUnit);//y'=z*uz+(x*ux+y*uy)/2;
		return p;
	}

	static inline Vec2 gameToView2F(float x, float y)
	{
		Vec2 p;
		p.x=(x*sXUnit-y*sYUnit);//x'=x*ux-y*uy;
		p.y=0.5*(x*sXUnit+y*sYUnit);//y'=z*uz+(x*ux+y*uy)/2;
		return p;
	}

	static inline Vec2 gameToViewPoint(const Vec2&  point)
	{
		return gameToView2F(point.x,point.y);
	}

	//==============使用传址的方式=====================//

    static inline void viewToGame3FP(float x,float y,float gameZ,Vec2* destPoint)
	{
        destPoint->x=(x*0.5+y-gameZ*sZUnit)/sXUnit;//x=(x'/2+y'-z*uz)/ux;
		destPoint->y=(y-0.5*x-gameZ*sZUnit)/sYUnit;//y=(-x'/2+y'-z*uz)/uy
	}
    
	static inline void viewToGame2FP(float x,float y,Vec2* destPoint)
	{
		destPoint->x=(x*0.5+y)/sXUnit;//x=(x'/2+y'-z)/ux;
		destPoint->y=(y-0.5*x)/sYUnit;//y=(-x'/2+y'-z)/uy
	}

	static inline void viewToGamePointP(const Vec2& point,Vec2* destPoint)
	{
		viewToGame2FP(point.x,point.y,destPoint);
	}

	static inline void viewToGameCell2FP(float x,float  y,Vec2* destPoint)
	{
		viewToGame2FP(x,y,destPoint);
		destPoint->x=floor(destPoint->x);
		destPoint->y=floor(destPoint->y);
	}

	static inline void viewToGameCellPointP (const Vec2& point,Vec2* destPoint)
	{
		viewToGameCell2FP(point.x,point.y,destPoint);
	}

	static inline void gameToView3FP(float x ,float y ,float z,Vec2* destPoint)
	{
        destPoint->x=(x*sXUnit-y*sYUnit);//x'=x*ux-y*uy;
		destPoint->y=(0.5*(x*sXUnit+y*sYUnit)+z*sZUnit);//y'=z*uz+(x*ux+y*uy)/2;
    }

	static inline void gameToView2FP(float x, float y,Vec2* destPoint)
	{
        destPoint->x=(x*sXUnit-y*sYUnit);//x'=x*ux-y*uy;
		destPoint->y=0.5*(x*sXUnit+y*sYUnit);//y'=z*uz+(x*ux+y*uy)/2;
	}

	static inline void gameToViewPointP(const Vec2&  point,Vec2* destPoint)
	{
		gameToView2FP(point.x,point.y,destPoint);
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