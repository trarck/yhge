#include "ISOTileUtils.h"

NS_CC_YHGE_BEGIN

/**
 * ������ʾ�����ڣ����������������
 */
void ISOTileUtils::calcDynamicComponetSize(const CCSize& visibleSize,const CCSize& tileSize,int* column,int* row)
{
	//�ο�Isometric.Game.Programming.with.DirectX.7�ĵ�421ҳ��
	//���Ҫ��ʾȫvisibleSize�Ĵ�С�ڵ�Ԫ�أ����ڳ��Կ��С���ĸ���Ҫ�����ƶ�һ����������СҪ��2.
	*column=floor(visibleSize.width/tileSize.width)+2;
	*row=floor(visibleSize.height/tileSize.height)+2;
}

NS_CC_YHGE_END
