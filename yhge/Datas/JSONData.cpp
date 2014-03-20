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
    
    CC_SAFE_DELETE_ARRAY(pBytes);
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

NS_CC_YHGE_END
