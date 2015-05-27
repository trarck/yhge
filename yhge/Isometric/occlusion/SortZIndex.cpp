//
//  SortZIndex.m
//  Dungeons
//
//  Created by trarck trarck on 11-11-3.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "SortZIndex.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

SortZIndex::SortZIndex()
:_rootNode(NULL)
,_rootZOrder(0)
//,_statics(NULL)
//,_dynamics(NULL)
//,_isWorking(true)
//,_staticDirty(true)

{
    
}

SortZIndex::~SortZIndex()
{
//    CC_SAFE_RELEASE_NULL(_statics);
//    CC_SAFE_RELEASE_NULL(_dynamics);
    CC_SAFE_RELEASE_NULL(_rootNode);
}

bool SortZIndex::init()
{
       
    _rootNode=new SortZIndexNode();

	return true;
}

void SortZIndex::insert(SortZIndexNode* node)
{
    
    bool addedFlag=parseNode(_rootNode, node, 0);
    
    if (!addedFlag) {
        _rootNode->addChild(node);
    }
}

int SortZIndex::parseNode(SortZIndexNode* currentNode,SortZIndexNode* node,int deep)
{
    bool addedFlag=false;
    
    for (SortZIndexNode::SortZIndexNodeReverseIterator iter=currentNode->rbeginChild(); iter!=currentNode->rendChild(); ++iter) {
        addedFlag|=checkNode(*iter, node, deep+1);
    }

    return addedFlag;
}

bool SortZIndex::checkNode(SortZIndexNode* currentNode,SortZIndexNode* node,int deep)
{
//    CCLOG("current deep:%d",currentNode->getDeep());
//    CCAssert(currentNode->getDeep()==deep, "deep error");
    
    bool addedFlag=false;
    
    int side=caculateSide(currentNode->getRect(), node->getRect());
    
    if (side<0) {
        //小于node
        //把当前结点作为被检查结点的子元素
        //需要检查深度值。如果检查点所在的深度值大于等于当前结点所在的深度值，那么移过去深度值会增加，则执行移动操作，否则不需要
        if (node->getDeep()>=deep) {
            node->addChild(currentNode);
        }
        
        //不用处理当前结点的子结点
    }else if (side>0){
        //大于node
        //由于关系不能明确，需要处理其子元素。
        int subAddedFlag=parseNode(currentNode, node, deep);
        
        if (!subAddedFlag) {
            
            if (node->getParent()) {
                //如果node已经被添加到树中，则比较二者的深度值.使用深度值较大者。
                if (deep>=node->getDeep()) {
                    currentNode->addChild(node);
                }
                
            }else{
                currentNode->addChild(node);
            }
        }
        
        //检查结点必定会被添加到当前结点的树中(子结点或子孙结点)
        addedFlag=true;
    }else{
        //等于node
        //由于关系不明确，需要处理子元素
        parseNode(currentNode, node, deep);
        //不处理返回结果，由父结点处理
    }
    
    return addedFlag;
}

/**
 * 更新所有元素的zOrder值
 * 由于需要额外的结点字段来确定zorder，另外在移除结点的时候会有大量的结点操作，因此不推荐使用。
 */
void SortZIndex::updateZOrder_()
{
    std::vector<SortZIndexNode*> nodes;
    
    int rootZOrder=0;
    
    _rootNode->setSortedDeep(rootZOrder);
    
    nodes=_rootNode->getChildren();
    
    SortZIndexNode* item=NULL;
    SortZIndexNode* parent=NULL;
    int sortedDeep=0;
    
    SortZIndexNode::SortZIndexNodeIterator iter;
    SortZIndexNode::SortZIndexNodeIterator childIter;
    
    while (nodes.size()) {
        iter=nodes.begin();
        item=*iter;
        
        parent=item->getParent();
        
//        //旧的更新排续算法
//        sortedDeep=parent->getSortedDeep()+1;
//        item->setSortedDeep(sortedDeep);
//        item->updateZOrder(-sortedDeep);
        
        //为了减少运算，直接把deep用作zOrder
        sortedDeep=parent->getSortedDeep()-1;
        item->setSortedDeep(sortedDeep);
        item->updateZOrder(sortedDeep);
        
        nodes.erase(iter);
        
        for(childIter=item->beginChild();childIter!=item->endChild();++iter){
            nodes.push_back(*iter);
        }
    }
}

/**
 * 更新所有元素的zOrder值
 * 不依赖深度值
 */
void SortZIndex::updateZOrder()
{
    //把node按deep值存放
    std::vector< std::vector<SortZIndexNode*> > deepNodes;
    
    SortZIndexNode* item=NULL;
    
    SortZIndexNode::SortZIndexNodeIterator childIter;
    
    int currentDeep=0;
    int nextDeep=0;
    int deepZOrder=0;
    
    std::vector<SortZIndexNode*> emptyVector;
    deepNodes.push_back(emptyVector);
    
    deepNodes[currentDeep].push_back(_rootNode);
    
    while (deepNodes[currentDeep].size()) {
        
        nextDeep=currentDeep+1;
        deepZOrder=_rootZOrder-currentDeep;
        
        std::vector<SortZIndexNode*> subEmptyVector;
        deepNodes.push_back(subEmptyVector);
        
        std::vector<SortZIndexNode*>::iterator deepIter=deepNodes[currentDeep].begin();
        
        for (; deepIter!=deepNodes[currentDeep].end(); ++deepIter) {
            
            item=*deepIter;
            
            item->updateZOrder(deepZOrder);
            
//            CCLOG("%d:origin:%f,%f:size:%f,%f",deepZOrder,item->getRect().origin.x,item->getRect().origin.y,item->getRect().size.width,item->getRect().size.height);
            
            for(childIter=item->beginChild();childIter!=item->endChild();++childIter){
                deepNodes[nextDeep].push_back(*childIter);
            }
        }

        //如果结点数量大，为了减少内存使用，则要消除之前的层的元素。
        //但是只是使用了索引不用占用太多的内存,更新完成后五起删除.
        //deepNodes[currentDeep].clear();
        
        ++currentDeep;
    }
}


/**
 * 测试使用
 */
void SortZIndex::showTest()
{
    //把node按deep值存放
    std::vector< std::vector<SortZIndexNode*> > deepNodes;
    
    int rootZOrder=0;
    
    SortZIndexNode* item=NULL;
    
    SortZIndexNode::SortZIndexNodeIterator iter;
    SortZIndexNode::SortZIndexNodeIterator childIter;
    
    int currentDeep=0;
    int nextDeep=0;
    int deepZOrder=0;
    
    deepNodes[currentDeep].push_back(_rootNode);
    
    while (deepNodes[currentDeep].size()) {
        
        nextDeep=currentDeep+1;
        deepZOrder=rootZOrder-currentDeep;
        
        std::vector<SortZIndexNode*>::iterator deepIter=deepNodes[currentDeep].begin();
        
        for (; deepIter!=deepNodes[currentDeep].end(); ++deepIter) {
            
            item=*deepIter;
            
            item->updateZOrder(deepZOrder);
            
            CCLOGINFO("%d:origin:%f,%f:size:%f,%f",deepZOrder,item->getRect().origin.x,item->getRect().origin.y,item->getRect().size.width,item->getRect().size.height);
            
            for(childIter=item->beginChild();childIter!=item->endChild();++iter){
                deepNodes[nextDeep].push_back(*childIter);
            }
        }
        
        ++currentDeep;
    }
}

//
//int SortZIndex::parseTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
//{
//    
//    int side=caculateSide(currentNode->getRect(), node->getRect());
//    
//    if (side<0) {
//        //小于node
//        
//        _stateStack.push_back(kParseStateSmall);
//        _parsingState=kParseStateSmall;
//        
//        parseSmallTree(currentNode, node, kParseStateSmall);
//        
////        //由于是从父类过来的不用处理大于分支(大于分支是其父元素)。
////        //小于分支的元素都小于node
////        
////        if (_parseStack.size()==1) {
////            //调整node之间的关系。node是没有左右子树的
////            node->setLeftNode(currentNode);
////        }
////        
////        //处理等于分支
////        SortZIndexNode* rightNode=currentNode->getRightNode();
////        if (rightNode) {
////            
////            flag=parseTree(rightNode,node,flag);
////            
////            if (flag==0) {
////                //右子结点和node相等，则把右子结点移到node上
////                node->setRightNode(rightNode);
////                currentNode->setRightNode(NULL);
////            }
////        }
//        
//        return flag==0?-1:flag;
//        
//    }else if (side>0){
//        //大于node
//        //处理小于和等于
//        
//        int subFlag=0;
//        
//        SortZIndexNode* leftNode=currentNode->getLeftNode();
//        if (leftNode) {
//            flag=parseTree(leftNode,node,flag);
//        }
//        
//        SortZIndexNode* rightNode=currentNode->getRightNode();
//        if (rightNode) {
//            flag=parseTree(rightNode,node,flag);
//            
//            //消除右子树
//            if (flag<-1) {
//                currentNode->setRightNode(NULL);
//            }
//        }
//
//        
//        if (flag==0) {
//            currentNode->setLeftNode(node);
//        }
//        
//        return flag==0?1:flag;
//    }else{
//        //等于node
//        
//        //处理小于和等于分支
//        int subFlag=parseEqualTree(currentNode,node,flag);
//        
////        if (subFlag==0){
////            //左右子树都和元素相等，放入最上层分支
////            currentNode->setRightNode(node);
////            node->setRightNode(rightNode);
////        }
//    }
//    
//    _parseStack.pop_back();
//    
//    return 0;
//}
//
//int SortZIndex::parseEqualTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
//{
//
//    int lastState=*(_stateStack.end()-2);
//    
//    int state=_stateStack.back();
//    
//    
//    if (_parsingState!=kParseStateEqual) {
//        _parsingState=kParseStateEqual;
//    }
//    
//    int subFlag=0;
//    
//    
//    SortZIndexNode* rightNode=currentNode->getRightNode();
//    if (rightNode) {
//        int rightFlag=parseEqual(rightNode,node,1);
//        subFlag=subFlag!=1?rightFlag:subFlag;
//        
//        int topParsingState=_stateStack[1];
//        switch (topParsingState) {
//            case kParseStateSmall:{
//                if (subFlag!=1) {
//                    if (state==kParseStateRightEqual) {
//                        SortZIndexNode* temp=node->getRightNode();
//                        node->setRightNode(currentNode);
//                        currentNode->setRightNode(temp);
//                    }else if (flag==0){
//                        currentNode->setRightNode(node);
//                        node->setRightNode(rightNode);
//                    }
//                }
//                
//                break;
//            }
//            case kParseStateBig:{
//                
//                break;
//            }
//            case kParseStateEqual:{
//                
//                break;
//            }
//            default:
//                break;
//        
//    }
//    
//    SortZIndexNode* leftNode=currentNode->getLeftNode();
//    if (leftNode) {
//        subFlag=parseEqual(leftNode,node,-1);
//    }
//    
//
//    
//    if (_parsingNode==currentNode) {
//        if (subFlag!=1) {
//            
//            if (flag==-1) {
//                node->setRightNode(currentNode);
//            }else if (flag==0){
//                currentNode->setRightNode(node);
//                node->setRightNode(rightNode);
//            }
//        }
//    }
//    
//    return subFlag;
//}
//
//int SortZIndex::parseSmallTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
//{
//    int state=_stateStack.back();
//    
//    switch (state) {
//        case kParseStateSmall:
//            node->setLeftNode(currentNode);
//            _rootNode=node;
//            break;
//            
//        default:
//            break;
//    }
//    
//    int subFlag=-1;
//    
//    SortZIndexNode* rightNode=currentNode->getRightNode();
//    if (rightNode) {
//        
//        
//        subFlag=parseSmall(rightNode,node,1);
//        
//        if (_parseStack.size()==0){
//            
//            if (subFlag==-1) {
//                
//            }
//        }
//        
////        //如果右子树的所有点不小于检查点，则说明右子树已经被修改
////        if (subFlag!=-1) {
////            //右子树已经改变.去除当前结点的右子树
////            currentNode->setRightNode(NULL);
////        }
//    }
//    
//    _parseStack.pop_back();
//
//    
//    return subFlag;
//}
//
//int SortZIndex::parseBigTree(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
//{
//    
//    //只要进入大于状态，则把之前的结点栈消除掉
//    _parsingNode=currentNode;
//    
//    int subFlag=1;
//    
//    SortZIndexNode* leftNode=currentNode->getLeftNode();
//    if (leftNode) {
//        subFlag=parseBig(leftNode,node,-2);
//    }
//    
//    SortZIndexNode* rightNode=currentNode->getRightNode();
//    if (rightNode) {
//        subFlag|=parseBig(rightNode,node,subFlag);
//    }
//    
//    if (_parsingNode==currentNode) {
//        
//        currentNode->setLeftNode(node);
//    }
//    
//    return subFlag;
//}
//
//int SortZIndex::parseSmall(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
//{
//    int side=caculateSide(currentNode->getRect(), node->getRect());
//    
//    if (side<0) {
//        int subFlag=0;
//
//        if (flag==1) {
//            _stateStack.push_back(kParseStateRightSmall);
//        }else if(flag==-1){
//            _stateStack.push_back(kParseStateLeftSmall);
//        }
//        
//        subFlag=parseSmallTree(currentNode,node,-1);
//        
//        return -1;
//        
//    }else if (side>0){
//        //大于node
//        //把当前结点从父类中断开
//        SortZIndexNode* parentNode=currentNode->getParentNode();
//        parentNode->setRightNode(NULL);
//        
//        parseBigTree(currentNode, node, flag);
//        
//        return 1;
//    }else{
//        //把当前结点从父类中断开
//        if (flag==1) {
//            _stateStack.push_back(kParseStateRightEqual);
//        }
//        
//        parseEqualTree(currentNode, node, -1);
//        
//        return 0;
//
//        
//    }
//    
//}
//
//int SortZIndex::parseEqual(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
//{    
//    int side=caculateSide(currentNode->getRect(), node->getRect());
//    
//    //只处理当前结点大于检查结点
//    if (side>0) {
//        parseBigTree(currentNode, node, 0);
//        return 1;
//    }else{
//        if (flag==1) {
//            _stateStack.push_back(kParseStateRightEqual);
//        }else{
//            _stateStack.push_back(kParseStateLeftEqual);
//        }
//        return parseEqualTree(currentNode, node, 0);
//    }
//}
//
//int SortZIndex::parseBig(SortZIndexNode* currentNode,SortZIndexNode* node,int flag)
//{
//    int side=caculateSide(currentNode->getRect(), node->getRect());
//    
//    if (side<0) {
//        
//        if (flag==1) {
//            node->setLeftNode(currentNode);
//        }else{
//            _parsingNode->setLeftNode(node);
//            node->setLeftNode(currentNode);
//        }
//        
//        return parseSmallTree(currentNode, node, flag);
//        
////        return -1;
//    }else if (side>0){
//        //大于node
//        return parseBigTree(currentNode, node, 1);
////        return 0;
//    }else{
//        //等于node
//        if (flag) {
//            _parsingNode->setLeftNode(node);
//            node->setRightNode(currentNode);
//        }
//        
//        return parseEqualTree(currentNode, node, 1);
//        
////        return 0;
//    }
//
//}


/**
 * 计算二个矩形的位置关系
 * 这里使用的屏幕坐标。
       |     |
     2 |  1  | 0
   ----|-----|----
     1 |  0  | -1
   ----|-----|----
     0 | -1  | -2
       |     |
 
 * 中间是from,其它8个位置表示to可能出现的位置。
 * 反回值表示from-to的值
 * 大于0,表示from大于to(from遮挡to);
 * 小于0,表示from小于to(to遮挡from);
 * 等于0,表示from等于to(相互不遮挡).
 * 注意屏幕坐标和opengl的坐标
 
 *  opengl的斜视角的关系
            
 
          \  2 /
           \  /
         1  \/  1
      \     /\    /
       \   /  \  /
        \ /  0 \/
     0   /\    /\   0
        /  \  /  \
       / -1 \/ -1 \
            /\
           /  \
          / -2 \
 */
int SortZIndex::caculateSide(const CCRect& pFrom ,const CCRect& pTo)
{
	int lr, tb;//如果要确切的知道8个方位。上下左右分别用1,4,2,8表示，中还是用0。这样二二之和就可以确定方位。

    //这里使用的是opengl的坐标
    //大于等于
	if ((pTo.origin.x > pFrom.origin.x+pFrom.size.width) || fabs(pTo.origin.x- (pFrom.origin.x+pFrom.size.width))<0.0001 ) {
		//右
		lr = 1;
	//小于等于
    }else if((pTo.origin.x+pTo.size.width<pFrom.origin.x) || fabs(pTo.origin.x+pTo.size.width-pFrom.origin.x)<0.0001){
		//左
		lr = -1;
	} else  {//desc.right<=src.right && desc.left>=src.left(内中),desc.right>=src.right && desc.left<=src.left(外中) 都算中
		//中
		lr = 0;
	}
	
	if ((pTo.origin.y > pFrom.origin.y+pFrom.size.height) ||fabs(pTo.origin.y-( pFrom.origin.y+pFrom.size.height))<0.0001) {
		//上
		tb = 1;
	} else if ((pTo.origin.y+pTo.size.height < pFrom.origin.y) || fabs(pTo.origin.y+pTo.size.height -pFrom.origin.y)<0.0001) {
		//下
		tb = -1;
	} else {
		//中
		tb = 0;
	}

	return lr + tb;
}

NS_CC_YHGE_ISOMETRIC_END