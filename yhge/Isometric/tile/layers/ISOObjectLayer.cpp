#include "ISOObjectLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include "../ISOBases.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_BEGIN

ISOObjectLayer::ISOObjectLayer()
:m_layerName("")
,m_layerOrientation(0)
,m_opacity(255)
,m_offset(CCPointZero)
,m_properties(NULL)
,m_map(NULL)
,m_vertexZvalue(0)
,m_objectGroup(NULL)
{
	
}

ISOObjectLayer::~ISOObjectLayer()
{
    CC_SAFE_RELEASE_NULL(m_properties);
    CC_SAFE_RELEASE_NULL(m_objectGroup);
}

bool ISOObjectLayer::init()
{
    m_properties=new CCDictionary();
    
	return true;
}

ISOObjectLayer* ISOObjectLayer::create()
{
    ISOObjectLayer* pRet=new ISOObjectLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}

void ISOObjectLayer::releaseLayer()
{
    removeAllChildren();
}

void ISOObjectLayer::setupObjects()
{
    if (m_objectGroup) {
        CCArray* objects=m_objectGroup->getObjects();
        CCObject* pObj=NULL;
        ISOMapObject* mapObject=NULL;
        CCARRAY_FOREACH(objects, pObj){
            mapObject=static_cast<ISOMapObject*>(pObj);
            if (mapObject->getGid()!=0 && mapObject->getVisible()) {
                createObject(mapObject->getGid(), mapObject->getPosition());
            }
        }
    }
}

/**
 * 使用gid从tileset中取出一个图片显示
 */
CCSprite* ISOObjectLayer::createObject(int gid,const CCPoint& position)
{
    ISOTileset* tileset=m_map->getTilesetGroup()->getTilesetByGid(gid);
    
    ISOTile* tile=tileset->tileForGid(gid);
    
    CCSprite* tileSprite=CCSprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    //object 的对齐方式为底部居中
    tileSprite->setAnchorPoint(ccp(0,0.5f));
    tileSprite->setPosition(position);
    tileSprite->setOpacity(m_opacity);
    
    this->addChild(tileSprite,position.y);
    
    return tileSprite;
}

void ISOObjectLayer::scroll(const CCPoint& tOffset)
{
    CCLOG("ISOObjectLayer::scroll");
}

void ISOObjectLayer::scroll(float x,float y)
{
    scroll(ccp(x,y));
}

void ISOObjectLayer::parseInternalProperties()
{
    CCLOG("ISOObjectLayer::parseInternalProperties");

}

CCString* ISOObjectLayer::propertyNamed(const char *propertyName)
{
    return (CCString*)m_properties->objectForKey(propertyName);
}

NS_CC_YHGE_END
