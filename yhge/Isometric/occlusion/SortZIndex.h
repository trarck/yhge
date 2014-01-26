
#ifndef YHGE_ISOMETRIC_SORTZINDEX_H_
#define YHGE_ISOMETRIC_SORTZINDEX_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "SortZIndexNode.h"

NS_CC_YHGE_BEGIN

class SortZIndex : public CCObject {

public:
    SortZIndex();
    
    ~SortZIndex();
    
    bool init();
    
    void insert(SortZIndexNode* node);
    
    /**
     * 更新所有元素的zOrder值
     */
    void updateZOrder_();
    
    /**
     * 更新所有元素的zOrder值
     */
    void updateZOrder();
    
    /**
     * 测试使用
     */
    void showTest();

public:
    
    typedef enum {
        kZIndexStatic,
        kZIndexDynamic
    } ZIndexType;
    
    inline void setRootNode(SortZIndexNode* rootNode)
    {
        CC_SAFE_RETAIN(rootNode);
        CC_SAFE_RELEASE(m_rootNode);
        m_rootNode = rootNode;
    }
    
    inline SortZIndexNode* getRootNode()
    {
        return m_rootNode;
    }
    
protected:
    
    int parseNode(SortZIndexNode* currentNode,SortZIndexNode* node,int deep);
    
    bool checkNode(SortZIndexNode* currentNode,SortZIndexNode* node,int deep);
    
//    int parseTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag);
//    
//    int parseEqualTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag);
//    int parseSmallTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag);
//    int parseBigTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag);
//    
//    int parseSmall(SortZIndexNode* currentNode,SortZIndexNode* node,int flag);
//    
//    int parseEqual(SortZIndexNode* currentNode,SortZIndexNode* node,int flag);
//    
//    int parseBig(SortZIndexNode* currentNode,SortZIndexNode* node,int flag);
    
    int caculateSide(const CCRect& pFrom ,const CCRect& pTo);
    
protected:
	CCArray *m_pStatics;
	CCArray *m_pDynamics;
	bool m_bIsWorking;
	bool m_bStaticDirty;

    SortZIndexNode* m_rootNode;
    
    SortZIndexNode* m_parsingNode;
    
    std::vector<SortZIndexNode*> m_parseStack;
    std::vector<SortZIndexNode*> m_nodeStack;
    
    std::vector<int> m_stateStack;
    int m_parsingState;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_SORTZINDEX_H_
