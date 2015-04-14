#ifndef YHGE_ENTITYCOMPONENT_MANAGERS_ECMANAGER_H_
#define YHGE_ENTITYCOMPONENT_MANAGERS_ECMANAGER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class Engine;

/**
 * base manager
 */
class ECManager : public Ref
{
public:
    
    ECManager();
    
    virtual ~ECManager();
    
    virtual bool init(void);
    
    virtual void setEngine(Engine* engine);
    virtual Engine* getEngine();
    
protected:
    //weak refrence
    Engine* _engine;
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_MANAGERS_ECMANAGER_H_
