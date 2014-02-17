
#include "ISOStaticCoordinate.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

#ifndef YHGE_ISO_DEFAULT_TILEWIDTH
#define YHGE_ISO_DEFAULT_TILEWIDTH 64
#endif

#ifndef YHGE_ISO_DEFAULT_TILEHEIGHT
#define YHGE_ISO_DEFAULT_TILEHEIGHT 32
#endif

float ISOStaticCoordinate::sTileWidth=YHGE_ISO_DEFAULT_TILEWIDTH;
float ISOStaticCoordinate::sTileHeight=YHGE_ISO_DEFAULT_TILEHEIGHT;
float ISOStaticCoordinate::sXUnit=YHGE_ISO_DEFAULT_TILEWIDTH/2;
float ISOStaticCoordinate::sYUnit=YHGE_ISO_DEFAULT_TILEHEIGHT;
float ISOStaticCoordinate::sZUnit=YHGE_ISO_DEFAULT_TILEHEIGHT;
float ISOStaticCoordinate::sHalfYUnit=YHGE_ISO_DEFAULT_TILEHEIGHT/2;


void ISOStaticCoordinate::initTileSize(float tileWidth,float tileHeight)
{
	sTileWidth=tileWidth;
	sTileHeight=tileHeight;

	sXUnit=tileWidth/2;
	sYUnit=tileHeight;
	sZUnit=tileHeight;
    sHalfYUnit=sYUnit/2;
}

void ISOStaticCoordinate::initCoordinateUnit(float xUnit,float yUnit,float zUnit)
{
	sXUnit=xUnit;
	sYUnit=yUnit;
	sZUnit=zUnit;
    sHalfYUnit=sYUnit/2;

	sTileWidth=xUnit+yUnit;
	sTileHeight=sTileWidth/2;//(xUnit+yUnit)/2;
}

NS_CC_YHGE_ISOMETRIC_END