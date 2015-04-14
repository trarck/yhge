//
//  ZIndex.

#include "ZIndexNode.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ZIndexNode::ZIndexNode()
:_pEntity(NULL)
{

}

ZIndexNode::~ZIndexNode()
{

}

void ZIndexNode::setRect(const CCRect& rect)
{
    _tRect=rect;
}

const CCRect& ZIndexNode::getRect()
{
    return _tRect;
}

void ZIndexNode::setEntity(Ref* entity)
{
    _pEntity=entity;
}

Ref* ZIndexNode::getEntity()
{
    return _pEntity;
}

NS_CC_YHGE_ISOMETRIC_END