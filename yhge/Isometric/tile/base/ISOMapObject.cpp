#include "ISOMapObject.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOMapObject::ISOMapObject()
:m_uGid(0)
,m_sName("")
,m_sType("")
,m_tPosition(CCPointZero)
,m_tSize(CCSizeZero)
,m_rotation(0)
,m_bVisible(true)
,m_pProperties(NULL)
{

}


ISOMapObject::~ISOMapObject()
{
    CCLOG("ISOMapObject destroy");
    CC_SAFE_RELEASE(m_pProperties);
}

bool ISOMapObject::init()
{
    m_pProperties = new CCDictionary();
    return true;
}

NS_CC_YHGE_ISOMETRIC_END
