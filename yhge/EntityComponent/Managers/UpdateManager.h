#ifndef YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_
#define YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class UpdateGroup:public CCObject
{
public:
    
    
};

/**
 * 更新管理器
 * 负责组件的更新统一处理
 */
class UpdateManager : public CCObject
{
public:
    
    UpdateManager();
    
    virtual ~UpdateManager();
    
    virtual bool init(void);
    	
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_
