﻿#include "JSONDataDAO.h"

USING_NS_CC;

NS_CC_YHGE_DATA_BEGIN

JSONDataDAO::JSONDataDAO()
{

}

JSONDataDAO::~JSONDataDAO()
{

}

void JSONDataDAO::loadFromFile(const std::string& file)
{
	ssize_t size = 0;
    
    unsigned char * pBytes = CCFileUtils::sharedFileUtils()->getFileData(file.c_str(), "rb", &size);
    unsigned char *end = pBytes + size;
    
    Json::Reader reader;
    reader.parse((const char*)pBytes, (const char*)end, _data);
    
    CC_SAFE_DELETE_ARRAY(pBytes);
}

void JSONDataDAO::loadFromContentString(const std::string& content)
{
    Json::Reader reader;
    reader.parse(content, _data);
}

void JSONDataDAO::loadFromUrl(const std::string& url)
{
    //TODO
}

void JSONDataDAO::unload()
{
    _data=Json::Value::null;
}

NS_CC_YHGE_DATA_END
