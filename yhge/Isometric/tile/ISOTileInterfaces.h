#ifndef YHGE_ISOMETRIC_ISOTILEINTERFACES_H_
#define YHGE_ISOMETRIC_ISOTILEINTERFACES_H_

#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 主要用于接收组件坐标更新
 */
class ISODynamicComponentUpdateDelegator
{
public:
    virtual void onUpdateComponentMapCoordinate(unsigned int index,float deltaMapX,float deltaMapY)=0;
};

/**
 * ISODynamicComponent用于显示内容。
 * 目前的结构没有使用。由于直接可以从TileSet取得显示内容，所以暂时没有使用。
 */
class ISODynamicComponentCreateDelegator
{
public:
    virtual CCSprite* createTile()=0;
};

NS_CC_YHGE_ISOMETRIC_END

#endif // YHGE_ISOMETRIC_ISOTILEINTERFACES_H_