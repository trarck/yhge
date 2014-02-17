
#include "ISOStaticCoordinateFormulae.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

#ifndef YHGE_ISO_DEFAULT_TILEWIDTH
#define YHGE_ISO_DEFAULT_TILEWIDTH 64
#endif

#ifndef YHGE_ISO_DEFAULT_TILEHEIGHT
#define YHGE_ISO_DEFAULT_TILEHEIGHT 32
#endif

float ISOStaticCoordinateFormulae::sTileWidth=YHGE_ISO_DEFAULT_TILEWIDTH;
float ISOStaticCoordinateFormulae::sTileHeight=YHGE_ISO_DEFAULT_TILEHEIGHT;
float ISOStaticCoordinateFormulae::sXUnit=YHGE_ISO_DEFAULT_TILEWIDTH/2;
float ISOStaticCoordinateFormulae::sYUnit=YHGE_ISO_DEFAULT_TILEHEIGHT;
float ISOStaticCoordinateFormulae::sZUnit=YHGE_ISO_DEFAULT_TILEHEIGHT;
float ISOStaticCoordinateFormulae::sHalfYUnit=YHGE_ISO_DEFAULT_TILEHEIGHT/2;


void ISOStaticCoordinateFormulae::initTileSize(float tileWidth,float tileHeight)
{
	sTileWidth=tileWidth;
	sTileHeight=tileHeight;

	sXUnit=tileWidth/2;
	sYUnit=tileHeight;
	sZUnit=tileHeight;
    sHalfYUnit=sYUnit/2;
}

void ISOStaticCoordinateFormulae::initCoordinateUnit(float xUnit,float yUnit,float zUnit)
{
	sXUnit=xUnit;
	sYUnit=yUnit;
	sZUnit=zUnit;
    sHalfYUnit=sYUnit/2;

	sTileWidth=xUnit+yUnit;
	sTileHeight=sTileWidth/2;//(xUnit+yUnit)/2;
}

NS_CC_YHGE_ISOMETRIC_END