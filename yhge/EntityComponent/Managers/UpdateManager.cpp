#include "UpdateManager.h"
#include <yhge/Base/Log.h>

NS_CC_YHGE_BEGIN

typedef struct _listEntry
{
    struct _listEntry   *prev, *next;
    IUpdateable         *updater;
    int                 priority;
    bool                paused;
    //bool                markedForDeletion; // selector will no longer be called and entry will be removed at end of the next tick
} tListEntry;

UpdateManager::UpdateManager()
:m_updating(false)
{
    YHDEBUG("UpdateManager create");
}

UpdateManager::~UpdateManager()
{
    YHDEBUG("UpdateManager destroy");
}

bool UpdateManager::init(void)
{
    YHDEBUG("UpdateManager init");
    return true;
}

void UpdateManager::update(float delta)
{
    m_updating=true;
    
    m_updating=false;
    
    if (m_willRemoveList.size()) {
        m_updaterList.e
    }
}

NS_CC_YHGE_END
