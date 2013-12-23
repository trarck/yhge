#ifndef COCOS_YHGE_ISOMETRIC_H_
#define COCOS_YHGE_ISOMETRIC_H_

//ISometric info base
#include "Isometric/ISOCoordinate.h"
#include "Isometric/CCCoordinate.h"
#include "Isometric/CCAstarNode.h"
#include "Isometric/CCAstar.h"
#include "Isometric/CCZIndexNode.h"
#include "Isometric/CCZIndex.h"

//Isometric map info and parser
#include "Isometric/parser/CCISOTileInfo.h"
#include "Isometric/parser/CCISOTilesetInfo.h"
#include "Isometric/parser/CCISOObjectInfo.h"
#include "Isometric/parser/CCISOObjectGroupInfo.h"
#include "Isometric/parser/CCISOLayerInfo.h"
#include "Isometric/parser/CCISOMapInfo.h"
#include "Isometric/parser/CCISOXMLParserInfo.h"

//Isometric map element
#include "Isometric/CCISOTile.h"
#include "Isometric/CCISOTileset.h"
#include "Isometric/CCISOTilesetGroup.h"
#include "Isometric/CCISOObject.h"
#include "Isometric/CCISOObjectGroup.h"
#include "Isometric/CCISOComponentNode.h"
#include "Isometric/CCISODynamicComponent.h"
#include "Isometric/CCISOTileLayer.h"
#include "Isometric/CCISOGroundTileLayer.h"
#include "Isometric/CCISODynamicTileLayer.h"
#include "Isometric/CCISOBatchTileLayer.h"
#include "Isometric/CCISOBatchDynamicComponent.h"
#include "Isometric/CCISOBatchDynamicTileLayer.h"
#include "Isometric/CCISOTileMap.h"
#include "Isometric/CCISOTileMapBuilder.h"

#endif //COCOS_YHGE_ISOMETRIC_H_