#include "DAOFactory.h"
#include <sqlite3.h>

USING_NS_CC;


NS_CC_YHGE_DATA_BEGIN

static DAOFactory* sDaoFactoryInstance=NULL;

DAOFactory::DAOFactory()
:_jsonDaos(NULL)
,_cocosDaos(NULL)
,_openFlag(SQLITE_OPEN_READWRITE)
{
    
}

DAOFactory::~DAOFactory()
{
    CC_SAFE_RELEASE_NULL(_jsonDaos);
    CC_SAFE_RELEASE_NULL(_cocosDaos);
}

bool DAOFactory::init()
{
    _jsonDaos=new CCDictionary();
    
    _cocosDaos=new CCDictionary();
    
    return true;
}

DAOFactory* DAOFactory::getInstance()
{
    if (!sDaoFactoryInstance) {
        sDaoFactoryInstance=new DAOFactory();
        sDaoFactoryInstance->init();
    }
    
    return sDaoFactoryInstance;
}

JSONSqliteDAO* DAOFactory::getJsonDao(const std::string& dbPath)
{
    JSONSqliteDAO* dao=static_cast<JSONSqliteDAO*>(_jsonDaos->objectForKey(dbPath));
    
    if (!dao) {
        dao=new JSONSqliteDAO();
        dao->init(dbPath, _openFlag);
        
        _jsonDaos->setObject(dao, dbPath);
    }
    
    return dao;
}

CocosSqliteDAO* DAOFactory::getCocosDao(const std::string& dbPath)
{
    CocosSqliteDAO* dao=static_cast<CocosSqliteDAO*>(_cocosDaos->objectForKey(dbPath));
    
    if (!dao) {
        dao=new CocosSqliteDAO();
        dao->init(dbPath, _openFlag);
        
        _cocosDaos->setObject(dao, dbPath);
    }
    
    return dao;
}

NS_CC_YHGE_DATA_END
