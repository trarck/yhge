#include "AIManager.h"
#include <yhge/Base/Log.h>

NS_CC_YHGE_BEGIN

AIManager::AIManager()
{
    YHDEBUG("AIManager create");
}

AIManager::~AIManager()
{
    YHDEBUG("AIManager destroy");
}

bool AIManager::init(void)
{
    YHDEBUG("AIManager init");
    return true;
}

NS_CC_YHGE_END
