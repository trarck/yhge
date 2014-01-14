#include "ISOTilesetGroup.h"
#include <yhge/Isometric/ISOCoordinate.h>



NS_CC_YHGE_BEGIN

ISOTilesetGroup::ISOTilesetGroup()
:m_pTilesets(NULL)
{

}

ISOTilesetGroup::~ISOTilesetGroup()
{
    CCLOG("ISOTilesetGroup destroy");
    CC_SAFE_RELEASE(m_pTilesets);
}

bool ISOTilesetGroup::init()
{
    m_pTilesets=new CCArray();
    return true;
}

void ISOTilesetGroup::addTileset(ISOTileset* tileset)
{
    m_pTilesets->addObject(tileset);
}

void ISOTilesetGroup::insertTileset(int index,ISOTileset* tileset)
{
    m_pTilesets->insertObject(tileset, index);
}

int ISOTilesetGroup::indexOfTileset(ISOTileset* tileset)
{
   return m_pTilesets->indexOfObject(tileset);
}

void ISOTilesetGroup::removeTilesetAt(int index)
{
    m_pTilesets->removeObjectAtIndex(index);
}

void ISOTilesetGroup::replaceTileset(ISOTileset* oldTileset,ISOTileset* newTileset)
{
    unsigned int index=m_pTilesets->indexOfObject(oldTileset);
    
    m_pTilesets->replaceObjectAtIndex(index, newTileset);
}


ISOTileset* ISOTilesetGroup::getTilesetByGid(unsigned int gid)
{
   
    ISOTileset* tileset = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH_REVERSE(m_pTilesets, pObj)
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

NS_CC_YHGE_END
