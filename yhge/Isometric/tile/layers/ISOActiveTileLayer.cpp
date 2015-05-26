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
,_properties(NULL)
,_map(NULL)
,_vertexZvalue(0)
,_objectGroup(NULL)
{
	
}

ISOActiveTileLayer::~ISOActiveTileLayer()
{
    CC_SAFE_RELEASE_NULL(_properties);
    CC_SAFE_RELEASE_NULL(_objectGroup);
}

bool ISOActiveTileLayer::init()
{
    _properties=new CCDictionary();
    
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
        CCArray* objects=_objectGroup->getObjects();
        Ref* pObj=NULL;
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
CCSprite* ISOActiveTileLayer::createObject(int gid,const Vec2& position)
{
    ISOTileset* tileset=_map->getTilesetGroup()->getTilesetByGid(gid);
    
    ISOTile* tile=tileset->tileForGid(gid);
    
    CCSprite* tileSprite=CCSprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
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
