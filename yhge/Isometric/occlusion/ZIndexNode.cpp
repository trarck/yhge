//
//  ZIndex.

#include "ZIndexNode.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ZIndexNode::ZIndexNode()
:_entity(NULL)
{

}

ZIndexNode::~ZIndexNode()
{

}

void ZIndexNode::setRect(const CCRect& rect)
{
    _rect=rect;
}

const CCRect& ZIndexNode::getRect()
{
    return _rect;
}

void ZIndexNode::setEntity(Ref* entity)
{
    _entity=entity;
}

Ref* ZIndexNode::getEntity()
{
    return _entity;
}

NS_CC_YHGE_ISOMETRIC_END