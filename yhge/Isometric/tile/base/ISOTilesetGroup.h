#ifndef YHGE_ISOMETRIC_ISOTILESETGROUP_H_
#define YHGE_ISOMETRIC_ISOTILESETGROUP_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ISOTileset.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 组织管理tileset
 */
class ISOTilesetGroup : public Ref{

public:
    
    ISOTilesetGroup();
    
    ~ISOTilesetGroup();
    
    bool init();
    
    void addTileset(ISOTileset* tileset);
    
    void insertTileset(int index,ISOTileset* tileset);
    
    int indexOfTileset(ISOTileset* tileset);
    
    void removeTilesetAt(int index);
    
    void replaceTileset(ISOTileset* oldTileset,ISOTileset* newTileset);
    
    int tilesetCount(){return _tilesets->count();}
    
    ISOTileset* getTilesetByIndex(int index){ return (ISOTileset *)_tilesets->objectAtIndex(index); }
    
    ISOTileset *tilesetAt(int index){ return (ISOTileset *)_tilesets->objectAtIndex(index); }
    
    ISOTileset* getTilesetByGid(unsigned int gid);
    
    CCArray* getTilesets(){return _tilesets;}

public:
    CCArray* _tilesets;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILESETGROUP_H_
