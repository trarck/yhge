#ifndef YHGE_DATAS_COCOSDATA_H_
#define YHGE_DATAS_COCOSDATA_H_

#include "BaseData.h"

NS_CC_YHGE_BEGIN

class CocosData:public BaseData
{
public:
    
	CocosData();
    
	~CocosData();
    
    bool init();
    
    virtual void loadFromFile(const std::string& file);
    
    virtual void loadFromContentString(const std::string& content);
    
    virtual void loadFromUrl(const std::string& url);
    
    virtual void unload();
    
    inline CCDictionary* getValue(const std::string& key)
    {
        return static_cast<CCDictionary*>(m_data->objectForKey(key));
    }
    
    void setValue(const std::string& key,int value)
    {
        m_data->setObject(CCInteger::create(value), key);
    }
    
    void setValue(const std::string& key,float value)
    {
        m_data->setObject(CCFloat::create(value), key);
    }
    
    void setValue(const std::string& key,double value)
    {
        m_data->setObject(CCDouble::create(value), key);
    }
    
    void setValue(const std::string& key,const std::string& value)
    {
        m_data->setObject(CCString::create(value), key);
    }
    
    inline void setValue(const std::string& key,CCArray* value)
    {
        m_data->setObject(value, key);
    }
    
    void setValue(const std::string& key,CCDictionary* value)
    {
        m_data->setObject(value, key);
    }

protected:
    
    CCDictionary* m_data;
    
};

NS_CC_YHGE_END



#endif //YHGE_DATAS_COCOSDATA_H_