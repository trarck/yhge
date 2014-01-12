#ifndef YHGE_ISOMETRIC_ISOTILEINTERFACES_H_
#define YHGE_ISOMETRIC_ISOTILEINTERFACES_H_

#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * ��Ҫ���ڽ�������������
 */
class ISODynamicComponentUpdateDelegator
{
public:
    virtual void onUpdateComponentMapCoordinate(unsigned int index,float deltaMapX,float deltaMapY)=0;
};

/**
 * ISODynamicComponent������ʾ���ݡ�
 * Ŀǰ�Ľṹû��ʹ�á�����ֱ�ӿ��Դ�TileSetȡ����ʾ���ݣ�������ʱû��ʹ�á�
 */
class ISODynamicComponentCreateDelegator
{
public:
    virtual CCSprite* createTile()=0;
};

NS_CC_YHGE_END

#endif // YHGE_ISOMETRIC_ISOTILEINTERFACES_H_