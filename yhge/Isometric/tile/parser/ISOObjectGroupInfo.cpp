#include "ISOObjectGroupInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOObjectGroupInfo::ISOObjectGroupInfo()
:_name("")
,_color(ccWHITE)
,_opacity(255)
,_visible(true)
,_positionOffset(CCPointZero)
{

}

ISOObjectGroupInfo::~ISOObjectGroupInfo()
{
    CCLOG("ISOObjectGroupInfo destroy");
}

NS_CC_YHGE_ISOMETRIC_END
