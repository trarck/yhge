#ifndef YHGE_ISOMETRIC_ISODYNAMICGROUP_H_
#define YHGE_ISOMETRIC_ISODYNAMICGROUP_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ISODynamicComponent.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISODynamicComponentUpdateDelegator;
class ISODynamicComponentCreateDelegator;
class ISOTileMap;

class ISODynamicGroup : public Ref {

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
		_iComponentTileColumn = iComponentTileColumn;
	}

	inline int getComponentTileColumn()
	{
		return _iComponentTileColumn;
	}

	inline void setComponentTileRow(int iComponentTileRow)
	{
		_iComponentTileRow = iComponentTileRow;
	}

	inline int getComponentTileRow()
	{
		return _iComponentTileRow;
	}

	inline void setComponentTileExtendCount(int iComponentNodeExtendCount)
	{
		_iComponentNodeExtendCount = iComponentNodeExtendCount;
	}

	inline int getComponentTileExtendCount()
	{
		return _iComponentNodeExtendCount;
	}

    inline void setOffset(const CCPoint& tOffset)
	{
		_tOffset = tOffset;
	}

	inline void setOffset(float x,float y)
	{
		_tOffset.x=x;
		_tOffset.y=y;
	}

	inline CCPoint getOffset()
	{
		return _tOffset;
	}

	void setDynamiceComponentList(CCArray* dynamiceComponentList)
	{
		CC_SAFE_RETAIN(dynamiceComponentList);
		CC_SAFE_RELEASE(_pDynamiceComponentList);
		_pDynamiceComponentList = dynamiceComponentList;
	}

	CCArray* getDynamiceComponentList()
	{
		return _pDynamiceComponentList;
	}

	void setTileMap(ISOTileMap* tileMap)
	{
		_tileMap = tileMap;
	}

	ISOTileMap* getTileMap()
	{
		return _tileMap;
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
    int _iComponentTileColumn;
    int _iComponentTileRow;
    
	/**
     * 总的行列数
	 * 总的行列数是行列数的2倍。斜45度地图格子之间是有交错的。
     */
    int _iComponentTileTotalColumn;
    int _iComponentTileTotalRow;

    //x,y增加相同的格子数
    int _iComponentNodeExtendCount;
    
	//需要更新的动态组件组
	CCArray* _pDynamiceComponentList;
    
    /**
     * 地图的偏移量。屏幕坐标。
	 * 也可以理解为相机在地图上的位置
     */
	CCPoint _tOffset;
    
    /**
     * 偏移量的地图坐标
     */
	int _iStartX;
	int _iStartY;

    /**
	 * 上次偏移量的地图坐标
	 */
    int _iLastStartX;
    int _iLastStartY;
        
	/**
	 * 组件结点索引
	 */
    int _iComponentIndexX;
    int _iComponentIndexY;
 
	/**
	 * 事件代理
	 */
    ISODynamicComponentUpdateDelegator* _pUpdateDelegator;
    ISODynamicComponentCreateDelegator* _pCreateDelegator;

    //tileMap保持弱引用
    ISOTileMap* _tileMap;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISODYNAMICGROUP_H_
