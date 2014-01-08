#ifndef COCOS_YHGE_ISOMETRIC_H_
#define COCOS_YHGE_ISOMETRIC_H_

//ISometric info base
#include "Isometric/ISOCoordinate.h"
#include "Isometric/Coordinate.h"
#include "Isometric/ZIndexNode.h"
#include "Isometric/ZIndex.h"

//Isometric map info and parser
#include "Isometric/tile/parser/ISOTileInfo.h"
#include "Isometric/tile/parser/ISOTilesetInfo.h"
#include "Isometric/tile/parser/ISOObjectInfo.h"
#include "Isometric/tile/parser/ISOObjectGroupInfo.h"
#include "Isometric/tile/parser/ISOLayerInfo.h"
#include "Isometric/tile/parser/ISOMapInfo.h"
#include "Isometric/tile/parser/ISOXMLParser.h"

//Isometric map elementgit
#include "Isometric/tile/base/ISOTile.h"
#include "Isometric/tile/base/ISOTileset.h"
#include "Isometric/tile/base/ISOTilesetGroup.h"
#include "Isometric/tile/base/ISOTileMapObject.h"
#include "Isometric/tile/base/ISOComponentNode.h"
#include "Isometric/tile/base/ISOObjectGroup.h"
#include "Isometric/tile/layers/ISODynamicComponent.h"
#include "Isometric/tile/layers/ISOTileLayer.h"
#include "Isometric/tile/layers/ISOGroundTileLayer.h"
#include "Isometric/tile/layers/ISODynamicTileLayer.h"
#include "Isometric/tile/layers/ISOBatchTileLayer.h"
#include "Isometric/tile/layers/ISOBatchDynamicComponent.h"
#include "Isometric/tile/layers/ISOBatchDynamicTileLayer.h"
#include "Isometric/tile/ISOTileMap.h"
#include "Isometric/tile/reader/ISOTileMapBuilder.h"

#endif //COCOS_YHGE_ISOMETRIC_H_