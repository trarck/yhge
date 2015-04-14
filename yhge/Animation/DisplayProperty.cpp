#include "DisplayProperty.h"

NS_CC_YHGE_BEGIN

DisplayProperty::DisplayProperty()
:_spriteFrame(NULL)
,_haveCharacter(false)
,_haveTransform(false)
,_transform(CCAffineTransformMakeIdentity())
,_haveColor(false)
,_color(ccWHITE)
,_haveOpacity(false)
,_opacity(255)
,_haveZOrder(false)
,_zOrder(0)
{
    
}
    
DisplayProperty::~DisplayProperty()
{
    CC_SAFE_RELEASE_NULL(_spriteFrame);
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