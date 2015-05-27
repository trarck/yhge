#include "ISOCoordinateLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>

USING_NS_CC;

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOCoordinateLayer::ISOCoordinateLayer()
:_iMapWidth(0)
,_iMapHeight(0)
,_isShow(true)
{

}

// on "init" you need to initialize your instance
bool ISOCoordinateLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    return true;
}

void ISOCoordinateLayer::draw()
{
	if(_isShow){
		int i,j;
		Vec2 to;
		Vec2 from;

		ccDrawColor4B(255,0,0,255);
		//draw xias
		for(i=0;i<=_iMapWidth;i++){
			from=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(i,0));
			to=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(i,_iMapHeight));
			
			ccDrawLine( from, to );
		}
		//draw yias
		for(j=0;j<=_iMapHeight;j++){
			from=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(0,j));
			to=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(_iMapWidth,j));
			
			ccDrawLine( from, to );
		}
	}
}

void ISOCoordinateLayer::showCoordinate(bool isShow)
{
	_isShow=isShow;
}


void ISOCoordinateLayer::setMapWidth(int iMapWidth)
{
    _iMapWidth = iMapWidth;
}

int ISOCoordinateLayer::getMapWidth()
{
    return _iMapWidth;
}

void ISOCoordinateLayer::setMapHeight(int iMapHeight)
{
    _iMapHeight = iMapHeight;
}

int ISOCoordinateLayer::getMapHeight()
{
    return _iMapHeight;
}

NS_CC_YHGE_ISOMETRIC_END