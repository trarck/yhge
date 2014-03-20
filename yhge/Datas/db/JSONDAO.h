#ifndef YHGE_DATAS_DB_JSONDAO_H_
#define YHGE_DATAS_DB_JSONDAO_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Jsoncpp/json.h>
#include <yhge/Sqlite/SqliteDriver.h>
#include <yhge/CocosExt/CCRef.h>

NS_CC_YHGE_BEGIN

typedef CCRef<sqlite::SqliteDriver*> CocosSqliteDriver;

class JSONDAO:public CCObject
{
public:
    
	JSONDAO();
    
	~JSONDAO();
    
    bool init();
    
    bool init(const std::string& dbPath,int flag);
    
    int fetchNumber(const std::string& querySql);
    
    Json::Value fetchAll(const std::string& querySql);
    
    Json::Value fetchOne(const std::string& querySql);

    int insert(const std::string& table,const Json::Value& data);
    
    int update(const std::string& table,const Json::Value& data);
    
    int replace(const std::string& table,const Json::Value& data);
    
    int remove(const std::string& table,const Json::Value& where);
    
protected:
    
	std::string formateToPrepare(const Json::Value& data);
    
    
public:
    
    inline CocosSqliteDriver* getDriver()
    {
        return m_driver;
    }
    
protected:
    
    CocosSqliteDriver* m_driver;

};

NS_CC_YHGE_END



#endif //YHGE_DATAS_DB_JSONDAO_H_
