#include "DAOFactory.h"
#include <sqlite3.h>

USING_NS_CC;


NS_CC_YHGE_BEGIN

static DAOFactory* sDaoFactoryInstance=NULL;

DAOFactory::DAOFactory()
:m_jsonDaos(NULL)
,m_cocosDaos(NULL)
,m_openFlag(SQLITE_OPEN_READWRITE)
{
    
}

DAOFactory::~DAOFactory()
{
    CC_SAFE_RELEASE_NULL(m_jsonDaos);
    CC_SAFE_RELEASE_NULL(m_cocosDaos);
}

bool DAOFactory::init()
{
    m_jsonDaos=new CCDictionary();
    
    m_cocosDaos=new CCDictionary();
    
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

JSONDAO* DAOFactory::getJsonDao(const std::string& dbPath)
{
    JSONDAO* dao=static_cast<JSONDAO*>(m_jsonDaos->objectForKey(dbPath));
    
    if (!dao) {
        dao=new JSONDAO();
        dao->init(dbPath, m_openFlag);
        
        m_jsonDaos->setObject(dao, dbPath);
    }
    
    return dao;
}

CocosDAO* DAOFactory::getCocosDao(const std::string& dbPath)
{
    CocosDAO* dao=static_cast<CocosDAO*>(m_cocosDaos->objectForKey(dbPath));
    
    if (!dao) {
        dao=new CocosDAO();
        dao->init(dbPath, m_openFlag);
        
        m_cocosDaos->setObject(dao, dbPath);
    }
    
    return dao;
}

NS_CC_YHGE_END
