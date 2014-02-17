//
//  Coordinate.m
//  Dungeons
//
//  Created by trarck trarck on 11-10-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Coordinate.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

static Coordinate* l_coordinate=NULL;

Coordinate::Coordinate()
:m_xUnit(0)
,m_yUnit(0)
,m_zUnit(0)
,m_halfYUnit(0)
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

Coordinate* Coordinate::create(float width,float height)
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

Coordinate* Coordinate::create(float xUnit,float yUnit,float zUnit)
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

void Coordinate::setTileSize(float width ,float height)
{
	m_tileWidth=width;
	m_tileHeight=height;
	
	m_xUnit=width/2;
	m_yUnit=height;
	m_zUnit=height;
    m_halfYUnit=m_yUnit/2;
}

void Coordinate::setCoordinateUnit(float xUnit ,float yUnit ,float zUnit)
{
	m_xUnit=xUnit;
	m_yUnit=yUnit;
	m_zUnit=zUnit;
    m_halfYUnit=m_yUnit/2;
	
	m_tileWidth=xUnit+yUnit;
	m_tileHeight=m_tileWidth/2;//(xUnit+yUnit)/2
}

CCSize Coordinate::mapToScreenSize(int l ,int b ,int h)
{
	int s;
	float width,height;
	CCSize size;
	
	s=l+b;
	width=s*m_xUnit;
	height=s*m_halfYUnit+h*m_zUnit;
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

NS_CC_YHGE_ISOMETRIC_END
