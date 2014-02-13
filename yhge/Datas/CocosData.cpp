#include "CocosData.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

CocosData::CocosData()
:m_data(NULL)
{

}

CocosData::~CocosData()
{
    CC_SAFE_RELEASE_NULL(m_data);
}

bool CocosData::init()
{
    if (!BaseData::init()) {
        return false;
    }
    m_data=new CCDictionary();
    return true;
}

void CocosData::loadFromFile(const std::string& file)
{
    m_data=CCDictionary::createWithContentsOfFile(file.c_str());
}

void CocosData::loadFromContentString(const std::string& content)
{
    //TODO
}

void CocosData::loadFromUrl(const std::string& url)
{
    //TODO
}

void CocosData::unload()
{
    CC_SAFE_RELEASE_NULL(m_data);
}

NS_CC_YHGE_END
