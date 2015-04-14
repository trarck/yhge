#ifndef YHGE_ENTITYCOMPONENT_PROPERTIES_ISOMETRICPROPERTY_H_
#define YHGE_ENTITYCOMPONENT_PROPERTIES_ISOMETRICPROPERTY_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * 组件系统基类
 */
class IsometricProperty : public Ref
{
public:
    
    IsometricProperty();
    
    virtual ~IsometricProperty();
    
    virtual bool init(void);

};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_PROPERTIES_ISOMETRICPROPERTY_H_
