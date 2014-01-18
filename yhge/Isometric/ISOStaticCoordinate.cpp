
#include "ISOStaticCoordinate.h"

NS_CC_YHGE_BEGIN

float ISOStaticCoordinate::sTileWidth=64;
float ISOStaticCoordinate::sTileHeight=32;
float ISOStaticCoordinate::sXUnit=32;
float ISOStaticCoordinate::sYUnit=16;
float ISOStaticCoordinate::sZUnit=32;


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