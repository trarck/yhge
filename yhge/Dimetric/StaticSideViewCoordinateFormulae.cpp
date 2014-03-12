
#include "StaticSideViewCoordinateFormulae.h"

NS_CC_YHGE_DIMETRIC_BEGIN

// height:with = 1:6
static const float kDimetricSideViewDefaultTileWidth=48.0f;
static const float kDimetricSideViewDefaultTileHeight=8;

float StaticSideViewCoordinateFormulae::sTileWidth=kDimetricSideViewDefaultTileWidth;
float StaticSideViewCoordinateFormulae::sTileHeight=kDimetricSideViewDefaultTileHeight;
float StaticSideViewCoordinateFormulae::sXUnit=kDimetricSideViewDefaultTileHeight*4;
float StaticSideViewCoordinateFormulae::sYUnit=kDimetricSideViewDefaultTileHeight*4;
float StaticSideViewCoordinateFormulae::sZUnit=kDimetricSideViewDefaultTileHeight*4;
float StaticSideViewCoordinateFormulae::sHalfYUnit=sYUnit/2;
float StaticSideViewCoordinateFormulae::sQuarterYUnit=sYUnit/4;

void StaticSideViewCoordinateFormulae::initTileSize(float tileWidth,float tileHeight)
{
	sTileWidth=tileWidth;
	sTileHeight=tileHeight;

	sXUnit=tileHeight*4;
	sYUnit=tileHeight*4;
	sZUnit=tileHeight*4;
    sHalfYUnit=sYUnit/2;
    sQuarterYUnit=sYUnit/4;
}

void StaticSideViewCoordinateFormulae::initCoordinateUnit(float xUnit,float yUnit,float zUnit)
{
	sXUnit=xUnit;
	sYUnit=yUnit;
	sZUnit=zUnit;
    sHalfYUnit=sYUnit/2;
    sQuarterYUnit=sYUnit/4;

	sTileWidth=xUnit+sHalfYUnit;
	sTileHeight=sQuarterYUnit;
}

NS_CC_YHGE_DIMETRIC_END