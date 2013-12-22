#include "CCGeometryValue.h"

NS_CC_YHGE_BEGIN

//CCPointValue::CCPointValue(void)
//{
//    setPoint(0.0f, 0.0f);
//}
//    
//CCPointValue::CCPointValue(const CCPointValue& other)
//{
//    this->setPoint(other.getPoint());
//}

CCPointValue& CCPointValue::operator= (const CCPointValue& other)
{
     m_tPoint=other.getPoint();
    return *this;
}

cocos2d::CCObject* CCPointValue::copyWithZone(cocos2d::CCZone* pZone)
{
    CCPointValue* pRet = new CCPointValue();
    pRet->setPoint(this->m_tPoint);
    return pRet;
}

// implementation of CCSizeValue

//CCSizeValue::CCSizeValue(void)
//{
//    setSize(0.0f, 0.0f);
//}
//
//CCSizeValue::CCSizeValue(float width, float height)
//{
//    setSize(width, height);
//}
//
//CCSizeValue::CCSizeValue(const cocos2d::CCSize& tSize)
//{
//    setSize(tSize);
//}
//
//CCSizeValue::CCSizeValue(const CCSizeValue& other)
//{
//    setSize(other.getSize());
//}

CCSizeValue& CCSizeValue::operator= (const CCSizeValue& other)
{
    setSize(other.getSize());
    return *this;
}


cocos2d::CCObject* CCSizeValue::copyWithZone(cocos2d::CCZone* pZone)
{
    CCSizeValue* pRet = new CCSizeValue();
    pRet->setSize(this->m_tSize);
    return pRet;
}

// implementation of CCRectValue

//CCRectValue::CCRectValue(void)
//{
//    setRect(0.0f, 0.0f, 0.0f, 0.0f);
//}
//
//CCRectValue::CCRectValue(float x, float y, float width, float height)
//{
//    setRect(x, y, width, height);
//}
//
//CCRectValue::CCRectValue(const cocos2d::CCRect& tRect)
//{
//    setRect(tRect);
//}
//
//CCRectValue::CCRectValue(const CCRectValue& other)
//{
//    setRect(other.getRect());
//}

CCRectValue& CCRectValue::operator= (const CCRectValue& other)
{
    setRect(other.getRect());
    return *this;
}

cocos2d::CCObject* CCRectValue::copyWithZone(cocos2d::CCZone* pZone)
{
    CCRectValue* pRet = new CCRectValue();
    pRet->setRect(this->getRect());
    return pRet;
}

NS_CC_YHGE_END
