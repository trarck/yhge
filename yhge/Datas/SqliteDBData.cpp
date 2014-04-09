#include "SqliteDBData.h"
#include "db/DAOFactory.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

SqliteDBData::SqliteDBData()
:m_dao(NULL)
,m_table("")
,m_key("id")
{
    
}

SqliteDBData::~SqliteDBData()
{
    CC_SAFE_RELEASE_NULL(m_dao);
}

bool SqliteDBData::init()
{
    return BaseData::init();
}

bool SqliteDBData::init(JSONDAO* dao)
{
    if (BaseData::init()) {
        setDao(dao);
        
        return true;
    }
    
    return false;
}

bool SqliteDBData::init(JSONDAO* dao,const std::string& table)
{
    if (BaseData::init()) {
        
        setDao(dao);
        
        m_table=table;
        
        return true;
    }
    
    return false;
}

void SqliteDBData::loadFromFile(const std::string& file)
{
    JSONDAO* dao=DAOFactory::getInstance()->getJsonDao(file);
    
    setDao(dao);
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

Json::Value SqliteDBData::loadData(int key)
{
    std::string loadSql="SELECT * FROM "+m_table+" WHERE "+m_key+" = ?";
    return m_dao->load(loadSql,key);
}

NS_CC_YHGE_END
