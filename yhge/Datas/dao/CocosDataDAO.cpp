#include "CocosDataDAO.h"

USING_NS_CC;

NS_CC_YHGE_DATA_BEGIN

CocosDataDAO::CocosDataDAO()
:m_data(NULL)
{

}

CocosDataDAO::~CocosDataDAO()
{
    CC_SAFE_RELEASE_NULL(m_data);
}

bool CocosDataDAO::init()
{
    if (!DAO::init()) {
        return false;
    }
    m_data=new CCDictionary();
    return true;
}

void CocosDataDAO::loadFromFile(const std::string& file)
{
    m_data=CCDictionary::createWithContentsOfFile(file.c_str());
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
    CC_SAFE_RELEASE_NULL(m_data);
}

NS_CC_YHGE_DATA_END
