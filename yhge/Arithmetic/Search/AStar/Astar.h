/**
 * 要配合具体的游戏，来确定MapCellInfo
 */

#ifndef YHGE_ARITHMETIC_SEARCH_ASTAR_ASTAR_H_
#define YHGE_ARITHMETIC_SEARCH_ASTAR_ASTAR_H_

#include "AstarNode.h"

NS_CC_YHGE_BEGIN

class Astar : public CCObject {
public:
	
	Astar();
    
	virtual ~Astar(void);

	bool init();
	   
    /**
     * 重置
     * 消除搜索数据
     */
	void reset();
    
    /**
     * 设置搜索范围
     */
	void setBounding(int minX ,int minY,int maxX,int maxY);
    
    /**
     * 设置开始位置
     */
	void setStart(int x ,int y);
    
    /**
     * 设置结束位置
     */
	void setEnd(int x ,int y);
    
    /**
     * 开始搜索
     */
    bool search();
    
    /**
     * 取得搜索结果
     */
    CCArray* getPath();
	CCArray* getPathWithStart();
	CCArray* getPathWithEnd();
	CCArray* getPathWithStartEnd();
    
protected:
    
    /**
     * 检查附近格子
     * 默认搜索8方向，可以设置只搜索4方向，不搜索斜方向
     */
	bool checkNearby();
    
    /**
     * 从开启队列取得下个结点
     */
	void getNext();
	
    /**
     * 重新设置node的搜索值,并在开启队列重新排序
     */
    void setOpenSeqNode(AstarNode* node ,int g);

    /**
     * 添加结点到开启队表和开启映射表
     */
    void addToOpen(AstarNode* node);
	
    /**
     * 把结点从开启队表和开启映射表中删除
     */
    void removeFromOpen(AstarNode* node);

    /**
     * 某个位置是否已经开启，也就是搜索过
     */
    bool isInOpen(int x ,int y);
	
    /**
     * 从开启映射表取得结点
     */
	AstarNode* getFromOpen(int x ,int y);

    /**
     * 添加结点到关闭映射表
     */
	void addToClose(int x,int y);
    
    /**
     * 某个位置是否在关闭映射表
     */
	bool isInClose(int x ,int y);

    /**
     * 获取位置的搜索权值
     */
	int getH(int x ,int y);

    /**
     * 检查是否超出边界
     */
	bool isOut(int x ,int y);
    
    /**
     * 检查是否可能通过
     * 具体子类实现
     */
	virtual bool isWorkable(int x ,int y) ;
    
    /**
     * 目标点是否可以通过
     * 首选检查目标点是不是障碍点，如果是则不可通过。
     * 再检查是不是从斜对角过来的，如果是从斜对角过来要检查两旁是否可以通过
     * 如果搜索4方向不用考虑斜通过
     */
	bool isWorkableWithCrossSide(int x ,int y ,int stepX ,int stepY);
    
    /**
     * 目标点的两旁是否可以通过
     * 不检查目录点本身，只检查从斜对角过来时，两旁是否可以通过
     */
	bool isCrossSideWorkable(int x ,int y ,int stepX,int stepY);
    
    /**
     * 检查是不是结束点
     */
	bool isEnd(int x ,int  y) ;
    
    /**
     * 检查是不是结束点，并检查两旁是否可以通过
     */
	bool isEnd(int x,int y ,int stepX ,int stepY);
    
public:
    
    inline void setMinX(int minX)
    {
        m_minX = minX;
    }
    
    inline int getMinX()
    {
        return m_minX;
    }
    
    inline void setMinY(int minY)
    {
        m_minY = minY;
    }
    
    inline int getMinY()
    {
        return m_minY;
    }
    
    inline void setMaxX(int maxX)
    {
        m_maxX = maxX;
    }
    
    inline int getMaxX()
    {
        return m_maxX;
    }
    
    inline void setMaxY(int maxY)
    {
        m_maxY = maxY;
    }
    
    inline int getMaxY()
    {
        return m_maxY;
    }

protected:
    
    //搜索范围
	int m_minX;
	int m_minY;
	int m_maxX;
	int m_maxY;
	
    //开始结点
	AstarNode* m_start;

    //结束结点
	AstarNode* m_end;
    
    //当前结点
	AstarNode* m_current;
	
    //开启队列
	CCArray* m_openSeq;//开启队列，存放每个结点。结点属性,parent 父结点，x,y地图坐,f,g,h路径评分
	
	//opens closes与地图相关，一般用二维数组
	//这里使用"y,x"做为关键字，BOOL做为值的dictionary来在存储。键可替换y右移16位加上x的数值
	//当然也可以根据搜索范围(minX,minY,maxX,maxY)来生成数组，数组值是BOOL
	//TODO 比较二种方法哪种快。最好应该是关于x，y的二维hash表算法最快。
	//二元hash:先创建关于y的hash,值为关于x的hash。这样查找时间为O(2)
	CCDictionary* m_opens;//开起列表,设置地图上的坐标，表示开启状态
	CCDictionary* m_closes;//关闭列表,存放已经到达过的点
};

NS_CC_YHGE_END

#endif // YHGE_ARITHMETIC_SEARCH_ASTAR_ASTAR_H_