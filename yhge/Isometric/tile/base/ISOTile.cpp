#include "ISOTile.h"
#include "ISOTileset.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTile::ISOTile()
:_id(0)
,_texture(NULL)
,_animation(NULL)
,_textureRect(Rect(0,0,0,0))
,_tileset(NULL)
{
    
}

ISOTile::~ISOTile()
{
    CCLOG("ISOTile destroy");
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE_NULL(_animation);
}

bool ISOTile::init()
{
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

bool ISOTile::init(int id,ISOTileset* tileset,Texture2D* texture)
{
    if(init(id,tileset)){
        setTexture(texture);
        _textureRect.size=texture->getContentSizeInPixels();
        return true;
    }
    return false;
}

bool ISOTile::init(int id,ISOTileset* tileset,Texture2D* texture,Rect& textureRect)
{
    if(init(id,tileset,texture)){
        _textureRect=textureRect;
        return true;
    }
    return false;
}


int ISOTile::getGId()
{
    return _id+_tileset->getFirstGid();
}

NS_CC_YHGE_ISOMETRIC_END
