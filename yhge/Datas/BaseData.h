#ifndef YHGE_DATAS_BASEDATA_H_
#define YHGE_DATAS_BASEDATA_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class BaseData:public CCObject
{
public:
    
	BaseData();
    
	~BaseData();
    
    inline bool init(){return true;}
    
    virtual void loadFromFile(const std::string& file){};
    
    virtual void loadFromContentString(const std::string& content){};
    
    virtual void loadFromUrl(const std::string& url){};
    
    virtual void unload(){};

};

NS_CC_YHGE_END



#endif //YHGE_DATAS_BASEDATA_H_
