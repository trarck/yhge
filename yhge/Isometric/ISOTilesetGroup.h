#ifndef YHGE_ISOMETRIC_ISOTILESETGROUP_H_
#define YHGE_ISOMETRIC_ISOTILESETGROUP_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "ISOTileset.h"

NS_CC_YHGE_BEGIN


class ISOTilesetGroup : public CCObject{

public:
    
    ISOTilesetGroup();
    
    ~ISOTilesetGroup();
    
    bool init();
    
    void addTileset(ISOTileset* tileset);
    
    void insertTileset(int index,ISOTileset* tileset);
    
    int indexOfTileset(ISOTileset* tileset);
    
    void removeTilesetAt(int index);
    
    void replaceTileset(ISOTileset* oldTileset,ISOTileset* newTileset);
    
    int tilesetCount(){return m_pTilesets->count();}
    
    ISOTileset* getTilesetByIndex(int index){ return (ISOTileset *)m_pTilesets->objectAtIndex(index); }
    
    ISOTileset *tilesetAt(int index){ return (ISOTileset *)m_pTilesets->objectAtIndex(index); }
    
    ISOTileset* getTilesetByGid(unsigned int gid);
    
    CCArray* getTilesets(){return m_pTilesets;}

public:
    CCArray* m_pTilesets;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOTILESETGROUP_H_
