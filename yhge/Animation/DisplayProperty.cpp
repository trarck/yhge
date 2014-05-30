#include "DisplayProperty.h"

NS_CC_YHGE_BEGIN

DisplayProperty::DisplayProperty()
:m_spriteFrame(NULL)
,m_haveTransform(false)
,m_transform(CCAffineTransformMakeIdentity())
,m_color(ccWHITE)
,m_opacity(255)
{

}
    
DisplayProperty::~DisplayProperty()
{
    CC_SAFE_RELEASE_NULL(m_spriteFrame);
}

bool DisplayProperty::init()
{
    return true;
}

bool DisplayProperty::init(CCSpriteFrame* spriteFrame)
{
    setSpriteFrame(spriteFrame);    
    return true;
}

NS_CC_YHGE_END