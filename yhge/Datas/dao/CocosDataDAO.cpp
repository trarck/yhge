#include "CocosDataDAO.h"

USING_NS_CC;

NS_CC_YHGE_DATA_BEGIN

CocosDataDAO::CocosDataDAO()
{

}

CocosDataDAO::~CocosDataDAO()
{

}

bool CocosDataDAO::init()
{
    if (!DAO::init()) {
        return false;
    }
    return true;
}

void CocosDataDAO::loadFromFile(const std::string& file)
{
	_data = FileUtils::getInstance()->getValueMapFromFile(file);
}

void CocosDataDAO::loadFromContentString(const std::string& content)
{
	_data = FileUtils::getInstance()->getValueMapFromData(content.c_str(),content.size());
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
