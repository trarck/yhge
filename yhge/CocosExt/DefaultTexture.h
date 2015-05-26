#ifndef YHGE_COCOSEXT_CCSCOPEPTR_H_
#define YHGE_COCOSEXT_CCSCOPEPTR_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class DefaultTexture : public Ref
{
public:

    DefaultTexture();
    ~DefaultTexture();

    static DefaultTexture* getInstance();

	Texture2D* createDefaultTexture();

    void setTexture(Texture2D* texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }

    Texture2D* getTexture();

private:

    Texture2D* _texture;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCSCOPEPTR_H_
