#ifndef YHGE_ISOMETRIC_ISOTILEUTILS_H_
#define YHGE_ISOMETRIC_ISOTILEUTILS_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class ISOTileUtils : public CCObject {

public:
	
	/**
	 * ������ʾ�����ڣ����������������
	 */
	static void calcDynamicComponetSize(const CCSize& visibleSize,const CCSize& tileSize,int* column,int* row);
};





NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOTILEUTILS_H_
