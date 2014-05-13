#ifndef YHGE_ENTITYCOMPONENT_MANAGERS_AIMANAGER_H_
#define YHGE_ENTITYCOMPONENT_MANAGERS_AIMANAGER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * AI管理器
 */
class AIManager : public CCObject
{
public:
    
    AIManager();
    
    virtual ~AIManager();
    
    virtual bool init(void);
    	
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_MANAGERS_AIMANAGER_H_
