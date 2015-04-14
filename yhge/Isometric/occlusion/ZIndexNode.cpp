//
//  ZIndex.

#include "ZIndexNode.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

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

void ZIndexNode::setEntity(Ref* entity)
{
    m_pEntity=entity;
}

Ref* ZIndexNode::getEntity()
{
    return m_pEntity;
}

NS_CC_YHGE_ISOMETRIC_END