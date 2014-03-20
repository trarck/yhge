#include "SqliteDBData.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

SqliteDBData::SqliteDBData()
:m_dao(NULL)
{

}

SqliteDBData::~SqliteDBData()
{
    CC_SAFE_RELEASE_NULL(m_dao);
}

void SqliteDBData::loadFromFile(const std::string& file)
{
    //do nothing
    //数据的访问通过dao来实现
}

void SqliteDBData::loadFromContentString(const std::string& content)
{
    //do nothing
    //数据的访问通过dao来实现
}

void SqliteDBData::loadFromUrl(const std::string& url)
{
    //do nothing
    //数据的访问通过dao来实现
}

void SqliteDBData::unload()
{
    setDao(NULL);
}


NS_CC_YHGE_END
