#ifndef YHGE_ISOMETRIC_ISODYNAMICTILELAYER_H_
#define YHGE_ISOMETRIC_ISODYNAMICTILELAYER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "ISOTileLayer.h"
#include "ISODynamicComponent.h"

NS_CC_YHGE_BEGIN

/**
 * 动态更新可显示区域,只渲染显示区域的tile.
 * 使用batchnode来优化组件显示。
 */
class ISODynamicTileLayer : public ISOTileLayer,ISODynamicComponentCreateDelegator {

public:
	
	ISODynamicTileLayer();
    
	~ISODynamicTileLayer(void);
	
    virtual bool init();
    
    virtual bool init(CCSize& mapTileSize,CCPoint& offset);

    virtual void setupTiles();

    //设置m_pDynamicComponent的column and row
    void setComponentColumnAndRow();
    /**
     * 更新前检查
     */
	bool beforeUpdateContent();
    
    /**
     * 更新内容
     */
	void doUpdateContent();

    /**
     * 移动位置
     * 只作判断使用，不改变显示位置
     */
    virtual void scroll(const CCPoint& tOffset);
    
	bool isCellChange();
    void visitTileShowable();
    void visitTileShowable2();
    
    /**
     * test bounding
     */
    virtual void draw();
        
    CCSprite* createTile();

public:
    
    virtual void setDynamicComponent(ISODynamicComponent* pDynamicComponent);
    
    virtual ISODynamicComponent* getDynamicComponent();
   
    
protected:

    ISODynamicComponent* m_pDynamicComponent;
    
    /**
     * 上次移动的地图位置
     */
    int m_iLastStartX;
    int m_iLastStartY;
    
//	CCPoint m_tLastStartPoint;
    
//	int m_iStartX;
//	int m_iStartY;
};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISODYNAMICTILELAYER_H_
