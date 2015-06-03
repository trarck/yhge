#include "ISOActiveObjectLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../ISOBases.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOActiveObjectLayer::ISOActiveObjectLayer()
:_layerName("")
,_layerOrientation(0)
,_opacity(255)
,_offset(CCPointZero)
,_map(NULL)
,_vertexZvalue(0)
,_objectGroup(NULL)
{
	
}

ISOActiveObjectLayer::~ISOActiveObjectLayer()
{
    CC_SAFE_RELEASE_NULL(_objectGroup);
}

bool ISOActiveObjectLayer::init()
{  
	return true;
}

ISOActiveObjectLayer* ISOActiveObjectLayer::create()
{
    ISOActiveObjectLayer* pRet=new ISOActiveObjectLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}

void ISOActiveObjectLayer::releaseLayer()
{
    removeAllChildren();
}

void ISOActiveObjectLayer::setupObjects()
{
    if (_objectGroup) {
        ISOObjectGroup::ISOMapObjectVector objects=_objectGroup->getObjects();
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
Sprite* ISOActiveObjectLayer::createObject(int gid,const Vec2& position)
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

void ISOActiveObjectLayer::scroll(const Vec2& tOffset)
{
    CCLOG("ISOActiveObjectLayer::scroll");
}

void ISOActiveObjectLayer::scroll(float x,float y)
{
    scroll(ccp(x,y));
}

void ISOActiveObjectLayer::parseInternalProperties()
{
    CCLOG("ISOActiveObjectLayer::parseInternalProperties");

}

Value ISOActiveObjectLayer::getProperty(const std::string& propertyName)
{
	if (_properties.find(propertyName) != _properties.end())
		return _properties.at(propertyName);

	return Value::Null;
}

NS_CC_YHGE_ISOMETRIC_END
