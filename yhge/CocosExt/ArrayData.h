#ifndef YHGE_COCOSEXT_ARRAYDATA_H_
#define YHGE_COCOSEXT_ARRAYDATA_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class DictionaryData;
/**
 * 游戏配置
 * 从文件中取得
 */
class ArrayData:public CCObject
{
public:
    
    ArrayData();
    
    ~ArrayData();
    
    bool init();
    
    bool init(CCArray* pData);
    /**
     * 从文件中加载
     */
    void loadFromFile(const char* configPath);
    
    /**
     * 从字符数串中加载
     */
    
    void loadFromString(const char* content);
    
    //    void loadFromUrl(const char* configUrl);
    
    //不安全的获取数据内容
    int getInt(int index);

    unsigned int getUint(int index);

    float getFloat(int index);
    
    double getDouble(int index);
    
    bool getBool(int index);
    
    const char* getCString(int index);
    
    std::string getStdString(int index);
    
    CCDictionary* getDictionary(int index);
    
    CCArray* getArray(int index);
    
	ArrayData* getArrayData(int index);
	
	DictionaryData* getDictionaryData(int index);
    
    //安全的获取数据内容
    bool safeGetInt(int index,int* pResult);
    
    bool safeGetUint(int index,unsigned int* pResult);
    
    bool safeGetFloat(int index,float* pResult);
    
    bool safeGetDouble(int index,double* pResult);
    
    bool safeGetBool(int index,bool* pResult);
    
    bool safeGetStdString(int index,std::string& sResult);
    
    bool safeGetCString(int index,const char** pResult);
    
	bool safeGetCStringBytes(int index,char* buffer);
    
    bool safeGetDictionary(int index,CCDictionary** pResult);
    
    bool safeGetArray(int index,CCArray** pArray);
    
	bool safeGetArrayData(int index,ArrayData** pResult);
    
	bool safeGetDictionaryData(int index,DictionaryData** pResult);
	
    /**
     * 设置配置数据
     */
    
    inline void setData(CCArray* pData)
    {
        CC_SAFE_RETAIN(pData);
        CC_SAFE_RELEASE(m_pData);
        m_pData = pData;
    }
    
    /**
     * 获取配置数据
     */
    inline CCArray* getData()
    {
        return m_pData;
    }
    
protected:
    
    /**
     * 原始数据
     */
    CCArray* m_pData;
};

NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_ARRAYDATA_H_
