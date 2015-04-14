//
//  AstarNode.m
//  isometric
//
//

#include "AstarNode.h"

NS_CC_YHGE_BEGIN

AstarNode::AstarNode()
:_parent(NULL)
{
	
}

AstarNode::~AstarNode()
{
	CC_SAFE_RELEASE(_parent);
}

bool AstarNode::init()
{

	_x=0;
	_y=0;
	_g=0;
	_h=0;
	_f=0;

	return true;
}

bool AstarNode::init(int x ,int y ,int g ,int h)
{
	
	_x=x;
	_y=y;
	_g=g;
	_h=h;
	_f=g+h;

	return true;
}

bool AstarNode::init(int x ,int y)
{
	return init(x,y,0,0);
}

void AstarNode::setX(int x)
{
    _x = x;
}

int AstarNode::getX()
{
    return _x;
}

void AstarNode::setY(int y)
{
    _y = y;
}

int AstarNode::getY()
{
    return _y;
}

void AstarNode::setG(int g)
{
    _g = g;
}

int AstarNode::getG()
{
    return _g;
}

void AstarNode::setH(int h)
{
    _h = h;
}

int AstarNode::getH()
{
    return _h;
}

void AstarNode::setF(int f)
{
    _f = f;
}

int AstarNode::getF()
{
    return _f;
}

void AstarNode::setParent(AstarNode* parent)
{
    CC_SAFE_RETAIN(parent);
    CC_SAFE_RELEASE(_parent);
    _parent = parent;
}

AstarNode* AstarNode::getParent()
{
    return _parent;
}

NS_CC_YHGE_END
