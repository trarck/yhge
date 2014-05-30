
#include "Frame.h"

NS_CC_YHGE_BEGIN

Frame::Frame()
:m_spriteFrame(NULL)
,m_haveTransform(false)
,m_transform(CCAffineTransformMakeIdentity())
,m_color(ccWHITE)
,m_opacity(255)
{

}
    
Frame::~Frame()
{
    CC_SAFE_RELEASE_NULL(m_spriteFrame);
}

bool Frame::init()
{
    return true;
}

//bool Frame::init(CCSpriteFrame* spriteFrame)
//{
//    setSpriteFrame(spriteFrame);    
//    return true;
//}

NS_CC_YHGE_END