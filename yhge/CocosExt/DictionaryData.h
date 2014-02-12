//
//  Config.h
//  ProjectFB
//
//  Created by duanhouhai on 13-4-23.
//
//

#ifndef YHGE_COCOSEXT_DICTIONARYDATA_H_
#define YHGE_COCOSEXT_DICTIONARYDATA_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class ArrayData;

/**
 * 游戏配置
 * 从文件中取得
 */
class DictionaryData:public CCObject
{
public:
    
    DictionaryData();
    
    ~DictionaryData();
    
    bool init();
    
    bool init(CCDictionary* pData);
    
    /**
     * 从文件中加载
     */
    void loadFromFile(const char* configPath);
    
    /**
     * 从字符数串中加载
     */
    
    void loadFromString(const char* content);
    
    //void loadFromUrl(const char* configUrl);
    
    //不安全的获取数据内容
    int getInt(const char* sKey);
    
    unsigned int getUint(const char* sKey);
    
    float getFloat(const char* sKey);
    
    double getDouble(const char* sKey);
    
    bool getBool(const char* sKey);
    
    const char* getCString(const char* sKey);
    
    std::string getStdString(const char* sKey);
    
    CCDictionary* getDictionary(const char* sKey);
    
    CCArray* getArray(const char* sKey);
    
	DictionaryData* getDictionaryData(const char* sKey);
	
	ArrayData* getArrayData(const char* sKey);
    
    //安全的获取数据内容
    bool safeGetInt(const char* sKey,int* pResult);
    
    bool safeGetUint(const char* sKey,unsigned int* pResult);
    
    bool safeGetFloat(const char* sKey,float* pResult);
    
    bool safeGetDouble(const char* sKey,double* pResult);
    
    bool safeGetBool(const char* sKey,bool* pResult);
    
    bool safeGetStdString(const char* sKey,std::string& sResult);
    
    bool safeGetCString(const char* sKey,const char** pResult);
    
	bool safeGetCStringBytes(const char* sKey,char* buffer);
    
    bool safeGetDictionary(const char* sKey,CCDictionary** pResult);
    
    bool safeGetArray(const char* sKey,CCArray** pArray);
    
	bool safeGetDictionaryData(const char* sKey,DictionaryData** pResult);
    
	bool safeGetArrayData(const char* sKey,ArrayData** pResult);
	
    
    //=============使用int型的key=============//
    
    //不安全的获取数据内容
    int getInt(int iKey);
    
    unsigned int getUint(int iKey);
    
    float getFloat(int iKey);
    
    double getDouble(int iKey);
    
    bool getBool(int iKey);
    
    const char* getCString(int iKey);
    
    std::string getStdString(int iKey);
    
    CCDictionary* getDictionary(int iKey);
    
    CCArray* getArray(int iKey);
    
	DictionaryData* getDictionaryData(int iKey);
	
	ArrayData* getArrayData(int iKey);
    
    //安全的获取数据内容
    bool safeGetInt(int iKey,int* pResult);
    
    bool safeGetUint(int iKey,unsigned int* pResult);
    
    bool safeGetFloat(int iKey,float* pResult);
    
    bool safeGetDouble(int iKey,double* pResult);
    
    bool safeGetBool(int iKey,bool* pResult);
    
    bool safeGetStdString(int iKey,std::string& sResult);
    
    bool safeGetCString(int iKey,const char** pResult);
    
	bool safeGetCStringBytes(int iKey,char* buffer);
    
    bool safeGetDictionary(int iKey,CCDictionary** pResult);
    
    bool safeGetArray(int iKey,CCArray** pArray);
    
	bool safeGetDictionaryData(int iKey,DictionaryData** pResult);
    
	bool safeGetArrayData(int iKey,ArrayData** pResult);
    
    CCObject* getObjectByKeyIndex(int index);
    
    DictionaryData* getDictionaryDataByKeyIndex(int index);
    
    /**
     * 设置配置数据
     */
    inline void setData(CCDictionary* pData)
    {
        CC_SAFE_RETAIN(pData);
        CC_SAFE_RELEASE(m_pData);
        m_pData = pData;
    }
    
    /**
     * 获取配置数据
     */
    inline CCDictionary* getData()
    {
        return m_pData;
    }
    
protected:
    /**
     * 原始数据
     */
    CCDictionary* m_pData;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_DICTIONARYDATA_H_
