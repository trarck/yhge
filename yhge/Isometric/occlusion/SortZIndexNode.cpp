//
//  ZIndex.

#include "SortZIndexNode.h"

NS_CC_YHGE_BEGIN

SortZIndexNode::SortZIndexNode()
:m_entity(NULL)
,m_rect(CCRectZero)
,m_parent(NULL)
,m_sortedDeep(0)
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
    m_children.push_back(child);
    child->setParent(child);
}

/**
 * 移除一个子结点
 */
void SortZIndexNode::removeChild(SortZIndexNode* child)
{
    SortZIndexNodeIterator iter=std::find(m_children.begin(), m_children.end(), child);
    if (iter!=m_children.end()) {
        m_children.erase(iter);
        child->release();
    }
}

/**
 * 设置父结点
 */
void SortZIndexNode::setParent(SortZIndexNode* parent)
{
    if (m_parent) {
        m_parent->removeChild(this);
    }
    m_parent = parent;
}

/**
 * 取得结点的实时深度值
 */
int SortZIndexNode::getDeep()
{
    int deep=0;
    
    SortZIndexNode* parent=m_parent;
    
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
    if (m_entity) {
        static_cast<CCNode*>(m_entity)->setZOrder(zOrder);
    }
}

/**
 * 消除childre
 */
void SortZIndexNode::clearChildren()
{
    for (SortZIndexNodeIterator iter=m_children.begin(); iter!=m_children.end(); ++iter) {
        (*iter)->release();
    }
}

NS_CC_YHGE_END