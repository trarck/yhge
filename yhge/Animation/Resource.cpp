
#include "Resource.h"

NS_CC_YHGE_BEGIN

Resource::Resource()
:m_id(0)
,m_type(kNoneTexture)
,m_spriteFrame(NULL)
,m_texture(NULL)
{

}
    
Resource::~Resource()
{
    CC_SAFE_RELEASE_NULL(m_spriteFrame);
    CC_SAFE_RELEASE_NULL(m_texture);
}

bool Resource::init()
{
    return true;
}

CCSize Resource::getSize()
{
    CCSize size;
    switch (m_type) {
        case kPackTexture:
            size=m_spriteFrame->getOriginalSize();
            break;
        case kFileTexture:
            size=m_texture->getContentSize();
            break;
        default:
            size=CCSizeZero;
            break;
    }
    return size;
}


NS_CC_YHGE_END