#include "JSONData.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

JSONData::JSONData()
{

}

JSONData::~JSONData()
{

}

void JSONData::loadFromFile(const std::string& file)
{
    unsigned long size = 0;
    
    unsigned char * pBytes = CCFileUtils::sharedFileUtils()->getFileData(file.c_str(), "rb", &size);
    unsigned char *end = pBytes + size;
    
    Json::Reader reader;
    reader.parse((const char*)pBytes, (const char*)end, m_data);
}

void JSONData::loadFromContentString(const std::string& content)
{
    Json::Reader reader;
    reader.parse(content, m_data);
}

void JSONData::loadFromUrl(const std::string& url)
{
    //TODO
}

void JSONData::unload()
{
    m_data=Json::Value::null;
}

Json::Value JSONData::getValue(const std::string& key)
{
    return m_data.get(key, Json::Value::null);
}

void JSONData::setValue(const std::string& key,int value)
{
    m_data[key]=value;
}

void JSONData::setValue(const std::string& key,float value)
{
    m_data[key]=value;
}

void JSONData::setValue(const std::string& key,double value)
{
    m_data[key]=value;
}

void JSONData::setValue(const std::string& key,const std::string& value)
{
    m_data[key]=value;
}

void JSONData::setValue(const std::string& key,Json::Value value)
{
    m_data[key]=value;
}

NS_CC_YHGE_END
