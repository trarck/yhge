/**
 * MapCellInfo由成员函数来实现
 */

#ifndef YHGE_ARITHMETIC_SEARCH_ASTAR_ASTARFLEXIBLE_H_
#define YHGE_ARITHMETIC_SEARCH_ASTAR_ASTARFLEXIBLE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "AstarNode.h"

NS_CC_YHGE_BEGIN

class AstarDelegate
{
public:

	/**
	 *检查是否可以通过
	 */
	virtual bool isWorkable(int x,int y);

};

class AstarFlexible : public CCObject {
public:
	
	AstarFlexible();
	~AstarFlexible(void);

	bool init();
	
	virtual void setMinX(int minX);
	virtual int getMinX();
	virtual void setMinY(int minY);
	virtual int getMinY();
	virtual void setMaxX(int maxX);
	virtual int getMaxX();
	virtual void setMaxY(int maxY);
	virtual int getMaxY();

	static AstarFlexible* sharedAstar();

	void setBounding(int minX ,int minY,int maxX,int maxY);
	void setStart(int x ,int y);
	void setEnd(int x ,int y);
	void reset();

	bool search();
	bool checkNearby();
	
	void getNext();
    void setOpenSeqNode(AstarNode* node ,int g);
	void addToOpen(AstarNode* node);
	void removeFromOpen(AstarNode* node);
	bool isInOpen(int x ,int y);
	
	AstarNode* getFromOpen(int x ,int y);

	void addToClose(int x,int y);
	bool isInClose(int x ,int y);

	int getH(int x ,int y);

	bool isOut(int x ,int y);
	
	
	bool isWorkableWithCrossSide(int x ,int y ,int stepX ,int stepY);
	bool isCrossSideWorkable(int x ,int y ,int stepX,int stepY);
	bool isEnd(int x ,int  y) ;
	bool isEnd(int x,int y ,int stepX ,int stepY);

	//由具体应用实现
	bool isWorkable(int x ,int y) ;

	//use call back function.使用callback比使用delegate在性能上会高一些
	//void setCheckBarrierHandle(SEL_CheckBarrierHandler checkBarrierHandle,CCObject* target);

	CCArray* getPath();
	CCArray* getPathWithStart();
	CCArray* getPathWithEnd();
	CCArray* getPathWithStartEnd();

protected:	
	int m_minX;
	int m_minY;
	int m_maxX;
	int m_maxY;
	
	AstarNode* m_start;
	AstarNode* m_end;
	AstarNode* m_current;
	
	CCArray* m_openSeq;//开启队列，存放每个结点。结点属性,parent 父结点，x,y地图坐,f,g,h路径评分
	
	//opens closes与地图相关，一般用二维数组
	//这里使用"y,x"做为关键字，BOOL做为值的dictionary来在存储。键可替换y右移16位加上x的数值
	//当然也可以根据搜索范围(minX,minY,maxX,maxY)来生成数组，数组值是BOOL
	//TODO 比较二种方法哪种快。最好应该是关于x，y的二维hash表算法最快。
	//二元hash:先创建关于y的hash,值为关于x的hash。这样查找时间为O(2)
	CCDictionary* m_opens;//开起列表,设置地图上的坐标，表示开启状态
	CCDictionary* m_closes;//关闭列表,存放已经到达过的点
	
	AstarDelegate* m_delegate;
};

NS_CC_YHGE_END

#endif // YHGE_ARITHMETIC_SEARCH_ASTAR_ASTARFLEXIBLE_H_