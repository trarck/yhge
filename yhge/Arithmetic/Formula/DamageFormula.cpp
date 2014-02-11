//
//  DamageFormula.m
//  isometric
//
//

#include "DamageFormula.h"

NS_CC_YHGE_BEGIN

DamageFormula::DamageFormula()
:m_parent(NULL)
{
	
}

DamageFormula::~DamageFormula()
{
	CC_SAFE_RELEASE(m_parent);
}

bool DamageFormula::init()
{

	m_x=0;
	m_y=0;
	m_g=0;
	m_h=0;
	m_f=0;

	return true;
}

bool DamageFormula::init(int x ,int y ,int g ,int h)
{
	
	m_x=x;
	m_y=y;
	m_g=g;
	m_h=h;
	m_f=g+h;

	return true;
}

bool DamageFormula::init(int x ,int y)
{
	return init(x,y,0,0);
}

void DamageFormula::setX(int x)
{
    m_x = x;
}

int DamageFormula::getX()
{
    return m_x;
}

void DamageFormula::setY(int y)
{
    m_y = y;
}

int DamageFormula::getY()
{
    return m_y;
}

void DamageFormula::setG(int g)
{
    m_g = g;
}

int DamageFormula::getG()
{
    return m_g;
}

void DamageFormula::setH(int h)
{
    m_h = h;
}

int DamageFormula::getH()
{
    return m_h;
}

void DamageFormula::setF(int f)
{
    m_f = f;
}

int DamageFormula::getF()
{
    return m_f;
}

void DamageFormula::setParent(DamageFormula* parent)
{
    CC_SAFE_RETAIN(parent);
    CC_SAFE_RELEASE(m_parent);
    m_parent = parent;
}

DamageFormula* DamageFormula::getParent()
{
    return m_parent;
}

NS_CC_YHGE_END
