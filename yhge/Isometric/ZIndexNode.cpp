//
//  ZIndex.

#include "ZIndexNode.h"

NS_CC_YHGE_BEGIN

ZIndexNode::ZIndexNode()
:m_pEntity(NULL)
{

}

ZIndexNode::~ZIndexNode()
{

}

void ZIndexNode::setRect(const CCRect& rect)
{
    m_tRect=rect;
}

const CCRect& ZIndexNode::getRect()
{
    return m_tRect;
}

void ZIndexNode::setEntity(CCObject* entity)
{
    m_pEntity=entity;
}

CCObject* ZIndexNode::getEntity()
{
    return m_pEntity;
}

NS_CC_YHGE_END