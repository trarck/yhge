#include "ISOActiveLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include "../ISOBases.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_BEGIN

ISOActiveLayer::ISOActiveLayer()
:m_vertexZvalue(0)
,m_objects(NULL)
,m_tileMap(NULL)
{
	
}

ISOActiveLayer::~ISOActiveLayer()
{
    CC_SAFE_RELEASE_NULL(m_objects);
}

bool ISOActiveLayer::init()
{
    m_objects=new CCArray();
	return true;
}

ISOActiveLayer* ISOActiveLayer::create()
{
    ISOActiveLayer* pRet=new ISOActiveLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}

/**
 * 设置层
 */
void ISOActiveLayer::setupLayer()
{
    setupObjects();
}

void ISOActiveLayer::releaseLayer()
{
    removeAllChildren();
}

void ISOActiveLayer::setupObjects()
{
    if (m_objects) {
        CCObject* pObj=NULL;
        ISOMapObject* mapObject=NULL;
        CCARRAY_FOREACH(m_objects, pObj){
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
CCSprite* ISOActiveLayer::createObject(int gid,const CCPoint& position)
{
    ISOTileset* tileset=m_tileMap->getTilesetGroup()->getTilesetByGid(gid);
    
    ISOTile* tile=tileset->tileForGid(gid);
    
    CCSprite* tileSprite=CCSprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    //object 的对齐方式为底部居中
    tileSprite->setAnchorPoint(ccp(0.5f,0));
    tileSprite->setPosition(isoGameToViewPoint(position));
    tileSprite->setOpacity(m_cOpacity);
    
    this->addChild(tileSprite,-position.y);
    
    return tileSprite;
}

void ISOActiveLayer::scroll(const CCPoint& tOffset)
{
    CCLOG("ISOActiveLayer::scroll");
}

void ISOActiveLayer::setMap(ISOMap* pMap)
{
    ISOLayer::setMap(pMap);
    m_tileMap=static_cast<ISOTileMap*>(pMap);
}

void ISOActiveLayer::parseInternalProperties()
{
    CCLOG("ISOActiveLayer::parseInternalProperties");

}

NS_CC_YHGE_END
