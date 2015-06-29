#ifndef YHGE_ISOMETRIC_ISODYNAMICTILELAYER_H_
#define YHGE_ISOMETRIC_ISODYNAMICTILELAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ISOTileLayer.h"
#include "ISODynamicComponent.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 动态更新可显示区域,只渲染显示区域的tile.
 * 使用batchnode来优化组件显示。
 */
class ISODynamicTileLayer : public ISOTileLayer,ISODynamicComponentCreateDelegator {

public:
	
	ISODynamicTileLayer();
    
	~ISODynamicTileLayer(void);
	
    virtual bool init();
    
    virtual bool init(Size& mapTileSize,Vec2& offset);

    virtual void setupTiles();

    //设置_dynamicComponent的column and row
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
    virtual void scroll(const Vec2& tOffset);
    
	bool isCellChange();
    void visitTileShowable();
    void visitTileShowable2();
    
    /**
     * test bounding
     */
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
        
    Sprite* createTile();

public:
    
    virtual void setDynamicComponent(ISODynamicComponent* dynamicComponent);
    
    virtual ISODynamicComponent* getDynamicComponent();
   
    
protected:

    ISODynamicComponent* _dynamicComponent;
    
    /**
     * 上次移动的地图位置
     */
    int _iLastStartX;
    int _iLastStartY;
    
//	Vec2 _lastStartPoint;
    
//	int _iStartX;
//	int _iStartY;
};



NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISODYNAMICTILELAYER_H_
