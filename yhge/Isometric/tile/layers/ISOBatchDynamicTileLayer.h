#ifndef YHGE_ISOMETRIC_ISOBATCHDYNAMICTILELAYER_H_
#define YHGE_ISOMETRIC_ISOBATCHDYNAMICTILELAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include <yhge/Isometric/tile/base/ISOTileset.h>
#include "ISODynamicTileLayer.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 动态更新可显示区域,只渲染显示区域的tile.
 * 使用batchnode来优化组件显示。
 */
class ISOBatchDynamicTileLayer : public ISODynamicTileLayer {

public:
	
	ISOBatchDynamicTileLayer();
    
	~ISOBatchDynamicTileLayer(void);
	
    virtual bool init();
    
    virtual bool init(Size& mapTileSize,Vec2& offset);
public:
    inline void setTileset(ISOTileset* tileset)
	{
		CC_SAFE_RETAIN(tileset);
		CC_SAFE_RELEASE(_tileset);
		_tileset = tileset;
	}

	inline ISOTileset* getTileset()
	{
		return _tileset;
	}
protected:

    ISOTileset* _tileset;
};



NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOBATCHDYNAMICTILELAYER_H_
