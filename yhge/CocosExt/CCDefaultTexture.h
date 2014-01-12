#ifndef YHGE_COCOSEXT_CCSCOPEPTR_H_
#define YHGE_COCOSEXT_CCSCOPEPTR_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class CCDefaultTexture : public CCObject
{
public:

    CCDefaultTexture();
    ~CCDefaultTexture();

    static CCDefaultTexture* getInstance();

	CCTexture2D* createDefaultTexture();

    void setTexture(CCTexture2D* texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(m_texture);
        m_texture = texture;
    }

    CCTexture2D* getTexture();

private:

    CCTexture2D* m_texture;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCSCOPEPTR_H_
