
#include "Frame.h"

NS_CC_YHGE_BEGIN

bool Frame::init()
{
    return true;
}

bool Frame::init(CCTexture2D* texture,const CCRect& rect)
{
    
    setTexture(texture);
    m_rect=rect;
    
    m_size=rect.size;
    
    return true;
}

bool Frame::init(CCTexture2D* texture,const CCRect& rect,const CCSize & size,const CCPoint & offset)
{
    setTexture(texture);
    m_rect=rect;
    m_size=size;
    m_offset=offset;
    return true;
}

NS_CC_YHGE_END