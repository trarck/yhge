#ifndef YHGE_ISOMETRIC_ISOBATCHDYNAMICCOMPONENT_H_
#define YHGE_ISOMETRIC_ISOBATCHDYNAMICCOMPONENT_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "ISOComponentNode.h"
#include "ISODynamicComponent.h"

NS_CC_YHGE_BEGIN

class ISOTileLayer;

class ISOBatchDynamicComponent : public ISODynamicComponent {

public:
	
	ISOBatchDynamicComponent();
    
	~ISOBatchDynamicComponent(void);
	
    virtual bool init();
    
	void createComponents();
protected:
    
    virtual void updateNode(ISOComponentNode* node,float mx,float my);
    
protected:
    
    CCSpriteBatchNode* m_pBatchNode;
    
};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOBATCHDYNAMICCOMPONENT_H_
