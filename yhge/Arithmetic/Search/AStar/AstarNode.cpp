//
//  AstarNode.m
//  isometric
//
//

#include "AstarNode.h"

NS_CC_YHGE_BEGIN

AstarNode::AstarNode()
:m_parent(NULL)
{
	
}

AstarNode::~AstarNode()
{
	CC_SAFE_RELEASE(m_parent);
}

bool AstarNode::init()
{

	m_x=0;
	m_y=0;
	m_g=0;
	m_h=0;
	m_f=0;

	return true;
}

bool AstarNode::init(int x ,int y ,int g ,int h)
{
	
	m_x=x;
	m_y=y;
	m_g=g;
	m_h=h;
	m_f=g+h;

	return true;
}

bool AstarNode::init(int x ,int y)
{
	return init(x,y,0,0);
}

void AstarNode::setX(int x)
{
    m_x = x;
}

int AstarNode::getX()
{
    return m_x;
}

void AstarNode::setY(int y)
{
    m_y = y;
}

int AstarNode::getY()
{
    return m_y;
}

void AstarNode::setG(int g)
{
    m_g = g;
}

int AstarNode::getG()
{
    return m_g;
}

void AstarNode::setH(int h)
{
    m_h = h;
}

int AstarNode::getH()
{
    return m_h;
}

void AstarNode::setF(int f)
{
    m_f = f;
}

int AstarNode::getF()
{
    return m_f;
}

void AstarNode::setParent(AstarNode* parent)
{
    CC_SAFE_RETAIN(parent);
    CC_SAFE_RELEASE(m_parent);
    m_parent = parent;
}

AstarNode* AstarNode::getParent()
{
    return m_parent;
}

NS_CC_YHGE_END
