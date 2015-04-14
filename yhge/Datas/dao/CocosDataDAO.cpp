#include "CocosDataDAO.h"

USING_NS_CC;

NS_CC_YHGE_DATA_BEGIN

CocosDataDAO::CocosDataDAO()
:_data(NULL)
{

}

CocosDataDAO::~CocosDataDAO()
{
    CC_SAFE_RELEASE_NULL(_data);
}

bool CocosDataDAO::init()
{
    if (!DAO::init()) {
        return false;
    }
    _data=new CCDictionary();
    return true;
}

void CocosDataDAO::loadFromFile(const std::string& file)
{
    _data=CCDictionary::createWithContentsOfFile(file.c_str());
}

void CocosDataDAO::loadFromContentString(const std::string& content)
{
    //TODO
}

void CocosDataDAO::loadFromUrl(const std::string& url)
{
    //TODO
}

void CocosDataDAO::unload()
{
    CC_SAFE_RELEASE_NULL(_data);
}

NS_CC_YHGE_DATA_END
