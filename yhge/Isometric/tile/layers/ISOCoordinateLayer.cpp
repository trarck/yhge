#include "ISOCoordinateLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>

USING_NS_CC;

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOCoordinateLayer::ISOCoordinateLayer()
:_mapWidth(0)
,_mapHeight(0)
,_isShow(true)
,_content(NULL)
{

}

ISOCoordinateLayer::ISOCoordinateLayer(int mapWidth, int mapHeight)
:_mapWidth(mapWidth)
, _mapHeight(mapHeight)
, _isShow(true)
, _content(NULL)
{

}

// on "init" you need to initialize your instance
bool ISOCoordinateLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	_content = DrawNode::create();

	addChild(_content);

    return true;
}


ISOCoordinateLayer* ISOCoordinateLayer::create(int mapWidth, int mapHeight)
{
	ISOCoordinateLayer* coordinateLayer = new ISOCoordinateLayer(mapWidth,mapHeight);
	
	if (coordinateLayer->init()){
		coordinateLayer->autorelease();
		return coordinateLayer;
	}else{
		delete coordinateLayer;
		coordinateLayer = NULL;
		return NULL;
	}

}

void ISOCoordinateLayer::show()
{
	if(_isShow){
		int i,j;
		Vec2 to;
		Vec2 from;
		Color4F color = Color4F(1.0f,0,0,1.0f);

		ccDrawColor4B(255,0,0,255);
		//draw xias
		for(i=0;i<=_mapWidth;i++){
			from=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(i,0));
			to=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(i,_mapHeight));
			
			_content->drawLine(from, to, color);
		}
		//draw yias
		for(j=0;j<=_mapHeight;j++){
			from=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(0,j));
			to=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(_mapWidth,j));
			
			_content->drawLine(from, to, color);
		}
	}
}

void ISOCoordinateLayer::showCoordinate(bool isShow)
{
	_isShow=isShow;
}


void ISOCoordinateLayer::setMapWidth(int iMapWidth)
{
    _mapWidth = iMapWidth;
}

int ISOCoordinateLayer::getMapWidth()
{
    return _mapWidth;
}

void ISOCoordinateLayer::setMapHeight(int iMapHeight)
{
    _mapHeight = iMapHeight;
}

int ISOCoordinateLayer::getMapHeight()
{
    return _mapHeight;
}

NS_CC_YHGE_ISOMETRIC_END