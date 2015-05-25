/**
 *  上视角斜边形映射公式
 */

#ifndef YHGE_DIMETRIC_STATICTOPVIEWCOORDINATEFORMULAE_H_
#define YHGE_DIMETRIC_STATICTOPVIEWCOORDINATEFORMULAE_H_

#include "cocos2d.h"
#include "DimetricMacros.h"


NS_CC_YHGE_DIMETRIC_BEGIN

/*
 @brief formulae
 http://www.compuphase.com/axometr.htm
 
 x,y,z is space coord.left handle coord system.x point left,y point top,z point front
 x',y' is pix coord
 ux,uy,uz is space unit to pix
 
 x'=x*ux+z*uz/4;
 y'=y*uy+z*uz/2;
 
 x=(x'-0.5*(y'-y*uy))/ux;
 z=2(y'-y*uy)/uz
 
 注意实际使用时，y和z要掉换一下。
 */
class StaticTopViewCoordinateFormulae:public Ref
{
public:

	static void initTileSize(float tileWidth,float tileHeight);
 
    /**
     *@brief 通常各分轴单位是一样的。
     */
	static void initCoordinateUnit(float xUnit,float yUnit,float zUnit);

	//==============使用传值的方式==========================//
    
    /**
     * @brief 视图坐标转成游戏坐标
     * 用于选择游戏坐标里的对象
     * @param x 视图的x坐标
     * @param y 视图的y坐标
     * @param z 游戏的z坐标
     * @return 游戏世界的x,y坐标
     */
    static inline Vec2 viewToGame3F(float x,float y,float gameZ)
	{
		Vec2 p;
        p.x=(x-0.5*(y-gameZ*sZUnit))/sXUnit;//x=(x'-0.5*(y'-z*uz))/ux;
		p.y=2*(y-gameZ*sZUnit)/sYUnit;//y=2(y'-z*uz)/uy
		return p;
	}
    
	static inline Vec2 viewToGame2F(float x,float y)
	{
		Vec2 p;
        p.x=(x-0.5*y)/sXUnit;//x=(x'-0.5*(y'-z*uz))/ux;
		p.y=2*y/sYUnit;//y=2(y'-z*uz)/uy
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
		p.x=x*sXUnit+y*sQuarterYUnit;//x'=x*ux+y*uy/4;
		p.y=z*sZUnit+y*sHalfYUnit;//y'=z*uz+y*uy/2;
		return p;
	}

	static inline Vec2 gameToView2F(float x, float y)
	{
		Vec2 p;
		p.x=x*sXUnit+y*sQuarterYUnit;//x'=x*ux+y*uy/4;
		p.y=y*sHalfYUnit;//y'=z*uz+y*uy/2;
		return p;
	}

	static inline Vec2 gameToViewPoint(const Vec2&  point)
	{
		return gameToView2F(point.x,point.y);
	}

	//==============使用传址的方式=====================//

    static inline void viewToGame2FP(float x,float y,float gameZ,Vec2* destPoint)
	{
        destPoint->x=(x-0.5*(y-gameZ*sZUnit))/sXUnit;//x=(x'-0.5*(y'-z*uz))/ux;
		destPoint->y=2*(y-gameZ*sZUnit)/sYUnit;//y=2(y'-z*uz)/uy
	}
    
	static inline void viewToGame2FP(float x,float y,Vec2* destPoint)
	{
        destPoint->x=(x-0.5*y)/sXUnit;//x=(x'-0.5*(y'-z*uz))/ux;
		destPoint->y=2*y/sYUnit;//y=2(y'-z*uz)/uy
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
        destPoint->x=x*sXUnit+y*sQuarterYUnit;//x'=x*ux+y*uy/2;
		destPoint->y=z*sZUnit+y*sHalfYUnit;//y'=z*uz+y*uy/4;
        
	}

	static inline void gameToView2FP(float x, float y,Vec2* destPoint)
	{
		destPoint->x=x*sXUnit+y*sQuarterYUnit;//x'=x*ux+y*uy/4;
		destPoint->y=y*sHalfYUnit;//y'=z*uz+y*uy/2;
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
    static float sQuarterYUnit;
};

NS_CC_YHGE_DIMETRIC_END

#endif //YHGE_DIMETRIC_STATICTOPVIEWCOORDINATEFORMULAE_H_