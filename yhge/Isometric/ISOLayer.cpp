#include "ISOLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include "../base/ISOTileset.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_BEGIN

ISOLayer::ISOLayer()
:m_iStartX(0)
,m_iStartY(0)
,m_tLayerSize(CCSizeZero)
,m_tMapTileSize(CCSizeZero)
,m_tOffset(CCPointZero)
,m_pProperties(NULL)
,m_sLayerName("")
{
	
}

ISOLayer::~ISOLayer()
{
    CC_SAFE_RELEASE_NULL(m_pProperties);
}

bool ISOLayer::init()
{
    m_pProperties=new CCDictionary();
    
	return true;
}

bool ISOLayer::init(CCSize& mapTileSize)
{
    if(init()){
        m_tMapTileSize=mapTileSize;
        return true;
    }
    return false;
}

bool ISOLayer::init(CCSize& mapTileSize,CCPoint& offset)
{
    if(init(mapTileSize)){
        m_tOffset=offset;
        return true;
    }
    return false;
}


void ISOLayer::initOffset(const CCPoint& tOffset)
{
	this->setOffset(tOffset);
}

void ISOLayer::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}

ISOLayer* ISOLayer::create()
{
    ISOLayer* pRet=new ISOLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}


void ISOLayer::setupLayer()
{

}

void ISOLayer::releaseLayer()
{

}

void ISOLayer::scroll(const CCPoint& tOffset)
{
//    CCLOG("ISOLayer::scroll");
}

void ISOLayer::scroll(float x,float y)
{
    scroll(ccp(x,y));
}

/**
 * 地图的缩放值
 */
void ISOLayer::onMapScaleChange(float orignalScale,float newScale)
{
    
}

void ISOLayer::parseInternalProperties()
{

}

NS_CC_YHGE_END
