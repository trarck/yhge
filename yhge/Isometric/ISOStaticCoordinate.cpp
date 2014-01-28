
#include "ISOStaticCoordinate.h"

NS_CC_YHGE_BEGIN

#ifndef YHGE_ISO_DEFAULT_TILEWIDTH
#define YHGE_ISO_DEFAULT_TILEWIDTH 64
#endif

#ifndef YHGE_ISO_DEFAULT_TILEHEIGHT
#define YHGE_ISO_DEFAULT_TILEHEIGHT 32
#endif

float ISOStaticCoordinate::sTileWidth=YHGE_ISO_DEFAULT_TILEWIDTH;
float ISOStaticCoordinate::sTileHeight=YHGE_ISO_DEFAULT_TILEHEIGHT;
float ISOStaticCoordinate::sXUnit=YHGE_ISO_DEFAULT_TILEWIDTH/2;
float ISOStaticCoordinate::sYUnit=YHGE_ISO_DEFAULT_TILEHEIGHT/2;
float ISOStaticCoordinate::sZUnit=YHGE_ISO_DEFAULT_TILEHEIGHT;


void ISOStaticCoordinate::initTileSize(int tileWidth,int tileHeight)
{
	sTileWidth=tileWidth;
	sTileHeight=tileHeight;

	sXUnit=tileWidth/2;
	sYUnit=tileHeight/2;
	sZUnit=tileHeight;
}

void ISOStaticCoordinate::initCoordinateUnit(int xUnit,int yUnit,int zUnit)
{
	sXUnit=xUnit;
	sYUnit=yUnit;
	sZUnit=zUnit;

	sTileWidth=xUnit*2;
	sTileHeight=yUnit*2;
}

NS_CC_YHGE_END