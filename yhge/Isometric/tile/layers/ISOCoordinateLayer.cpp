#include "ISOCoordinateLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>

USING_NS_CC;

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOCoordinateLayer::ISOCoordinateLayer()
:m_iMapWidth(0)
,m_iMapHeight(0)
,m_bIsShow(true)
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
	if(m_bIsShow){
		int i,j;
		CCPoint to;
		CCPoint from;

		ccDrawColor4B(255,0,0,255);
		//draw xias
		for(i=0;i<=m_iMapWidth;i++){
			from=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(i,0));
			to=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(i,m_iMapHeight));
			
			ccDrawLine( from, to );
		}
		//draw yias
		for(j=0;j<=m_iMapHeight;j++){
			from=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(0,j));
			to=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(m_iMapWidth,j));
			
			ccDrawLine( from, to );
		}
	}
}

void ISOCoordinateLayer::showCoordinate(bool isShow)
{
	m_bIsShow=isShow;
}


void ISOCoordinateLayer::setMapWidth(int iMapWidth)
{
    m_iMapWidth = iMapWidth;
}

int ISOCoordinateLayer::getMapWidth()
{
    return m_iMapWidth;
}

void ISOCoordinateLayer::setMapHeight(int iMapHeight)
{
    m_iMapHeight = iMapHeight;
}

int ISOCoordinateLayer::getMapHeight()
{
    return m_iMapHeight;
}

NS_CC_YHGE_ISOMETRIC_END