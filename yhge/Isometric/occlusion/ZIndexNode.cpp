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

void ZIndexNode::serect(const CCRect& rect)
{
    _rect=rect;
}

const CCRect& ZIndexNode::gerect()
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