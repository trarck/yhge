#ifndef YHGE_ISOMETRIC_ISODYNAMICCOMPONENT_H_
#define YHGE_ISOMETRIC_ISODYNAMICCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "../ISOTileInterfaces.h"
#include "../renderer/ISOComponentNode.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOTileLayer;

/**
 * 动态更新组件
 * 根据Isometric.Game.Programming.with.DirectX.7描述的渲染地图扩展而成
 */
class ISODynamicComponent : public Node {

public:

	typedef Vector<ISOComponentNode*> ComponentNodeVecotr;
	
	ISODynamicComponent();
    
	~ISODynamicComponent(void);
	
    virtual bool init();
    
	bool beforeUpdateContent();
    
	void doUpdateContent();
    
    void doUpdateComponents();

	/**
	 * 更新索引为nodeIndex的元素的坐标和显示内容
	 * 并且通知delegate这个改变
	 */
	virtual void updateMapCoordinate(unsigned int nodeIndex,float deltaMapX,float deltaMapY);
	
	/**
	 * 更新索引为nodeIndex的元素的坐标和显示内容
	 * 
	 */
	virtual void updateNodeBy(unsigned int nodeIndex,float deltaMapX,float deltaMapY);

	/**
	 * 更新索引为nodeIndex的元素的坐标和显示内容
	 */
	virtual void updateNode(ISOComponentNode* node,float mx,float my);

	void calcComponentsCount();
    
	virtual void createComponents();
    
    virtual void initComponents();
    
    virtual void setupComponents();
    
    virtual void setupComponents(const Vec2& position);
    
	virtual ComponentNodeVecotr& getComponents();

    virtual void inioffset(const Vec2& offset);
    
    virtual void inioffset(float x,float y);
    
    virtual void scroll(const Vec2& offset);
    
    virtual void scroll(float x,float y);
    
    virtual void setComponentTileColumn(int iComponentTileColumn);
    
    virtual int getComponentTileColumn();
    
    virtual void setComponentTileRow(int iComponentTileRow);
    
    virtual int getComponentTileRow();
    
    virtual void setComponentTileExtendCount(int iComponentNodeExtendCount);
    
    virtual int getComponentTileExtendCount();

    virtual void setOffset(const Vec2& offset);
    
	virtual void setOffset(float x,float y);

    virtual Vec2 getOffset();
    
    void setUpdateDelegator(ISODynamicComponentUpdateDelegator* updateDelegator);
    
    void setCreateDelegator(ISODynamicComponentCreateDelegator* createDelegator);

    //weak ref
    virtual void setTileLayer(ISOTileLayer* tileLayer);
    
    virtual ISOTileLayer* getTileLayer();
       
protected:
    
    int _iComponentTileColumn;
    int _iComponentTileRow;
    
    int _iComponentTileTotalColumn;
    int _iComponentTileTotalRow;
    //x,y增加相同的格子数
    int _iComponentNodeExtendCount;
    
	ComponentNodeVecotr _components;
    
    /**
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
	Vec2 _offset;
    
    /**
     * 偏移量的地图坐标
     */
	int _iStartX;
	int _iStartY;

    
    int _iLastStartX;
    int _iLastStartY;
        
    int _iComponentIndexX;
    int _iComponentIndexY;
    
    ISOTileLayer* _tileLayer;
    
    ISODynamicComponentUpdateDelegator* _updateDelegator;
    ISODynamicComponentCreateDelegator* _createDelegator;
    
    
};



NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISODYNAMICCOMPONENT_H_
