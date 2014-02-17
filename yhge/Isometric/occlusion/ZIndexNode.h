//
//  ZIndexNode.

#ifndef YHGE_ISOMETRIC_ZINDEXNODE_H_
#define YHGE_ISOMETRIC_ZINDEXNODE_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN


class ZIndexNode : public CCObject {

public:
    ZIndexNode();
    ~ZIndexNode();
    
    void setRect(const CCRect& rect);
    const CCRect& getRect();
    
    //弱引用
    void setEntity(CCObject* entity);
    CCObject* getEntity();
protected:
    CCObject* m_pEntity;
    CCRect m_tRect;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ZINDEXNODE_H_
