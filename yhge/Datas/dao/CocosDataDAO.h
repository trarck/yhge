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
    
    inline Value getValue(const std::string& key)
    {
		return _data[key];
    }
    
    inline void setValue(const std::string& key,int value)
    {
		_data[key] = Value(value);
    }
    
    inline void setValue(const std::string& key,float value)
    {
		_data[key] = Value(value);
    }
    
    inline void setValue(const std::string& key,double value)
    {
		_data[key] = Value(value);
    }
    
    inline void setValue(const std::string& key,const std::string& value)
    {
		_data[key] = Value(value);
    }
    
    inline void setValue(const std::string& key,const ValueVector& value)
    {
		_data[key] = value;
    }

	inline void setValue(const std::string& key, const ValueMap& value)
	{
		_data[key] = value;
	}

protected:
	//union
	//{
	//	StringKeyDataMap* strKeyData;
	//	IntKeyDataMap* intKeyData;
	//} _data;

	ValueMap _data;
    
};

NS_CC_YHGE_DATA_END



#endif //YHGE_DATAS_DAO_COCOSDATADAO_H_
