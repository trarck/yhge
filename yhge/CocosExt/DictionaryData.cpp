#include "DictionaryData.h"
#include "ArrayData.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN



DictionaryData::DictionaryData()
:m_pData(NULL)
{
    
}

DictionaryData::~DictionaryData()
{
    CC_SAFE_RELEASE(m_pData);
}

bool DictionaryData::init()
{
    m_pData=new CCDictionary();
    
    return true;
}

bool DictionaryData::init(CCDictionary* pData)
{
    setData(pData);
    
    return true;
}

void DictionaryData::loadFromFile(const char* DictionaryDataPath)
{
    CCDictionary* pData=CCDictionary::createWithContentsOfFile(DictionaryDataPath);
    setData(pData);
}

void DictionaryData::loadFromString(const char *content)
{
    
}

int DictionaryData::getInt(const char* sKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    return pValue?pValue->intValue():0;
}

unsigned int DictionaryData::getUint(const char* sKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    return pValue?pValue->uintValue():0;
}

float DictionaryData::getFloat(const char* sKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    return pValue?pValue->floatValue():0.0f;
}

double DictionaryData::getDouble(const char* sKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    return pValue?pValue->doubleValue():0.0f;
}

bool DictionaryData::getBool(const char* sKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    return pValue?pValue->boolValue():false;
}

const char* DictionaryData::getCString(const char* sKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    return pValue?pValue->getCString():"";
}

std::string DictionaryData::getStdString(const char* sKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    return pValue?std::string(pValue->getCString()):"";
}

CCDictionary* DictionaryData::getDictionary(const char* sKey)
{
    return static_cast<CCDictionary*>(m_pData->objectForKey(sKey));
}

CCArray* DictionaryData::getArray(const char* sKey)
{
    return static_cast<CCArray*>(m_pData->objectForKey(sKey));
}


DictionaryData* DictionaryData::getDictionaryData(const char* sKey)
{
    CCDictionary* data=getDictionary(sKey);
    
    if (data) {
        DictionaryData* pRet=new DictionaryData();
        pRet->init(data);
        pRet->autorelease();
        return pRet;
    }
    return NULL;
}

ArrayData* DictionaryData::getArrayData(const char* sKey)
{
	CCArray* data=getArray(sKey);
    if (data) {
        ArrayData* pRet=new ArrayData();
        pRet->init(data);
        pRet->autorelease();
        return pRet;
    }
    return NULL;
}

bool DictionaryData::safeGetInt(const char* sKey,int* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    if (pValue) {
        *pResult=pValue->intValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetUint(const char* sKey,unsigned int* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    if (pValue) {
        *pResult=pValue->uintValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetFloat(const char* sKey,float* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    if (pValue) {
        *pResult=pValue->floatValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetDouble(const char* sKey,double* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    if (pValue) {
        *pResult=pValue->doubleValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetBool(const char* sKey,bool* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    if (pValue) {
        *pResult=pValue->boolValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetStdString(const char* sKey,std::string& sResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    if (pValue) {
        sResult=pValue->getCString();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetCString(const char* sKey,const char** pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    if (pValue) {
        *pResult=pValue->getCString();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetCStringBytes(const char* sKey,char* buffer)
{
	CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(sKey));
    if (pValue) {
        strcpy(buffer, pValue->getCString());
        return true;
    }
    return false;
}

bool DictionaryData::safeGetDictionary(const char* sKey,cocos2d::CCDictionary** pResult)
{
    CCDictionary* pValue=static_cast<CCDictionary*>(m_pData->objectForKey(sKey));
    if (pValue) {
        *pResult =pValue;
        return true;
    }
    return false;
}

bool DictionaryData::safeGetArray(const char* sKey,cocos2d::CCArray** pResult)
{
    CCArray* pValue=static_cast<CCArray*>(m_pData->objectForKey(sKey));
    if (pValue) {
        *pResult =pValue;
        return true;
    }
    return false;
    
}

bool DictionaryData::safeGetDictionaryData(const char* sKey,DictionaryData** pResult)
{
    CCDictionary* pValue=static_cast<CCDictionary*>(m_pData->objectForKey(sKey));
    if (pValue) {
        DictionaryData* pRet=new DictionaryData();
        pRet->init(pValue);
        pRet->autorelease();
        *pResult=pRet;
        return true;
    }
    return false;
}

bool DictionaryData::safeGetArrayData(const char* sKey,ArrayData** pResult)
{
    CCArray* pValue=static_cast<CCArray*>(m_pData->objectForKey(sKey));
    if (pValue) {
        ArrayData* pRet=new ArrayData();
        pRet->init(pValue);
        pRet->autorelease();
        *pResult=pRet;
        return true;
    }
    return false;
}

//=============使用int型的key=============//

int DictionaryData::getInt(int iKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    return pValue?pValue->intValue():0;
}

unsigned int DictionaryData::getUint(int iKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    return pValue?pValue->uintValue():0;
}

float DictionaryData::getFloat(int iKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    return pValue?pValue->floatValue():0.0f;
}

double DictionaryData::getDouble(int iKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    return pValue?pValue->doubleValue():0.0f;
}

bool DictionaryData::getBool(int iKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    return pValue?pValue->boolValue():false;
}

const char* DictionaryData::getCString(int iKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    return pValue?pValue->getCString():"";
}

std::string DictionaryData::getStdString(int iKey)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    return pValue?std::string(pValue->getCString()):"";
}

CCDictionary* DictionaryData::getDictionary(int iKey)
{
    return static_cast<CCDictionary*>(m_pData->objectForKey(iKey));
}

CCArray* DictionaryData::getArray(int iKey)
{
    return static_cast<CCArray*>(m_pData->objectForKey(iKey));
}


DictionaryData* DictionaryData::getDictionaryData(int iKey)
{
    
    CCDictionary* data=getDictionary(iKey);
    
    if (data) {
        DictionaryData* pRet=new DictionaryData();
        pRet->init(data);
        pRet->autorelease();
        return pRet;
    }
    return NULL;
}

ArrayData* DictionaryData::getArrayData(int iKey)
{
	
    CCArray* data=getArray(iKey);
    
    if (data) {
        ArrayData* pRet=new ArrayData();
        pRet->init(data);
        pRet->autorelease();
        return pRet;
    }
    return NULL;
}

bool DictionaryData::safeGetInt(int iKey,int* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    if (pValue) {
        *pResult=pValue->intValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetUint(int iKey,unsigned int* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    if (pValue) {
        *pResult=pValue->uintValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetFloat(int iKey,float* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    if (pValue) {
        *pResult=pValue->floatValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetDouble(int iKey,double* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    if (pValue) {
        *pResult=pValue->doubleValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetBool(int iKey,bool* pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    if (pValue) {
        *pResult=pValue->boolValue();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetStdString(int iKey,std::string& sResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    if (pValue) {
        sResult=pValue->getCString();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetCString(int iKey,const char** pResult)
{
    CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    if (pValue) {
        *pResult=pValue->getCString();
        return true;
    }
    return false;
}

bool DictionaryData::safeGetCStringBytes(int iKey,char* buffer)
{
	CCString* pValue=static_cast<CCString*>(m_pData->objectForKey(iKey));
    if (pValue) {
        strcpy(buffer, pValue->getCString());
        return true;
    }
    return false;
}

bool DictionaryData::safeGetDictionary(int iKey,cocos2d::CCDictionary** pResult)
{
    CCDictionary* pValue=static_cast<CCDictionary*>(m_pData->objectForKey(iKey));
    if (pValue) {
        *pResult =pValue;
        return true;
    }
    return false;
}

bool DictionaryData::safeGetArray(int iKey,cocos2d::CCArray** pResult)
{
    CCArray* pValue=static_cast<CCArray*>(m_pData->objectForKey(iKey));
    if (pValue) {
        *pResult =pValue;
        return true;
    }
    return false;
    
}

bool DictionaryData::safeGetDictionaryData(int iKey,DictionaryData** pResult)
{
    CCDictionary* pValue=static_cast<CCDictionary*>(m_pData->objectForKey(iKey));
    if (pValue) {
        DictionaryData* pRet=new DictionaryData();
        pRet->init(pValue);
        pRet->autorelease();
        *pResult=pRet;
        return true;
    }
    return false;
}

bool DictionaryData::safeGetArrayData(int iKey,ArrayData** pResult)
{
    CCArray* pValue=static_cast<CCArray*>(m_pData->objectForKey(iKey));
    if (pValue) {
        ArrayData* pRet=new ArrayData();
        pRet->init(pValue);
        pRet->autorelease();
        *pResult=pRet;
        return true;
    }
    return false;
}

CCObject* DictionaryData::getObjectByKeyIndex(int index)
{
    CCDictElement* elem=NULL;
    
    //    CCDICT_GET(data, elem, index);
    
    CCDictElement* pTmp= NULL;
    CCDictElement* head=m_pData->m_pElements;
    
    int idx=0;
#ifdef NO_DECLTYPE
    
    for((elem)=(head), (*(char**)(&(pTmp)))=(char*)((head)?(head)->hh.next:NULL);
        elem && idx++<(index); (elem)=(pTmp),(*(char**)(&(pTmp)))=(char*)((pTmp)?(pTmp)->hh.next:NULL))
    {
        
    }
#else
    for((elem)=(head),(pTmp)=DECLTYPE(elem)((head)?(head)->hh.next:NULL);
        elem && idx++<(index);
        (elem)=(pTmp),(pTmp)=DECLTYPE(elem)((pTmp)?(pTmp)->hh.next:NULL))
    {
        
    }
    
#endif
    
    if (elem) {
        return elem->getObject();
    }
    return NULL;
}

DictionaryData* DictionaryData::getDictionaryDataByKeyIndex(int index)
{
    CCDictElement* elem=NULL;
    
    //    CCDICT_GET(data, elem, index);
    
    CCDictElement* pTmp= NULL;
    CCDictElement* head=m_pData->m_pElements;
    int idx=0;
    
#ifdef NO_DECLTYPE

    for((elem)=(head), (*(char**)(&(pTmp)))=(char*)((head)?(head)->hh.next:NULL);
    elem && idx++<(index); (elem)=(pTmp),(*(char**)(&(pTmp)))=(char*)((pTmp)?(pTmp)->hh.next:NULL))
    {
        
    }
#else
    for((elem)=(head),(pTmp)=DECLTYPE(elem)((head)?(head)->hh.next:NULL);
        elem && idx++<(index);
        (elem)=(pTmp),(pTmp)=DECLTYPE(elem)((pTmp)?(pTmp)->hh.next:NULL))
    {
        
    }

#endif
    
    if (elem) {
        DictionaryData* dictData=new DictionaryData();
        dictData->init(static_cast<CCDictionary*>(elem->getObject()));
        dictData->autorelease();
        return dictData;
    }
    return NULL;
}

NS_CC_YHGE_END