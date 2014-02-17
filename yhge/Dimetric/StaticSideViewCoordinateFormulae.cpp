
#include "StaticSideViewCoordinateFormulae.h"

NS_CC_YHGE_DIMETRIC_BEGIN

#ifndef YHGE_ISO_DEFAULT_TILEWIDTH
#define YHGE_ISO_DEFAULT_TILEWIDTH 48
#endif

#ifndef YHGE_ISO_DEFAULT_TILEHEIGHT
#define YHGE_ISO_DEFAULT_TILEHEIGHT 8
#endif

float StaticSideViewCoordinateFormulae::sTileWidth=YHGE_ISO_DEFAULT_TILEWIDTH;
float StaticSideViewCoordinateFormulae::sTileHeight=YHGE_ISO_DEFAULT_TILEHEIGHT;
float StaticSideViewCoordinateFormulae::sXUnit=YHGE_ISO_DEFAULT_TILEHEIGHT*4;
float StaticSideViewCoordinateFormulae::sYUnit=YHGE_ISO_DEFAULT_TILEHEIGHT*4;
float StaticSideViewCoordinateFormulae::sZUnit=YHGE_ISO_DEFAULT_TILEHEIGHT*4;
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