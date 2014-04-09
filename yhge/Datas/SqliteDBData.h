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
    
    bool init();
    
    bool init(JSONDAO* dao);
    
    bool init(JSONDAO* dao,const std::string& table);
    
    virtual void loadFromFile(const std::string& file);
    
    virtual void loadFromContentString(const std::string& content);
    
    virtual void loadFromUrl(const std::string& url);
    
    virtual void unload();
    
    Json::Value loadData(int key);
    
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
    
    inline void setTable(const std::string& table)
    {
        m_table = table;
    }
    
    inline const std::string& getTable()
    {
        return m_table;
    }
    
    inline void setKey(const std::string& key)
    {
        m_key = key;
    }
    
    inline const std::string& getKey()
    {
        return m_key;
    }
    
protected:
    
    JSONDAO* m_dao;
    
    std::string m_table;
    
    std::string m_key;
};

NS_CC_YHGE_END



#endif //YHGE_DATAS_SQLITEDBDATA_H_
