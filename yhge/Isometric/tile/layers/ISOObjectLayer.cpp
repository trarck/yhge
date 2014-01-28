#include "ISOObjectLayer.h"
#include <yhge/Isometric/ISOCoordinate.h>
#include <yhge/Isometric/ISOStaticCoordinate.h>
#include "../ISOBases.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_BEGIN

ISOObjectLayer::ISOObjectLayer()
:m_tileMap(NULL)
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
CCSprite* ISOObjectLayer::createObject(int gid,const CCPoint& coord)
{
    ISOTileset* tileset=m_tileMap->getTilesetGroup()->getTilesetByGid(gid);
    
    ISOTile* tile=tileset->tileForGid(gid);
    
    CCPoint pos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(coord));
    
    CCSprite* tileSprite=CCSprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    //object 的对齐方式为底部居中
    tileSprite->setAnchorPoint(ccp(0.5f,0));
    tileSprite->setPosition(YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(coord)));
    tileSprite->setOpacity(m_cOpacity);
    
    //屏幕的y方向作为zOrder，由于opengl的坐标和屏幕坐标反向，这里取反.
    //对于只占用一个格子的object来说，使用屏幕坐标的y方向来处理遮挡是可以的，如果大于一个格子，则会有问题。
    this->addChild(tileSprite,-(int)(pos.y));
    
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
