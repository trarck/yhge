#include "ISOTileUtils.h"

NS_CC_YHGE_BEGIN

/**
 * 计算显示区域内，组件数量的行列数
 */
void ISOTileUtils::calcDynamicComponetSize(const CCSize& visibleSize,const CCSize& tileSize,int* column,int* row)
{
	//参考Isometric.Game.Programming.with.DirectX.7的第421页。
	//如果要显示全visibleSize的大小内的元素，则在除以块大小后，四个角要向外移动一格。所以最后大小要加2.
	*column=floor(visibleSize.width/tileSize.width)+2;
	*row=floor(visibleSize.height/tileSize.height)+2;
}

NS_CC_YHGE_END
