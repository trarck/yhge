#include "ISOTilesetGroup.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTilesetGroup::ISOTilesetGroup()
:_pTilesets(NULL)
{

}

ISOTilesetGroup::~ISOTilesetGroup()
{
    CCLOG("ISOTilesetGroup destroy");
    CC_SAFE_RELEASE(_pTilesets);
}

bool ISOTilesetGroup::init()
{
    _pTilesets=new CCArray();
    return true;
}

void ISOTilesetGroup::addTileset(ISOTileset* tileset)
{
    _pTilesets->addObject(tileset);
}

void ISOTilesetGroup::insertTileset(int index,ISOTileset* tileset)
{
    _pTilesets->insertObject(tileset, index);
}

int ISOTilesetGroup::indexOfTileset(ISOTileset* tileset)
{
   return _pTilesets->indexOfObject(tileset);
}

void ISOTilesetGroup::removeTilesetAt(int index)
{
    _pTilesets->removeObjectAtIndex(index);
}

void ISOTilesetGroup::replaceTileset(ISOTileset* oldTileset,ISOTileset* newTileset)
{
    unsigned int index=_pTilesets->indexOfObject(oldTileset);
    
    _pTilesets->replaceObjectAtIndex(index, newTileset);
}


ISOTileset* ISOTilesetGroup::getTilesetByGid(unsigned int gid)
{
   
    ISOTileset* tileset = NULL;
    Ref* pObj = NULL;
    CCARRAY_FOREACH_REVERSE(_pTilesets, pObj)
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
