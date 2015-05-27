#include "ISOTilesetGroup.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTilesetGroup::ISOTilesetGroup()
:_tilesets(NULL)
{

}

ISOTilesetGroup::~ISOTilesetGroup()
{
    CCLOG("ISOTilesetGroup destroy");
    CC_SAFE_RELEASE(_tilesets);
}

bool ISOTilesetGroup::init()
{
    _tilesets=new CCArray();
    return true;
}

void ISOTilesetGroup::addTileset(ISOTileset* tileset)
{
    _tilesets->addObject(tileset);
}

void ISOTilesetGroup::insertTileset(int index,ISOTileset* tileset)
{
    _tilesets->insertObject(tileset, index);
}

int ISOTilesetGroup::indexOfTileset(ISOTileset* tileset)
{
   return _tilesets->indexOfObject(tileset);
}

void ISOTilesetGroup::removeTilesetAt(int index)
{
    _tilesets->removeObjectAtIndex(index);
}

void ISOTilesetGroup::replaceTileset(ISOTileset* oldTileset,ISOTileset* newTileset)
{
    unsigned int index=_tilesets->indexOfObject(oldTileset);
    
    _tilesets->replaceObjectAtIndex(index, newTileset);
}


ISOTileset* ISOTilesetGroup::getTilesetByGid(unsigned int gid)
{
   
    ISOTileset* tileset = NULL;
    Ref* pObj = NULL;
    CCARRAY_FOREACH_REVERSE(_tilesets, pObj)
    {
        tileset = (ISOTileset*)pObj;
        if (tileset)
        {
            if(tileset->contains(gid)){
                return tileset;
            }
        }
    }
    return tileset;
}

NS_CC_YHGE_ISOMETRIC_END
