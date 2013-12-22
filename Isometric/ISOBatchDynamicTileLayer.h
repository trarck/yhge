#ifndef YHGE_ISOMETRIC_ISOBATCHDYNAMICTILELAYER_H_
#define YHGE_ISOMETRIC_ISOBATCHDYNAMICTILELAYER_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "ISODynamicTileLayer.h"
#include "ISOTileset.h"

NS_CC_YHGE_BEGIN

/**
 * 动态更新可显示区域,只渲染显示区域的tile.
 * 使用batchnode来优化组件显示。
 */
class ISOBatchDynamicTileLayer : public ISODynamicTileLayer {

public:
	
	ISOBatchDynamicTileLayer();
    
	~ISOBatchDynamicTileLayer(void);
	
    virtual bool init();
    
    virtual bool init(CCSize& mapTileSize,CCPoint& offset);
public:
    inline void setTileset(ISOTileset* pTileset)
	{
		CC_SAFE_RETAIN(pTileset);
		CC_SAFE_RELEASE(m_pTileset);
		m_pTileset = pTileset;
	}

	inline ISOTileset* getTileset()
	{
		return m_pTileset;
	}
protected:

    ISOTileset* m_pTileset;
};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOBATCHDYNAMICTILELAYER_H_
