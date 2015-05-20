#ifndef YHGE_DATA_DAO_DAOFactory_H_
#define YHGE_DATA_DAO_DAOFactory_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "JSONSqliteDAO.h"
#include "CocosSqliteDAO.h"

NS_CC_YHGE_DATA_BEGIN

class DAOFactory:public Ref
{
public:

	typedef Map<std::string, DAO*> DaoMap;
    
	DAOFactory();
    
	~DAOFactory();
    
    bool init();
    
    static DAOFactory* getInstance();
    
    JSONSqliteDAO* getJsonDao(const std::string& dbPath);
    
    CocosSqliteDAO* getCocosDao(const std::string& dbPath);
    
public:
    
    inline void setOpenFlag(unsigned int openFlag)
    {
        _openFlag = openFlag;
    }
    
    inline unsigned int getOpenFlag()
    {
        return _openFlag;
    }
    
protected:
    
    unsigned int _openFlag;
    
	DaoMap _jsonDaos;
    
	DaoMap _cocosDaos;
    
};

NS_CC_YHGE_DATA_END



#endif //YHGE_DATA_DAO_DAOFactory_H_
