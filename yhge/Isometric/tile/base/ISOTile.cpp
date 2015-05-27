#include "ISOTile.h"
#include "ISOTileset.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTile::ISOTile()
:_id(0)
,_texture(NULL)
,_animation(NULL)
,_textureRect(CCRectZero)
,_properties(NULL)
,_tileset(NULL)
{
    
}

ISOTile::~ISOTile()
{
    CCLOG("ISOTile destroy");
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE_NULL(_animation);
}

bool ISOTile::init()
{
    _properties=new CCDictionary();
    return true;
}

bool ISOTile::init(int id,ISOTileset* tileset)
{
    if(init()){
        _id=id;
        setTileset(tileset);
        return true;
    }
    return false;
}

bool ISOTile::init(int id,ISOTileset* tileset,CCTexture2D* texture)
{
    if(init(id,tileset)){
        setTexture(texture);
        _textureRect.size=texture->getContentSizeInPixels();
        return true;
    }
    return false;
}

bool ISOTile::init(int id,ISOTileset* tileset,CCTexture2D* texture,CCRect& textureRect)
{
    if(init(id,tileset,texture)){
        _textureRect=textureRect;
        return true;
    }
    return false;
}

void ISOTile::setId(int id)
{
    _id = id;
}

int ISOTile::getId()
{
    return _id;
}

int ISOTile::getGId()
{
    return _id+_tileset->getFirstGid();
}

void ISOTile::setTileset(ISOTileset* tileset)
{
    _tileset = tileset;
}

ISOTileset* ISOTile::getTileset()
{
    return _tileset;
}

void ISOTile::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(_properties);
    _properties = pProperties;
}

CCDictionary* ISOTile::getProperties()
{
    return _properties;
}

NS_CC_YHGE_ISOMETRIC_END
