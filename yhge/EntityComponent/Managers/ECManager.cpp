#include "ECManager.h"
#include <yhge/Base/Log.h>
#include "../Engine.h"

NS_CC_YHGE_BEGIN

ECManager::ECManager()
:m_engine(NULL)
{
    YHDEBUG("ECManager create");
}

ECManager::~ECManager()
{
    YHDEBUG("ECManager destroy");
}

bool ECManager::init(void)
{
    YHDEBUG("ECManager init");
    return true;
}

void ECManager::setEngine(Engine* engine)
{
    m_engine=engine;
}

Engine* ECManager::getEngine()
{
    return m_engine;
}

NS_CC_YHGE_END
