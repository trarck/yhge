//
//  SortZIndex.m
//  Dungeons
//
//  Created by trarck trarck on 11-11-3.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "SortZIndex.h"
#include "SortParseState.h"

NS_CC_YHGE_BEGIN

SortZIndex::SortZIndex()
:m_pStatics(NULL)
,m_pDynamics(NULL)
,m_bIsWorking(true)
,m_bStaticDirty(true)
,m_rootNode(NULL)
{
    
}

SortZIndex::~SortZIndex()
{
    CC_SAFE_RELEASE_NULL(m_pStatics);
    CC_SAFE_RELEASE_NULL(m_pDynamics);
    CC_SAFE_RELEASE_NULL(m_rootNode);
}

bool SortZIndex::init()
{
    m_pStatics=new CCArray(20);
    m_pDynamics=new CCArray(20);
    m_bIsWorking=false;

	return true;
}

void SortZIndex::insert(SortZIndexNode* node)
{
    parseTree(m_rootNode, node, kParseStateIdle);
    m_parsingState=kParseStateIdle;
    m_stateStack.push_back(kParseStateIdle);
    m_parsingNode=m_rootNode;
}

int SortZIndex::parseTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
{
    
    int side=caculateSide(currentNode->getRect(), node->getRect());
    
    if (side<0) {
        //小于node
        
        m_stateStack.push_back(kParseStateSmall);
        m_parsingState=kParseStateSmall;
        
        parseSmallTree(currentNode, node, kParseStateSmall);
        
//        //由于是从父类过来的不用处理大于分支(大于分支是其父元素)。
//        //小于分支的元素都小于node
//        
//        if (m_parseStack.size()==1) {
//            //调整node之间的关系。node是没有左右子树的
//            node->setLeftNode(currentNode);
//        }
//        
//        //处理等于分支
//        SortZIndexNode* rightNode=currentNode->getRightNode();
//        if (rightNode) {
//            
//            flag=parseTree(rightNode,node,flag);
//            
//            if (flag==0) {
//                //右子结点和node相等，则把右子结点移到node上
//                node->setRightNode(rightNode);
//                currentNode->setRightNode(NULL);
//            }
//        }
        
        return flag==0?-1:flag;
        
    }else if (side>0){
        //大于node
        //处理小于和等于
        
        int subFlag=0;
        
        SortZIndexNode* leftNode=currentNode->getLeftNode();
        if (leftNode) {
            flag=parseTree(leftNode,node,flag);
        }
        
        SortZIndexNode* rightNode=currentNode->getRightNode();
        if (rightNode) {
            flag=parseTree(rightNode,node,flag);
            
            //消除右子树
            if (flag<-1) {
                currentNode->setRightNode(NULL);
            }
        }

        
        if (flag==0) {
            currentNode->setLeftNode(node);
        }
        
        return flag==0?1:flag;
    }else{
        //等于node
        
        //处理小于和等于分支
        int subFlag=parseEqualTree(currentNode,node,flag);
        
//        if (subFlag==0){
//            //左右子树都和元素相等，放入最上层分支
//            currentNode->setRightNode(node);
//            node->setRightNode(rightNode);
//        }
    }
    
    m_parseStack.pop_back();
    
    return 0;
}

int SortZIndex::parseEqualTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
{

    int lastState=*(m_stateStack.end()-2);
    
    int state=m_stateStack.back();
    
    
    if (m_parsingState!=kParseStateEqual) {
        m_parsingState=kParseStateEqual;
    }
    
    int subFlag=0;
    
    
    SortZIndexNode* rightNode=currentNode->getRightNode();
    if (rightNode) {
        int rightFlag=parseEqual(rightNode,node,1);
        subFlag=subFlag!=1?rightFlag:subFlag;
        
        int topParsingState=m_stateStack[1];
        switch (topParsingState) {
            case kParseStateSmall:{
                if (subFlag!=1) {
                    if (state==kParseStateRightEqual) {
                        SortZIndexNode* temp=node->getRightNode();
                        node->setRightNode(currentNode);
                        currentNode->setRightNode(temp);
                    }else if (flag==0){
                        currentNode->setRightNode(node);
                        node->setRightNode(rightNode);
                    }
                }
                
                break;
            }
            case kParseStateBig:{
                
                break;
            }
            case kParseStateEqual:{
                
                break;
            }
            default:
                break;
        }
    }
    
    SortZIndexNode* leftNode=currentNode->getLeftNode();
    if (leftNode) {
        subFlag=parseEqual(leftNode,node,-1);
    }
    

    
    if (m_parsingNode==currentNode) {
        if (subFlag!=1) {
            
            if (flag==-1) {
                node->setRightNode(currentNode);
            }else if (flag==0){
                currentNode->setRightNode(node);
                node->setRightNode(rightNode);
            }
        }
    }
    
    return subFlag;
}

int SortZIndex::parseSmallTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
{
    int state=m_stateStack.back();
    
    switch (state) {
        case kParseStateSmall:
            node->setLeftNode(currentNode);
            m_rootNode=node;
            break;
            
        default:
            break;
    }
    
    int subFlag=-1;
    
    SortZIndexNode* rightNode=currentNode->getRightNode();
    if (rightNode) {
        
        
        subFlag=parseSmall(rightNode,node,1);
        
        if (m_parseStack.size()==0){
            
            if (subFlag==-1) {
                
            }
        }
        
//        //如果右子树的所有点不小于检查点，则说明右子树已经被修改
//        if (subFlag!=-1) {
//            //右子树已经改变.去除当前结点的右子树
//            currentNode->setRightNode(NULL);
//        }
    }
    
    m_parseStack.pop_back();

    
    return subFlag;
}

int SortZIndex::parseBigTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
{
    
    //只要进入大于状态，则把之前的结点栈消除掉
    m_parsingNode=currentNode;
    
    int subFlag=1;
    
    SortZIndexNode* leftNode=currentNode->getLeftNode();
    if (leftNode) {
        subFlag=parseBig(leftNode,node,-2);
    }
    
    SortZIndexNode* rightNode=currentNode->getRightNode();
    if (rightNode) {
        subFlag|=parseBig(rightNode,node,subFlag);
    }
    
    if (m_parsingNode==currentNode) {
        
        currentNode->setLeftNode(node);
    }
    
    return subFlag;
}

int SortZIndex::parseSmall(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
{
    int side=caculateSide(currentNode->getRect(), node->getRect());
    
    if (side<0) {
        int subFlag=0;

        if (flag==1) {
            m_stateStack.push_back(kParseStateRightSmall);
        }else if(flag==-1){
            m_stateStack.push_back(kParseStateLeftSmall);
        }
        
        subFlag=parseSmallTree(currentNode,node,-1);
        
        return -1;
        
    }else if (side>0){
        //大于node
        //把当前结点从父类中断开
        SortZIndexNode* parentNode=currentNode->getParentNode();
        parentNode->setRightNode(NULL);
        
        parseBigTree(currentNode, node, flag);
        
        return 1;
    }else{
        //把当前结点从父类中断开
        if (flag==1) {
            m_stateStack.push_back(kParseStateRightEqual);
        }
        
        parseEqualTree(currentNode, node, -1);
        
        return 0;

        
    }
    
}

int SortZIndex::parseEqual(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
{    
    int side=caculateSide(currentNode->getRect(), node->getRect());
    
    //只处理当前结点大于检查结点
    if (side>0) {
        parseBigTree(currentNode, node, 0);
        return 1;
    }else{
        if (flag==1) {
            m_stateStack.push_back(kParseStateRightEqual);
        }else{
            m_stateStack.push_back(kParseStateLeftEqual);
        }
        return parseEqualTree(currentNode, node, 0);
    }
}

int SortZIndex::parseBig(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
{
    int side=caculateSide(currentNode->getRect(), node->getRect());
    
    if (side<0) {
        
        if (flag==1) {
            node->setLeftNode(currentNode);
        }else{
            m_parsingNode->setLeftNode(node);
            node->setLeftNode(currentNode);
        }
        
        return parseSmallTree(currentNode, node, flag);
        
//        return -1;
    }else if (side>0){
        //大于node
        return parseBigTree(currentNode, node, 1);
//        return 0;
    }else{
        //等于node
        if (flag) {
            m_parsingNode->setLeftNode(node);
            node->setRightNode(currentNode);
        }
        
        return parseEqualTree(currentNode, node, 1);
        
//        return 0;
    }

}


/**
 * 计算二个矩形的位置关系
       |     |
    -2 | -1  | 0
   ----|-----|----
    -1 |  0  | 1
   ----|-----|----
     0 |  1  | 2
       |     |
 
 * 反回值小于0表示小于(from遮挡to)，大于0表示大于(to遮挡from)，等于0表示等于(相互不遮挡)
 */
int SortZIndex::caculateSide(const CCRect& pFrom ,const CCRect& pTo)
{
	int lr, tb;//如果要确切的知道8个方位。上下左右分别用1,4,2,8表示，中还是用0。这样二二之和就可以确定方位。

    //大于等于
	if (pTo.origin.x > pFrom.origin.x+pFrom.size.width || fabs(pTo.origin.x- (pFrom.origin.x+pFrom.size.width))<0.0001 ) {
		//右
		lr = 1;
	//小于等于
    }else if(pTo.origin.x+pTo.size.width<pFrom.origin.x || fabs(pTo.origin.x+pTo.size.width-pFrom.origin.x)<0.0001){
		//左
		lr = -1;
	} else  {//desc.right<=src.right && desc.left>=src.left(内中),desc.right>=src.right && desc.left<=src.left(外中) 都算中
		//中
		lr = 0;
	}
	
	if (pTo.origin.y > pFrom.origin.y+pFrom.size.height ||fabs(pTo.origin.y-( pFrom.origin.y+pFrom.size.height))<0.0001) {
		//下
		tb = 1;
	} else if (pTo.origin.y+pTo.size.height < pFrom.origin.y || fabs(pTo.origin.y+pTo.size.height -pFrom.origin.y)<0.0001) {
		//上
		tb = -1;
	} else {
		//中
		tb = 0;
	}

	return lr + tb;
}

NS_CC_YHGE_END