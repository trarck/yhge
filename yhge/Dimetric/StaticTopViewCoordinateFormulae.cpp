
#include "StaticTopViewCoordinateFormulae.h"

NS_CC_YHGE_DIMETRIC_BEGIN

#ifndef YHGE_ISO_DEFAULT_TILEWIDTH
#define YHGE_ISO_DEFAULT_TILEWIDTH 48
#endif

#ifndef YHGE_ISO_DEFAULT_TILEHEIGHT
#define YHGE_ISO_DEFAULT_TILEHEIGHT 8
#endif

float StaticTopViewCoordinateFormulae::sTileWidth=YHGE_ISO_DEFAULT_TILEWIDTH;
float StaticTopViewCoordinateFormulae::sTileHeight=YHGE_ISO_DEFAULT_TILEHEIGHT;
float StaticTopViewCoordinateFormulae::sXUnit=YHGE_ISO_DEFAULT_TILEHEIGHT*4;
float StaticTopViewCoordinateFormulae::sYUnit=YHGE_ISO_DEFAULT_TILEHEIGHT*4;
float StaticTopViewCoordinateFormulae::sZUnit=YHGE_ISO_DEFAULT_TILEHEIGHT*4;
float StaticTopViewCoordinateFormulae::sHalfYUnit=sYUnit/2;
float StaticTopViewCoordinateFormulae::sQuarterYUnit=sYUnit/4;

void StaticTopViewCoordinateFormulae::initTileSize(float tileWidth,float tileHeight)
{
	sTileWidth=tileWidth;
	sTileHeight=tileHeight;

	sXUnit=tileHeight*4;
	sYUnit=tileHeight*4;
	sZUnit=tileHeight*4;
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

	sTileWidth=xUnit+sHalfYUnit;
	sTileHeight=sQuarterYUnit;
}

NS_CC_YHGE_DIMETRIC_END