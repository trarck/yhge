//
//  ZIndexNode.

#ifndef YHGE_ISOMETRIC_ZINDEXNODE_H_
#define YHGE_ISOMETRIC_ZINDEXNODE_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN


class ZIndexNode : public Ref {

public:
    ZIndexNode();
    ~ZIndexNode();
    
    void serect(const CCRect& rect);
    const CCRect& gerect();
    
    //弱引用
    void setEntity(Ref* entity);
    Ref* getEntity();
protected:
    Ref* _entity;
    CCRect _rect;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ZINDEXNODE_H_
