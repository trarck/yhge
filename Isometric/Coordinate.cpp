//
//  Coordinate.m
//  Dungeons
//
//  Created by trarck trarck on 11-10-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Coordinate.h"

NS_CC_YHGE_BEGIN

static Coordinate* l_coordinate=NULL;

Coordinate::Coordinate()
:m_xUnit(0)
,m_yUnit(0)
,m_zUnit(0)
,m_tileWidth(0)
,m_tileHeight(0)
{
    
}

Coordinate::~Coordinate()
{
    
}


Coordinate* Coordinate::sharedCoordinate()
{
	if(!l_coordinate){
		l_coordinate=new Coordinate();
        l_coordinate->init();
	}
	return l_coordinate;	
}

Coordinate* Coordinate::create()
{
	Coordinate* pRet=new Coordinate();
	if (pRet && pRet->init()){ 
        pRet->autorelease(); 
        return pRet; 
    }else{ 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    }
}

Coordinate* Coordinate::create(int width,int height)
{
	Coordinate* pRet=new Coordinate();
	if (pRet && pRet->init(width,height)){ 
        pRet->autorelease(); 
        return pRet; 
    }else{ 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    }
}

Coordinate* Coordinate::create(int xUnit,int yUnit,int zUnit)
{
	Coordinate* pRet=new Coordinate();
	if (pRet && pRet->init(xUnit,yUnit,zUnit)){ 
        pRet->autorelease(); 
        return pRet; 
    }else{ 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    }
}

void Coordinate::setTileSize(int width ,int height)
{
	m_tileWidth=width;
	m_tileHeight=height;
	
	m_xUnit=width/2;
	m_yUnit=height/2;
	m_zUnit=height;
}

void Coordinate::setCoordinateUnit(int xUnit ,int yUnit ,int zUnit)
{
	m_xUnit=xUnit;
	m_yUnit=yUnit;
	m_zUnit=zUnit;
	
	m_tileWidth=xUnit*2;
	m_tileHeight=yUnit*2;
}

CCSize Coordinate::mapToScreenSize(int l ,int b ,int h)
{
	int s;
	float width,height;
	CCSize size;
	
	s=l+b;
	width=s*m_xUnit;
	height=s*m_yUnit+h*m_zUnit;
	size.width=width;
	size.height=height;
	return size;
}

CCPoint Coordinate::mapToScreenAnchor(int l ,int b ,int h)
{
	CCPoint p;
	p.x=b*m_xUnit;
	p.y=h*m_zUnit;
	return p;
}

NS_CC_YHGE_END
