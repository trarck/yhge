#ifndef YHGE_DATAS_SQLITEDBDATA_H_
#define YHGE_DATAS_SQLITEDBDATA_H_

#include "BaseData.h"
#include <yhge/Jsoncpp/json.h>
#include "db/JSONDAO.h"

NS_CC_YHGE_BEGIN

class SqliteDBData:public BaseData
{
public:
    
	SqliteDBData();
    
	~SqliteDBData();
    
    virtual void loadFromFile(const std::string& file);
    
    virtual void loadFromContentString(const std::string& content);
    
    virtual void loadFromUrl(const std::string& url);
    
    virtual void unload();
    
public:
    
    inline void setDao(JSONDAO* dao)
    {
        CC_SAFE_RETAIN(dao);
        CC_SAFE_RELEASE(m_dao);
        m_dao = dao;
    }
    
    inline JSONDAO* getDao()
    {
        return m_dao;
    }
protected:
    
    JSONDAO* m_dao;
};

NS_CC_YHGE_END



#endif //YHGE_DATAS_SQLITEDBDATA_H_
