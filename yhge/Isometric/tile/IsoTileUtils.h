#ifndef YHGE_ISOMETRIC_ISOTILEUTILS_H_
#define YHGE_ISOMETRIC_ISOTILEUTILS_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOTileUtils : public Ref {

public:
	
	/**
	 * 计算显示区域内，组件数量的行列数
	 */
	static void calcDynamicComponetSize(const CCSize& visibleSize,const CCSize& tileSize,int* column,int* row);
};





NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILEUTILS_H_
