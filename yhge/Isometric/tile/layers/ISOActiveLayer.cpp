#include "ISOActiveLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../ISOBases.h"
#include "../ISOInfos.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOActiveLayer::ISOActiveLayer()
:_tileMap(NULL)
{
	
}

ISOActiveLayer::~ISOActiveLayer()
{
}

bool ISOActiveLayer::init()
{
    if (ISOLayer::init()) {
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
    if (_objects.size()) {
		ISOObjectInfo* objInfo = NULL;
		for (ISOObjectInfoVector::iterator iter = _objects.begin(); iter != _objects.end(); ++iter){
			objInfo = *iter;
			if (objInfo->getGid() != 0 && objInfo->getVisible()) {
				createObject(objInfo->getGid(), objInfo->getPosition());
			}
		}
    }
}

/**
 * 使用gid从tileset中取出一个图片显示
 */
Sprite* ISOActiveLayer::createObject(int gid,const Vec2& coord)
{
    ISOTileset* tileset=_tileMap->getTilesetGroup()->getTilesetByGid(gid);
    
    ISOTile* tile=tileset->tileForGid(gid);
    
    Vec2 pos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(coord));
    
    Sprite* tileSprite=Sprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    //object 的对齐方式为底部居中
    tileSprite->setAnchorPoint(Vec2(0.5f,0));
    tileSprite->setPosition(pos);
    tileSprite->setOpacity(_opacity);
    
    //屏幕的y方向作为zOrder，由于opengl的坐标和屏幕坐标反向，这里取反。
    //对于只占用一个格子的object来说，使用屏幕坐标的y方向来处理遮挡是可以的，如果大于一个格子，则会有问题。
    this->addChild(tileSprite,-(int)(pos.y));
    
    return tileSprite;
}

void ISOActiveLayer::scroll(const Vec2& tOffset)
{
    CCLOG("ISOActiveLayer::scroll");
}

void ISOActiveLayer::setMap(ISOMap* pMap)
{
    ISOLayer::setMap(pMap);
    _tileMap=static_cast<ISOTileMap*>(pMap);
}

void ISOActiveLayer::parseInternalProperties()
{
    CCLOG("ISOActiveLayer::parseInternalProperties");

}

NS_CC_YHGE_ISOMETRIC_END
