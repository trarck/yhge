#ifndef YHGE_DATAS_DAO_JSONDATADAO_H_
#define YHGE_DATAS_DAO_JSONDATADAO_H_

#include <yhge/Jsoncpp/json.h>
#include "DAO.h"

NS_CC_YHGE_DATA_BEGIN

class JSONDataDAO:public DAO
{
public:
    
	JSONDataDAO();
    
	~JSONDataDAO();
    
    virtual void loadFromFile(const std::string& file);
    
    virtual void loadFromContentString(const std::string& content);
    
    virtual void loadFromUrl(const std::string& url);
    
    virtual void unload();
    
    
    inline Json::Value getValue(const std::string& key)
    {
        return _data.get(key, Json::Value::null);
    }
    
    inline void setValue(const std::string& key,int value)
    {
        _data[key]=value;
    }
    
    inline void setValue(const std::string& key,float value)
    {
        _data[key]=value;
    }
    
    inline void setValue(const std::string& key,double value)
    {
        _data[key]=value;
    }
    
    inline void setValue(const std::string& key,const std::string& value)
    {
        _data[key]=value;
    }
    
    inline void setValue(const std::string& key,Json::Value value)
    {
        _data[key]=value;
    }
    
    inline Json::Value getValue(int key)
    {
        return _data[key];
    }
    
    inline void setValue(int key,int value)
    {
        _data[key]=value;
    }
    
    inline void setValue(int key,float value)
    {
        _data[key]=value;
    }
    
    inline void setValue(int key,double value)
    {
        _data[key]=value;
    }
    
    inline void setValue(int key,const std::string& value)
    {
        _data[key]=value;
    }
    
    inline void setValue(int key,Json::Value value)
    {
        _data[key]=value;
    }
    
protected:
    
    Json::Value _data;
};

NS_CC_YHGE_DATA_END



#endif //YHGE_DATAS_DAO_JSONDATADAO_H_
