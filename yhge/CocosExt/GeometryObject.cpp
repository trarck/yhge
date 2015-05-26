#include "GeometryObject.h"

NS_CC_YHGE_BEGIN

PointObject& PointObject::operator= (const PointObject& other)
{
     _point=other.getPoint();
    return *this;
}


SizeObject& SizeObject::operator= (const SizeObject& other)
{
    setSize(other.getSize());
    return *this;
}


RectObject& RectObject::operator= (const RectObject& other)
{
    setRect(other.getRect());
    return *this;
}


NS_CC_YHGE_END
