//
//  ZIndex.

#include "SortZIndexNode.h"

NS_CC_YHGE_BEGIN

SortZIndexNode::SortZIndexNode()
:m_pEntity(NULL)
,m_leftNode(NULL)
,m_rightNode(NULL)
,m_parentNode(NULL)
{

}

SortZIndexNode::~SortZIndexNode()
{

}

void SortZIndexNode::setRect(const CCRect& rect)
{
    m_tRect=rect;
}

const CCRect& SortZIndexNode::getRect()
{
    return m_tRect;
}

void SortZIndexNode::setEntity(CCObject* entity)
{
    m_pEntity=entity;
}

CCObject* SortZIndexNode::getEntity()
{
    return m_pEntity;
}

NS_CC_YHGE_END