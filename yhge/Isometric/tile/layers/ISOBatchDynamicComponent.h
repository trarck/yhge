#ifndef YHGE_ISOMETRIC_ISOBATCHDYNAMICCOMPONENT_H_
#define YHGE_ISOMETRIC_ISOBATCHDYNAMICCOMPONENT_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include <yhge/Isometric/tile/base/ISOTile.h>
#include "ISODynamicComponent.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

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
    
    CCSpriteBatchNode* _batchNode;
    
};



NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOBATCHDYNAMICCOMPONENT_H_
