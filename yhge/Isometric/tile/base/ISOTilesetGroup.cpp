#include "ISOTilesetGroup.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTilesetGroup::ISOTilesetGroup()
{

}

ISOTilesetGroup::~ISOTilesetGroup()
{
    CCLOG("ISOTilesetGroup destroy");
}

bool ISOTilesetGroup::init()
{
    return true;
}

void ISOTilesetGroup::addTileset(ISOTileset* tileset)
{
    _tilesets.pushBack(tileset);
}

void ISOTilesetGroup::insertTileset(int index,ISOTileset* tileset)
{
	_tilesets.insert(index, tileset);
}

int ISOTilesetGroup::indexOfTileset(ISOTileset* tileset)
{
	return _tilesets.getIndex(tileset);
}

void ISOTilesetGroup::removeTilesetAt(int index)
{
	_tilesets.erase(index);
}

void ISOTilesetGroup::replaceTileset(ISOTileset* oldTileset,ISOTileset* newTileset)
{
	unsigned int index = _tilesets.getIndex(oldTileset);
    
	_tilesets.replace(index, newTileset);
}


ISOTileset* ISOTilesetGroup::getTilesetByGid(unsigned int gid)
{
	for (ISOTilesetVector::iterator iter = _tilesets.begin(); iter != _tilesets.end(); ++iter){
		if ((*iter)->contains(gid)){
			return *iter;
		}
	}

    return nullptr;
}

NS_CC_YHGE_ISOMETRIC_END
