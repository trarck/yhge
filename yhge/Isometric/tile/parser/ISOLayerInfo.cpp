#include "ISOLayerInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOLayerInfo::ISOLayerInfo()
:_name("")
,_tiles(NULL)
,_offset(CCPointZero)
,_opacity(255)
,_ownTiles(true)
,_visible(true)
,_layerSize(CCSizeZero)
{

}

ISOLayerInfo::~ISOLayerInfo()
{
    CCLOG("ISOLayerInfo destroy");
    if(_ownTiles && _tiles )
    {
        delete [] _tiles;
        _tiles = NULL;
    }
}

NS_CC_YHGE_ISOMETRIC_END
