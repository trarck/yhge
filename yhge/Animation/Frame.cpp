
#include "Frame.h"

NS_CC_YHGE_BEGIN

Frame::Frame()
//:_spriteFrame(NULL)
//,_haveTransform(false)
//,_transform(CCAffineTransformMakeIdentity())
//,_color(ccWHITE)
//,_opacity(255)
:_displayProperty(NULL)
{

}
    
Frame::~Frame()
{
    CC_SAFE_RELEASE_NULL(_displayProperty);
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