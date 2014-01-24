//
//  SortZIndexNode.

#ifndef YHGE_ISOMETRIC_SortZIndexNode_H_
#define YHGE_ISOMETRIC_SortZIndexNode_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN


class SortZIndexNode : public CCObject {

public:
    SortZIndexNode();
    ~SortZIndexNode();
    
    void setRect(const CCRect& rect);
    const CCRect& getRect();
    
    //弱引用
    void setEntity(CCObject* entity);
    CCObject* getEntity();
    
    
    inline void setLeftNode(SortZIndexNode* leftNode)
    {
        m_leftNode = leftNode;
    }
    
    inline SortZIndexNode* getLeftNode()
    {
        return m_leftNode;
    }
    
    inline void setRightNode(SortZIndexNode* rightNode)
    {
        m_rightNode = rightNode;
    }
    
    inline SortZIndexNode* getRightNode()
    {
        return m_rightNode;
    }
    
    inline void setParentNode(SortZIndexNode* parentNode)
    {
        m_parentNode = parentNode;
    }
    
    inline SortZIndexNode* getParentNode()
    {
        return m_parentNode;
    }
    
protected:
    CCObject* m_pEntity;
    CCRect m_tRect;
    
    /**
     * 左子树。表示小于
     */
    SortZIndexNode* m_leftNode;
    
    //右子树。表示等于
    SortZIndexNode* m_rightNode;
    
    //父类结点
    SortZIndexNode* m_parentNode;
    
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_SortZIndexNode_H_
