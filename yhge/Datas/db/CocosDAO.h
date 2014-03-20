#ifndef YHGE_DATAS_DB_COCOSDAO_H_
#define YHGE_DATAS_DB_COCOSDAO_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class CocosDAO:public CCObject
{
public:
    
	CocosDAO();
    
	~CocosDAO();
    
    int fetchNumber(const std::string& querySql);
    
    CCArray* fetchAll(const std::string& querySql);
    
    CCDictionary* fetchOne(const std::string& querySql);
    
//    CCDictionary* load(const std::string& table,int value,const std::string& pk="id");

    int insert(const std::string& table,CCDictionary* data);
    
    int update(const std::string& table,CCDictionary* data);
    
    int replace(const std::string& table,CCDictionary* data);
    
    int remove(const std::string& table,CCDictionary* where);
    
protected:
    
	std::string formateToPrepare(CCDictionary* data);
    
private:
    
    

};

NS_CC_YHGE_END



#endif //YHGE_DATAS_DB_COCOSDAO_H_
