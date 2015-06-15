#include "ISOActiveTileLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../ISOBases.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOActiveTileLayer::ISOActiveTileLayer()
:_layerName("")
,_layerOrientation(0)
,_opacity(255)
,_offset(CCPointZero)
,_map(NULL)
,_vertexZvalue(0)
,_objectGroup(NULL)
{
	
}

ISOActiveTileLayer::~ISOActiveTileLayer()
{
    CC_SAFE_RELEASE_NULL(_objectGroup);
}

bool ISOActiveTileLayer::init()
{
    
	return true;
}

ISOActiveTileLayer* ISOActiveTileLayer::create()
{
    ISOActiveTileLayer* pRet=new ISOActiveTileLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}

void ISOActiveTileLayer::releaseLayer()
{
    removeAllChildren();
}

void ISOActiveTileLayer::setupObjects()
{
    if (_objectGroup) {
		ISOObjectGroup::ISOMapObjectVector objects = _objectGroup->getObjects();
		ISOMapObject* mapObject = NULL;
		for (ISOObjectGroup::ISOMapObjectVector::iterator iter = objects.begin(); iter != objects.end();++iter){
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
Sprite* ISOActiveTileLayer::createObject(int gid,const Vec2& position)
{
    ISOTileset* tileset=_map->getTilesetGroup()->getTilesetByGid(gid);
    
    ISOTile* tile=tileset->tileForGid(gid);
    
    Sprite* tileSprite=Sprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    //object 的对齐方式为底部居中
    tileSprite->setAnchorPoint(ccp(0.5f,0));
    tileSprite->setPosition(isoGameToViewPoint(position));
    tileSprite->setOpacity(_opacity);
    
    this->addChild(tileSprite,-position.y);
    
    return tileSprite;
}

void ISOActiveTileLayer::scroll(const Vec2& tOffset)
{
    CCLOG("ISOActiveTileLayer::scroll");
}

void ISOActiveTileLayer::scroll(float x,float y)
{
    scroll(ccp(x,y));
}

void ISOActiveTileLayer::parseInternalProperties()
{
    CCLOG("ISOActiveTileLayer::parseInternalProperties");

}

Value ISOActiveTileLayer::getProperty(const std::string& propertyName)
{
	if (_properties.find(propertyName) != _properties.end())
		return _properties.at(propertyName);

	return Value::Null;
}

NS_CC_YHGE_ISOMETRIC_END
