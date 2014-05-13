#include "UpdateManager.h"
#include <yhge/Base/Log.h>

NS_CC_YHGE_BEGIN

UpdateManager::UpdateManager()
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

NS_CC_YHGE_END
