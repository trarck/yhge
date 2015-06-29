#include "ISOObjectLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../ISOBases.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOObjectLayer::ISOObjectLayer()
:_tileMap(NULL)
,_objectGroup(NULL)
{
	
}

ISOObjectLayer::~ISOObjectLayer()
{
    CC_SAFE_RELEASE_NULL(_objectGroup);
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
    if (_objectGroup) {
		ISOObjectGroup::ISOMapObjectVector objects = _objectGroup->getObjects();
		ISOMapObject* mapObject = NULL;
		for (ISOObjectGroup::ISOMapObjectVector::iterator iter = objects.begin(); iter != objects.end(); ++iter){
			mapObject = *iter;
			if (mapObject->getGid() != 0 && mapObject->getVisible()) {
				createObject(mapObject->getGid(), mapObject->getPosition());
			}
		}
    }
}

/**
 * 使用gid从tileset中取出一个图片显示
 */
Sprite* ISOObjectLayer::createObject(int gid,const Vec2& coord)
{
    ISOTileset* tileset=_tileMap->getTilesetGroup()->getTilesetByGid(gid);
    
    ISOTile* tile=tileset->tileForGid(gid);
    
    Vec2 pos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(coord));
    
    Sprite* tileSprite=Sprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    //object 的对齐方式为底部居中
    tileSprite->setAnchorPoint(ccp(0.5f,0));
    tileSprite->setPosition(YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToViewPoint(coord)));
    tileSprite->setOpacity(_opacity);
    
    //屏幕的y方向作为zOrder，由于opengl的坐标和屏幕坐标反向，这里取反.
    //对于只占用一个格子的object来说，使用屏幕坐标的y方向来处理遮挡是可以的，如果大于一个格子，则会有问题。
    this->addChild(tileSprite,-(int)(pos.y));
    
    return tileSprite;
}

void ISOObjectLayer::scroll(const Vec2& tOffset)
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
    _tileMap=static_cast<ISOTileMap*>(pMap);
}

NS_CC_YHGE_ISOMETRIC_END
