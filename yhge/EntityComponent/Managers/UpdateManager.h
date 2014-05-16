#ifndef YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_
#define YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/EntityComponent/Components/Component.h>
#include <yhge/EntityComponent/Interfaces/IUpdateable.h>

NS_CC_YHGE_BEGIN

struct _listEntry;

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
    
    void update(float delta);
    
    void addUpdater(IUpdateable* updater,int priority);
    
    void removeUpdater(IUpdateable* updater);
    
public:
    
    inline void setUpdating(bool updating)
    {
        m_updating = updating;
    }
    
    inline bool isUpdating()
    {
        return m_updating;
    }
    
protected:
    
    struct _listEntry *m_pUpdatesNegList;        // list of priority < 0
    struct _listEntry *m_pUpdates0List;          // list priority == 0
    struct _listEntry *m_pUpdatesPosList;        // list priority > 0
    
    bool m_updating;
    
    std::vector<IUpdateable*> m_willRemoveList;
    	
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_
