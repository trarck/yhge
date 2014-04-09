#ifndef YHGE_DATAS_DB_DAOFactory_H_
#define YHGE_DATAS_DB_DAOFactory_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "JSONDAO.h"
#include "CocosDAO.h"

NS_CC_YHGE_BEGIN

class DAOFactory:public CCObject
{
public:
    
	DAOFactory();
    
	~DAOFactory();
    
    bool init();
    
    static DAOFactory* getInstance();
    
    JSONDAO* getJsonDao(const std::string& dbPath);
    
    CocosDAO* getCocosDao(const std::string& dbPath);
    
public:
    
    inline void setOpenFlag(unsigned int openFlag)
    {
        m_openFlag = openFlag;
    }
    
    inline unsigned int getOpenFlag()
    {
        return m_openFlag;
    }
    
protected:
    
    unsigned int m_openFlag;
    
    CCDictionary* m_jsonDaos;
    
    CCDictionary* m_cocosDaos;
    
};

NS_CC_YHGE_END



#endif //YHGE_DATAS_DB_DAOFactory_H_
