#ifndef YHGE_DATA_DAO_DAO_H_
#define YHGE_DATA_DAO_DAO_H_

#include "cocos2d.h"
#include <yhge/Datas/DataMacros.h>

NS_CC_YHGE_DATA_BEGIN


class DAO:public Ref
{
public:
    
	DAO();
    
	~DAO();
    
    bool init();

};

NS_CC_YHGE_DATA_END



#endif //YHGE_DATA_DAO_DAO_H_
