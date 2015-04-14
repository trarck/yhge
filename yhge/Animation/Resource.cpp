
#include "Resource.h"

NS_CC_YHGE_BEGIN

Resource::Resource()
:_id(0)
,_type(kNoneTexture)
,_spriteFrame(NULL)
,_texture(NULL)
{

}
    
Resource::~Resource()
{
    CC_SAFE_RELEASE_NULL(_spriteFrame);
    CC_SAFE_RELEASE_NULL(_texture);
}

bool Resource::init()
{
    return true;
}

CCSize Resource::getSize()
{
    CCSize size;
    switch (_type) {
        case kPackTexture:
            size=_spriteFrame->getOriginalSize();
            break;
        case kFileTexture:
            size=_texture->getContentSize();
            break;
        default:
            size=CCSizeZero;
            break;
    }
    return size;
}


NS_CC_YHGE_END