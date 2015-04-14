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
:_xUnit(0)
,_yUnit(0)
,_zUnit(0)
,_halfYUnit(0)
,_tileWidth(0)
,_tileHeight(0)
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
	_tileWidth=width;
	_tileHeight=height;
	
	_xUnit=width/2;
	_yUnit=height;
	_zUnit=height;
    _halfYUnit=_yUnit/2;
}

void Coordinate::setCoordinateUnit(float xUnit ,float yUnit ,float zUnit)
{
	_xUnit=xUnit;
	_yUnit=yUnit;
	_zUnit=zUnit;
    _halfYUnit=_yUnit/2;
	
	_tileWidth=xUnit+yUnit;
	_tileHeight=_tileWidth/2;//(xUnit+yUnit)/2
}

CCSize Coordinate::mapToScreenSize(int l ,int b ,int h)
{
	int s;
	float width,height;
	CCSize size;
	
	s=l+b;
	width=s*_xUnit;
	height=s*_halfYUnit+h*_zUnit;
	size.width=width;
	size.height=height;
	return size;
}

CCPoint Coordinate::mapToScreenAnchor(int l ,int b ,int h)
{
	CCPoint p;
	p.x=b*_xUnit;
	p.y=h*_zUnit;
	return p;
}

NS_CC_YHGE_ISOMETRIC_END
