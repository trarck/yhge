#ifndef YHGE_ISOMETRIC_ISODYNAMICGROUP_H_
#define YHGE_ISOMETRIC_ISODYNAMICGROUP_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ISODynamicComponent.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISODynamicComponentUpdateDelegator;
class ISODynamicComponentCreateDelegator;
class ISOTileMap;

class ISODynamicGroup : public CCObject {

public:
	
	ISODynamicGroup();
    
	~ISODynamicGroup(void);
	
	/*
	 * 初始化
	 */
    virtual bool init();

	/*
	 * 设置内容
	 */
	virtual void setup();
    
	bool beforeUpdateContent();
    
	void doUpdateContent();
    
    void doUpdateComponents();
    
	void calcComponentsCount();

    virtual void initOffset(const CCPoint& tOffset);
    
    virtual void initOffset(float x,float y);
    
    virtual void scroll(const CCPoint& tOffset);
    
    virtual void scroll(float x,float y);
	    
    void setUpdateDelegator(ISODynamicComponentUpdateDelegator* pUpdateDelegator);
    
    void setCreateDelegator(ISODynamicComponentCreateDelegator* pCreateDelegator);

    void addDynamicComponent(ISODynamicComponent* dynamicComponent);

	void removeDynamicComponent(ISODynamicComponent* dynamicComponent);

	inline void setComponentTileColumn(int iComponentTileColumn)
	{
		m_iComponentTileColumn = iComponentTileColumn;
	}

	inline int getComponentTileColumn()
	{
		return m_iComponentTileColumn;
	}

	inline void setComponentTileRow(int iComponentTileRow)
	{
		m_iComponentTileRow = iComponentTileRow;
	}

	inline int getComponentTileRow()
	{
		return m_iComponentTileRow;
	}

	inline void setComponentTileExtendCount(int iComponentNodeExtendCount)
	{
		m_iComponentNodeExtendCount = iComponentNodeExtendCount;
	}

	inline int getComponentTileExtendCount()
	{
		return m_iComponentNodeExtendCount;
	}

    inline void setOffset(const CCPoint& tOffset)
	{
		m_tOffset = tOffset;
	}

	inline void setOffset(float x,float y)
	{
		m_tOffset.x=x;
		m_tOffset.y=y;
	}

	inline CCPoint getOffset()
	{
		return m_tOffset;
	}

	void setDynamiceComponentList(CCArray* dynamiceComponentList)
	{
		CC_SAFE_RETAIN(dynamiceComponentList);
		CC_SAFE_RELEASE(m_pDynamiceComponentList);
		m_pDynamiceComponentList = dynamiceComponentList;
	}

	CCArray* getDynamiceComponentList()
	{
		return m_pDynamiceComponentList;
	}

	void setTileMap(ISOTileMap* tileMap)
	{
		m_tileMap = tileMap;
	}

	ISOTileMap* getTileMap()
	{
		return m_tileMap;
	}
    
protected:
    
	/**
	 * 更新组内元素的坐标
	 */
	virtual void updateMapCoordinate(unsigned int nodeIndex,float deltaMapX,float deltaMapY);

protected:
    /**
     * 所用到的组件的行列数
     */
    int m_iComponentTileColumn;
    int m_iComponentTileRow;
    
	/**
     * 总的行列数
	 * 总的行列数是行列数的2倍。斜45度地图格子之间是有交错的。
     */
    int m_iComponentTileTotalColumn;
    int m_iComponentTileTotalRow;

    //x,y增加相同的格子数
    int m_iComponentNodeExtendCount;
    
	//需要更新的动态组件组
	CCArray* m_pDynamiceComponentList;
    
    /**
     * 地图的偏移量。屏幕坐标。
	 * 也可以理解为相机在地图上的位置
     */
	CCPoint m_tOffset;
    
    /**
     * 偏移量的地图坐标
     */
	int m_iStartX;
	int m_iStartY;

    /**
	 * 上次偏移量的地图坐标
	 */
    int m_iLastStartX;
    int m_iLastStartY;
        
	/**
	 * 组件结点索引
	 */
    int m_iComponentIndexX;
    int m_iComponentIndexY;
 
	/**
	 * 事件代理
	 */
    ISODynamicComponentUpdateDelegator* m_pUpdateDelegator;
    ISODynamicComponentCreateDelegator* m_pCreateDelegator;

    //tileMap保持弱引用
    ISOTileMap* m_tileMap;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISODYNAMICGROUP_H_
