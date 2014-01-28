//
//  SortZIndexNode.

#ifndef YHGE_ISOMETRIC_SortZIndexNode_H_
#define YHGE_ISOMETRIC_SortZIndexNode_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * 排序用到的结点
 * 不使用二叉村，二叉树在表示相等的时候很麻烦
 * 使用多子树，当前结点的子结点都比当前结点小，相等的元素表示成兄弟结点。
 */
class SortZIndexNode : public CCObject {

public:
    SortZIndexNode();
    
    ~SortZIndexNode();
    
    inline bool init(){return true;}
    
    /**
     * 添加一个子结点
     */
    void addChild(SortZIndexNode* child);
    
    /**
     * 移除一个子结点
     */
    void removeChild(SortZIndexNode* child);
    
    /**
     * 设置父结点
     */
    void setParent(SortZIndexNode* parent);
    
    /**
     * 取得结点的实时深度值
     */
    int getDeep();
    
    /**
     * 更新结点代表的元素的zOrder值
     */
    void updateZOrder(int zOrder);
    
    /**
     * 消除children
     */
    void clearChildren();
    
    /**
     * 重制内部数据
     */
    void reset();
    
    /**
     * 重制相关联的结点
     * 父结点和子结点
     */
    void resetRelation();
    
    /**
     * 复制自身，包含子目录。
     */
    SortZIndexNode* clone();
    
    CREATE_FUNC(SortZIndexNode);
    
    /**
     * 定义子元素的遍历器
     */
    typedef std::vector<SortZIndexNode*>::iterator SortZIndexNodeIterator;
    typedef std::vector<SortZIndexNode*>::const_iterator SortZIndexNodeConstIterator;
    
    typedef std::vector<SortZIndexNode*>::reverse_iterator SortZIndexNodeReverseIterator;
    typedef std::vector<SortZIndexNode*>::const_reverse_iterator SortZIndexNodeConstReverseIterator;
    
    /**
     * 取得头结点遍历器
     */
    inline SortZIndexNodeIterator beginChild()
    {
        return m_children.begin();
    }
    
    inline SortZIndexNodeConstIterator beginChild() const
    {
        return m_children.begin();
    }
    
    /**
     * 取得终点结点遍历器
     */
    inline SortZIndexNodeIterator endChild()
    {
        return m_children.end();
    }
    
    inline SortZIndexNodeConstIterator endChild() const
    {
        return m_children.end();
    }
    
    /**
     * 取得反向头结点遍历器
     */
    inline SortZIndexNodeReverseIterator rbeginChild()
    {
        return m_children.rbegin();
    }
    
    inline SortZIndexNodeConstReverseIterator rbeginChild() const
    {
        return m_children.rbegin();
    }
    
    /**
     * 取得反向终结点遍历器
     */
    inline SortZIndexNodeConstReverseIterator rendChild()
    {
        return m_children.rend();
    }
    
    inline SortZIndexNodeConstReverseIterator rendChild() const
    {
        return m_children.rend();
    }
    
public:
    
    //get set
    inline void setChildren(const std::vector<SortZIndexNode*>& children)
    {
        m_children = children;
    }
    
    inline const std::vector<SortZIndexNode*>& getChildren()
    {
        return m_children;
    }
    
    inline SortZIndexNode* getParent()
    {
        return m_parent;
    }
    
    inline void setSortedDeep(int sortedDeep)
    {
        m_sortedDeep = sortedDeep;
    }
    
    inline int getSortedDeep()
    {
        return m_sortedDeep;
    }
    
    
    inline void setRect(const CCRect& rect)
    {
        m_rect=rect;
    }
    
    inline const CCRect& getRect()
    {
        return m_rect;
    }
    
    inline void setEntity(CCObject* entity)
    {
        m_entity=entity;
    }
    
    inline CCObject* getEntity()
    {
        return m_entity;
    }
    
////    inline void setLeftNode(SortZIndexNode* leftNode)
////    {
////        m_leftNode = leftNode;
////    }
////    
////    inline SortZIndexNode* getLeftNode()
////    {
////        return m_leftNode;
////    }
////    
////    inline void setRightNode(SortZIndexNode* rightNode)
////    {
////        m_rightNode = rightNode;
////    }
////    
////    inline SortZIndexNode* getRightNode()
////    {
////        return m_rightNode;
////    }
//    
//    inline void setParentNode(SortZIndexNode* parentNode)
//    {
//        m_parentNode = parentNode;
//    }
//    
//    inline SortZIndexNode* getParentNode()
//    {
//        return m_parentNode;
//    }
//    
    
protected:
    CCObject* m_entity;
    
    CCRect m_rect;
    
    //保存所有比自己ZOrder值小的元素。要占用一个引用计数
    std::vector<SortZIndexNode*> m_children;
    
    //父结点。弱引用
    SortZIndexNode* m_parent;
    
    //排过序的深度值
    int m_sortedDeep;
    
//    /**
//     * 左子树。表示小于
//     */
//    SortZIndexNode* m_leftNode;
//    
//    //右子树。表示等于
//    SortZIndexNode* m_rightNode;
//    
//    //父类结点
//    SortZIndexNode* m_parentNode;
    
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_SortZIndexNode_H_
