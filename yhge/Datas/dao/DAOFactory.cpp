#include "DAOFactory.h"
#include <sqlite3.h>

USING_NS_CC;


NS_CC_YHGE_DATA_BEGIN

static DAOFactory* sDaoFactoryInstance=NULL;

DAOFactory::DAOFactory()
:_openFlag(SQLITE_OPEN_READWRITE)
{
    
}

DAOFactory::~DAOFactory()
{

}

bool DAOFactory::init()
{
   
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
    JSONSqliteDAO* dao=static_cast<JSONSqliteDAO*>(_jsonDaos.at(dbPath));
    
    if (!dao) {
        dao=new JSONSqliteDAO();
        dao->init(dbPath, _openFlag);
        
        _jsonDaos.insert(dbPath,dao);
    }
    
    return dao;
}

CocosSqliteDAO* DAOFactory::getCocosDao(const std::string& dbPath)
{
    CocosSqliteDAO* dao=static_cast<CocosSqliteDAO*>(_cocosDaos.at(dbPath));
    
    if (!dao) {
        dao=new CocosSqliteDAO();
        dao->init(dbPath, _openFlag);
        
		_cocosDaos.insert(dbPath, dao);
    }
    
    return dao;
}

NS_CC_YHGE_DATA_END
