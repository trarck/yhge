
#include "StaticTopViewCoordinateFormulae.h"

NS_CC_YHGE_DIMETRIC_BEGIN

// height:with = 2:5
static const float kDimetricTopViewDefaultTileWidth=40.0f;
static const float kDimetricTopViewDefaultTileHeight=16.0f;

float StaticTopViewCoordinateFormulae::sTileWidth=kDimetricTopViewDefaultTileWidth;
float StaticTopViewCoordinateFormulae::sTileHeight=kDimetricTopViewDefaultTileHeight;
float StaticTopViewCoordinateFormulae::sXUnit=kDimetricTopViewDefaultTileHeight*2;
float StaticTopViewCoordinateFormulae::sYUnit=kDimetricTopViewDefaultTileHeight*2;
float StaticTopViewCoordinateFormulae::sZUnit=kDimetricTopViewDefaultTileHeight*2;
float StaticTopViewCoordinateFormulae::sHalfYUnit=sYUnit/2;
float StaticTopViewCoordinateFormulae::sQuarterYUnit=sYUnit/4;

void StaticTopViewCoordinateFormulae::initTileSize(float tileWidth,float tileHeight)
{
	sTileWidth=tileWidth;
	sTileHeight=tileHeight;

	sXUnit=tileHeight*2;
	sYUnit=tileHeight*2;
	sZUnit=tileHeight*2;
    sHalfYUnit=sYUnit/2;
    sQuarterYUnit=sYUnit/4;
}

void StaticTopViewCoordinateFormulae::initCoordinateUnit(float xUnit,float yUnit,float zUnit)
{
	sXUnit=xUnit;
	sYUnit=yUnit;
	sZUnit=zUnit;
    sHalfYUnit=sYUnit/2;
    sQuarterYUnit=sYUnit/4;

	sTileWidth=xUnit+sQuarterYUnit;
	sTileHeight=sHalfYUnit;
}

NS_CC_YHGE_DIMETRIC_END