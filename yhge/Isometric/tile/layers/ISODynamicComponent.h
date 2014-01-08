#ifndef YHGE_ISOMETRIC_ISODYNAMICCOMPONENT_H_
#define YHGE_ISOMETRIC_ISODYNAMICCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "../base/ISOComponentNode.h"

#define ComponentExtendCount 2

NS_CC_YHGE_BEGIN

class ISOTileLayer;

class ISODynamicComponentUpdateDelegator
{
public:
    virtual void updateComponentMapCoordinate(unsigned int index,float deltaMapX,float deltaMapY)=0;
};

class ISODynamicComponentCreateDelegator
{
public:
    virtual CCSprite* createTile()=0;
};



class ISODynamicComponent : public CCNode {

public:
	
	ISODynamicComponent();
    
	~ISODynamicComponent(void);
	
    virtual bool init();
    
	bool beforeUpdateContent();
    
	void doUpdateContent();
    
    void doUpdateComponents();

	void calcComponentsCount();
    
	virtual void createComponents();
    
    virtual void initComponents();
    
    virtual void setupComponents();
    
    virtual void setupComponents(const CCPoint& position);
    
    virtual CCArray* getComponents();

    virtual void initOffset(const CCPoint& tOffset);
    
    virtual void initOffset(float x,float y);
    
    virtual void scroll(const CCPoint& tOffset);
    
    virtual void scroll(float x,float y);
    
    virtual void setComponentTileColumn(int iComponentTileColumn);
    
    virtual int getComponentTileColumn();
    
    virtual void setComponentTileRow(int iComponentTileRow);
    
    virtual int getComponentTileRow();
    
    virtual void setComponentTileExtendCount(int iComponentNodeExtendCount);
    
    virtual int getComponentTileExtendCount();

    virtual void setOffset(const CCPoint& tOffset);
    
	virtual void setOffset(float x,float y);

    virtual CCPoint getOffset();
    
    void setUpdateDelegator(ISODynamicComponentUpdateDelegator* pUpdateDelegator);
    
    void setCreateDelegator(ISODynamicComponentCreateDelegator* pCreateDelegator);

    //weak ref
    virtual void setTileLayer(ISOTileLayer* pTileLayer);
    
    virtual ISOTileLayer* getTileLayer();
    
protected:
    
    virtual void updateNode(ISOComponentNode* node,float mx,float my);
    
    virtual void updateMapCoordinate(unsigned int nodeIndex,float deltaMapX,float deltaMapY);
    
protected:
    
    int m_iComponentTileColumn;
    int m_iComponentTileRow;
    
    int m_iComponentTileTotalColumn;
    int m_iComponentTileTotalRow;
    //x,y增加相同的格子数
    int m_iComponentNodeExtendCount;
    
	//ISOComponentNode** m_pComponents;
	CCArray* m_pComponents;
    
    /**
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
	CCPoint m_tOffset;
    
    /**
     * 偏移量的地图坐标
     */
	int m_iStartX;
	int m_iStartY;

    
    int m_iLastStartX;
    int m_iLastStartY;
        
    int m_iComponentIndexX;
    int m_iComponentIndexY;
    
    ISOTileLayer* m_pTileLayer;
    
    ISODynamicComponentUpdateDelegator* m_pUpdateDelegator;
    ISODynamicComponentCreateDelegator* m_pCreateDelegator;
    
    
};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISODYNAMICCOMPONENT_H_
