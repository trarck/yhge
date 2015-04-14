#include "ISOActiveLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../ISOBases.h"
#include "../ISOInfos.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOActiveLayer::ISOActiveLayer()
:m_objects(NULL)
,m_tileMap(NULL)
{
	
}

ISOActiveLayer::~ISOActiveLayer()
{
    CC_SAFE_RELEASE_NULL(m_objects);
}

bool ISOActiveLayer::init()
{
    if (ISOLayer::init()) {
        m_objects=new CCArray();
        return true;
    }
	return false;
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
    ISOLayer::setupLayer();
    setupObjects();
}

void ISOActiveLayer::releaseLayer()
{
    removeAllChildren();
    ISOLayer::releaseLayer();
}

void ISOActiveLayer::setupObjects()
{
    if (m_objects) {
        Ref* pObj=NULL;
        ISOObjectInfo* objInfo=NULL;
        CCARRAY_FOREACH(m_objects, pObj){
            objInfo=static_cast<ISOObjectInfo*>(pObj);
            if (objInfo->getGid()!=0 && objInfo->getVisible()) {
                createObject(objInfo->getGid(), objInfo->getPosition());
            }
        }
    }
}

/**
 * 使用gid从tileset中取出一个图片显示
 */
CCSprite* ISOActiveLayer::createObject(int gid,const CCPoint& coord)
{
    ISOTileset* tileset=m_tileMap->getTilesetGroup()->getTilesetByGid(gid);
    
    ISOTile* tile=tileset->tileForGid(gid);
    
    CCPoint pos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(coord));
    
    CCSprite* tileSprite=CCSprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    //object 的对齐方式为底部居中
    tileSprite->setAnchorPoint(ccp(0.5f,0));
    tileSprite->setPosition(pos);
    tileSprite->setOpacity(m_cOpacity);
    
    //屏幕的y方向作为zOrder，由于opengl的坐标和屏幕坐标反向，这里取反。
    //对于只占用一个格子的object来说，使用屏幕坐标的y方向来处理遮挡是可以的，如果大于一个格子，则会有问题。
    this->addChild(tileSprite,-(int)(pos.y));
    
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

NS_CC_YHGE_ISOMETRIC_END
