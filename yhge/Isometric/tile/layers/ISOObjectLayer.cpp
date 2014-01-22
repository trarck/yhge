#include "ISOObjectLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include "../ISOBases.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_BEGIN

ISOObjectLayer::ISOObjectLayer()
:m_tileMap(NULL)
,m_vertexZvalue(0)
,m_objectGroup(NULL)
{
	
}

ISOObjectLayer::~ISOObjectLayer()
{
    CC_SAFE_RELEASE_NULL(m_objectGroup);
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


/**
 * 初始化显示
 */
void ISOObjectLayer::setupLayer()
{
    setupObjects();
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

void ISOObjectLayer::setMap(ISOMap* pMap)
{
    m_tileMap=static_cast<ISOTileMap*>(pMap);
}

NS_CC_YHGE_END
