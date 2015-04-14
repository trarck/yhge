//
//  ZIndex.

#include "SortZIndexNode.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

SortZIndexNode::SortZIndexNode()
:_entity(NULL)
,_rect(CCRectZero)
,_parent(NULL)
,_sortedDeep(0)
{
    
}

SortZIndexNode::~SortZIndexNode()
{
    //删除对子结点的引用
    clearChildren();
}

/**
 * 添加一个子结点
 */
void SortZIndexNode::addChild(SortZIndexNode* child)
{
    child->retain();
    _children.push_back(child);
    child->setParent(this);
}

/**
 * 移除一个子结点
 */
void SortZIndexNode::removeChild(SortZIndexNode* child)
{
    SortZIndexNodeIterator iter=std::find(_children.begin(), _children.end(), child);
    if (iter!=_children.end()) {
        _children.erase(iter);
        child->release();
    }
}

/**
 * 设置父结点
 */
void SortZIndexNode::setParent(SortZIndexNode* parent)
{
    if (_parent) {
        _parent->removeChild(this);
    }
    _parent = parent;
}

/**
 * 取得结点的实时深度值
 */
int SortZIndexNode::getDeep()
{
    int deep=0;
    
    SortZIndexNode* parent=_parent;
    
    while (parent) {
        ++deep;
        parent=parent->getParent();
    }
    
    return deep;
}

/**
 * 更新结点代表的元素的zOrder值
 */
void SortZIndexNode::updateZOrder(int zOrder)
{
    if (_entity) {
        static_cast<CCNode*>(_entity)->setZOrder(zOrder);
    }
}

/**
 * 消除children
 */
void SortZIndexNode::clearChildren()
{
    for (SortZIndexNodeIterator iter=_children.begin(); iter!=_children.end(); ++iter) {
        (*iter)->release();
    }
    
    _children.clear();
}

/**
 * 重制内部数据
 */
void SortZIndexNode::reset()
{
    clearChildren();
    
    _rect=CCRectZero;
    _sortedDeep=0;
    
    setEntity(NULL);
    
    setParent(NULL);
}

/**
 * 重制相关联的结点
 * 父结点和子结点
 */
void SortZIndexNode::resetRelation()
{
    clearChildren();
    
    setParent(NULL);
}

/**
 * 复制自身，包含子目录。
 */
SortZIndexNode* SortZIndexNode::clone()
{
    SortZIndexNode* node=new SortZIndexNode();
    node->init();
    
    node->setEntity(_entity);
    node->setRect(_rect);
    
    //不用设置parent，在clone child的时候会设置
    
    //clone children
    for (SortZIndexNodeIterator iter=_children.begin(); iter!=_children.end(); ++iter) {
        node->addChild((*iter)->clone());
    }
    
    node->autorelease();
    
    return node;
}

NS_CC_YHGE_ISOMETRIC_END