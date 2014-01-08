#ifndef COCOS_YHGE_ISOMETRIC_H_
#define COCOS_YHGE_ISOMETRIC_H_

//ISometric info base
#include "Isometric/ISOCoordinate.h"
#include "Isometric/Coordinate.h"
#include "Isometric/ZIndexNode.h"
#include "Isometric/ZIndex.h"

//Isometric map info and parser
#include "Isometric/parser/ISOTileInfo.h"
#include "Isometric/parser/ISOTilesetInfo.h"
#include "Isometric/parser/ISOObjectInfo.h"
#include "Isometric/parser/ISOObjectGroupInfo.h"
#include "Isometric/parser/ISOLayerInfo.h"
#include "Isometric/parser/ISOMapInfo.h"
#include "Isometric/parser/ISOXMLParser.h"

//Isometric map element
#include "Isometric/ISOTile.h"
#include "Isometric/ISOTileset.h"
#include "Isometric/ISOTilesetGroup.h"
#include "Isometric/ISOObject.h"
#include "Isometric/ISOObjectGroup.h"
#include "Isometric/ISOComponentNode.h"
#include "Isometric/ISODynamicComponent.h"
#include "Isometric/ISOTileLayer.h"
#include "Isometric/ISOGroundTileLayer.h"
#include "Isometric/ISODynamicTileLayer.h"
#include "Isometric/ISOBatchTileLayer.h"
#include "Isometric/ISOBatchDynamicComponent.h"
#include "Isometric/ISOBatchDynamicTileLayer.h"
#include "Isometric/ISOTileMap.h"
#include "Isometric/ISOTileMapBuilder.h"

#endif //COCOS_YHGE_ISOMETRIC_H_