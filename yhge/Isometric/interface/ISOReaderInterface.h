#ifndef YHGE_ISOMETRIC_INTERFACE_ISOREADERINTERFACE_H_
#define YHGE_ISOMETRIC_INTERFACE_ISOREADERINTERFACE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

class ISOTileMap;

class ISOReaderInterface
{

public:
   
    virtual ISOTileMap* getMap();
    
    virtual readMap(ISOTileMap* pMap);
    
};

NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_INTERFACE_ISOREADERINTERFACE_H_
