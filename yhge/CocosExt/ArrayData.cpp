#include "ArrayData.h"
#include "DictionaryData.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN


ArrayData::ArrayData()
:m_pData(NULL)
{
    
}

ArrayData::~ArrayData()
{
    CC_SAFE_RELEASE(m_pData);
}

bool ArrayData::init()
{
    m_pData=new CCArray();
	m_pData->init();
	
    return true;
}

bool ArrayData::init(CCArray* pData)
{
    setData(pData);
    
    return true;
}

void ArrayData::loadFromFile(const char* ArrayDataPath)
{
    CCArray* pData=CCArray::createWithContentsOfFile(ArrayDataPath);
    setData(pData);
}

void ArrayData::loadFromString(const char *content)
{
    
}

int ArrayData::getInt(int index)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    return pValue?pValue->intValue():0;
}

unsigned int ArrayData::getUint(int index)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    return pValue?pValue->uintValue():0;
}

float ArrayData::getFloat(int index)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    return pValue?pValue->floatValue():0.0f;
}

double ArrayData::getDouble(int index)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    return pValue?pValue->doubleValue():0.0f;
}

bool ArrayData::getBool(int index)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    return pValue?pValue->boolValue():false;
}

const char* ArrayData::getCString(int index)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    return pValue?pValue->getCString():"";
}

std::string ArrayData::getStdString(int index)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    return pValue?std::string(pValue->getCString()):"";
}

CCDictionary* ArrayData::getDictionary(int index)
{
    return static_cast<CCDictionary*>(m_pData->objectAtIndex(index));
}

CCArray* ArrayData::getArray(int index)
{
    return static_cast<CCArray*>(m_pData->objectAtIndex(index));
}


ArrayData* ArrayData::getArrayData(int index)
{
    CCArray* data=getArray(index);
    if (data) {
        ArrayData* pRet=new ArrayData();
        pRet->init(data);
        pRet->autorelease();
        return pRet;
    }
    return NULL;
}

DictionaryData* ArrayData::getDictionaryData(int index)
{
    CCDictionary* data=getDictionary(index);
    if (data) {
        DictionaryData* pRet=new DictionaryData();
        pRet->init(data);
        pRet->autorelease();
        return pRet;
    }
    return NULL;
}

bool ArrayData::safeGetInt(int index,int* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    if (pValue) {
        *pResult=pValue->intValue();
        return true;
    }
    return false;
}

bool ArrayData::safeGetUint(int index,unsigned int* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    if (pValue) {
        *pResult=pValue->uintValue();
        return true;
    }
    return false;
}

bool ArrayData::safeGetFloat(int index,float* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    if (pValue) {
        *pResult=pValue->floatValue();
        return true;
    }
    return false;
}

bool ArrayData::safeGetDouble(int index,double* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    if (pValue) {
        *pResult=pValue->doubleValue();
        return true;
    }
    return false;
}

bool ArrayData::safeGetBool(int index,bool* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    if (pValue) {
        *pResult=pValue->boolValue();
        return true;
    }
    return false;
}

bool ArrayData::safeGetStdString(int index,std::string& sResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    if (pValue) {
        sResult=pValue->getCString();
        return true;
    }
    return false;
}

bool ArrayData::safeGetCString(int index,const char** pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    if (pValue) {
        *pResult=pValue->getCString();
        return true;
    }
    return false;
}

bool ArrayData::safeGetCStringBytes(int index,char* buffer)
{
	CCString* pValue=static_cast<CCString*>(m_pData->objectAtIndex(index));
    if (pValue) {
        strcpy(buffer, pValue->getCString());
        return true;
    }
    return false;
}

bool ArrayData::safeGetDictionary(int index,cocos2d::CCDictionary** pResult)
{
    CCDictionary* pValue=static_cast<CCDictionary*>(m_pData->objectAtIndex(index));
    if (pValue) {
        *pResult =pValue;
        return true;
    }
    return false;
}

bool ArrayData::safeGetArray(int index,cocos2d::CCArray** pResult)
{
    CCArray* pValue=static_cast<CCArray*>(m_pData->objectAtIndex(index));
    if (pValue) {
        *pResult =pValue;
        return true;
    }
    return false;
    
}

bool ArrayData::safeGetArrayData(int index,ArrayData** pResult)
{
    CCArray* pValue=static_cast<CCArray*>(m_pData->objectAtIndex(index));
    if (pValue) {
        ArrayData* pRet=new ArrayData();
        pRet->init(pValue);
        pRet->autorelease();
        *pResult=pRet;
        return true;
    }
    return false;
}

bool ArrayData::safeGetDictionaryData(int index,DictionaryData** pResult)
{
    CCDictionary* pValue=static_cast<CCDictionary*>(m_pData->objectAtIndex(index));
    if (pValue) {
        DictionaryData* pRet=new DictionaryData();
        pRet->init(pValue);
        pRet->autorelease();
        *pResult=pRet;
        return true;
    }
    return false;
}

NS_CC_YHGE_END