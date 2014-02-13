#ifndef YHGE_DATAS_COCOSDATA_H_
#define YHGE_DATAS_COCOSDATA_H_

#include "BaseData.h"
#include <yhge/Jsoncpp/json.h>

NS_CC_YHGE_BEGIN

class JSONData:public BaseData
{
public:
    
	JSONData();
    
	~JSONData();
    
    virtual void loadFromFile(const std::string& file);
    
    virtual void loadFromContentString(const std::string& content);
    
    virtual void loadFromUrl(const std::string& url);
    
    virtual void unload();
    
    Json::Value getValue(const std::string& key);

    void setValue(const std::string& key,int value);
    
    void setValue(const std::string& key,float value);
    
    void setValue(const std::string& key,double value);
    
    void setValue(const std::string& key,const std::string& value);
    
    void setValue(const std::string& key,Json::Value value);
    
protected:
    
    Json::Value m_data;
};

NS_CC_YHGE_END



#endif //YHGE_DATAS_COCOSDATA_H_
