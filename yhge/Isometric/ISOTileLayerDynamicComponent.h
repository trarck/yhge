#ifndef YHGE_ISOMETRIC_ISOTileLayerDynamicComponent_H_
#define YHGE_ISOMETRIC_ISOTileLayerDynamicComponent_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "ISOOptimizedTileLayer.h"
#include "ISOComponentNode.h"

NS_CC_YHGE_BEGIN

/**
 * 更加优化的动态显示layer.
 * 使用固定的组件来做显示的容器，避免频繁的创建和删除显示的tile
 * 目录已经废弃不用，直接DynamicComponent+DynamicLayer
 */
class ISOTileLayerDynamicComponent : public ISOOptimizedTileLayer {

public:
	
	ISOTileLayerDynamicComponent();
    
	~ISOTileLayerDynamicComponent(void);
	
    virtual bool init();
    
	virtual void initOffset(const CCPoint& tOffset);
    virtual void initOffset(float x,float y);
    
    CCSprite* createTile();

	bool beforeUpdateContent();
	void doUpdateContent();
    void doUpdateComponents();

	void calcComponentsCount();
	void createComponents();
    void initComponents();
    void setupComponents(int iComponentNodeExtendCount);
	void setupComponents(int iComponentNodeExtendCount,const CCPoint& position);
//    virtual void draw();
    
    virtual void setComponentTileColumn(int iComponentTileColumn);
    virtual int getComponentTileColumn();
    
    virtual void setComponentTileRow(int iComponentTileRow);
    virtual int getComponentTileRow();
    
    virtual void setComponentTileExtendCount(int iComponentNodeExtendCount);
    virtual int getComponentTileExtendCount();


    virtual void scroll(const CCPoint& tOffset);
    virtual void scroll(float x,float y);


protected:
    int m_iComponentTileColumn;
    int m_iComponentTileRow;
    
    int m_iComponentTileTotalColumn;
    int m_iComponentTileTotalRow;
    //x,y增加相同的格子数
    int m_iComponentNodeExtendCount;
    
	//ISOComponentNode** m_pComponents;
	CCArray* m_pComponents;
    
    int m_iLastStartX;
    int m_iLastStartY;
    
    int m_iComponentIndexX;
    int m_iComponentIndexY;
    
};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOTileLayerDynamicComponent_H_
