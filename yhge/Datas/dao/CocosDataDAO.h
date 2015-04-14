#ifndef YHGE_DATAS_DAO_COCOSDATADAO_H_
#define YHGE_DATAS_DAO_COCOSDATADAO_H_

#include "DAO.h"

NS_CC_YHGE_DATA_BEGIN

class CocosDataDAO:public DAO
{
public:
    
	CocosDataDAO();
    
	~CocosDataDAO();
    
    bool init();
    
    virtual void loadFromFile(const std::string& file);
    
    virtual void loadFromContentString(const std::string& content);
    
    virtual void loadFromUrl(const std::string& url);
    
    virtual void unload();
    
    inline CCDictionary* getValue(const std::string& key)
    {
        return static_cast<CCDictionary*>(_data->objectForKey(key));
    }
    
    inline void setValue(const std::string& key,int value)
    {
        _data->setObject(CCInteger::create(value), key);
    }
    
    inline void setValue(const std::string& key,float value)
    {
        _data->setObject(CCFloat::create(value), key);
    }
    
    inline void setValue(const std::string& key,double value)
    {
        _data->setObject(CCDouble::create(value), key);
    }
    
    inline void setValue(const std::string& key,const std::string& value)
    {
        _data->setObject(CCString::create(value), key);
    }
    
    inline void setValue(const std::string& key,CCArray* value)
    {
        _data->setObject(value, key);
    }
    
    inline void setValue(const std::string& key,CCDictionary* value)
    {
        _data->setObject(value, key);
    }
    
    
    inline CCDictionary* getValue(int key)
    {
        return static_cast<CCDictionary*>(_data->objectForKey(key));
    }
    
    inline void setValue(int key,int value)
    {
        _data->setObject(CCInteger::create(value), key);
    }
    
    inline void setValue(int key,float value)
    {
        _data->setObject(CCFloat::create(value), key);
    }
    
    inline void setValue(int key,double value)
    {
        _data->setObject(CCDouble::create(value), key);
    }
    
    inline void setValue(int key,const std::string& value)
    {
        _data->setObject(CCString::create(value), key);
    }
    
    inline void setValue(int key,CCArray* value)
    {
        _data->setObject(value, key);
    }
    
    inline void setValue(int key,CCDictionary* value)
    {
        _data->setObject(value, key);
    }

protected:
    
    CCDictionary* _data;
    
};

NS_CC_YHGE_DATA_END



#endif //YHGE_DATAS_DAO_COCOSDATADAO_H_
