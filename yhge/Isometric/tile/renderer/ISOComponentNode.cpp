#include "ISOComponentNode.h"


NS_CC_YHGE_BEGIN

ISOComponentNode::ISOComponentNode()
:m_iColumn(0)
,m_iRow(0)
,m_iMapCellX(0)
,m_iMapCellY(0)
{

}

ISOComponentNode::~ISOComponentNode()
{
    //CCLOG("ISOComponentNode destroy");
}

bool ISOComponentNode::init()
{
    if(CCSprite::init()){
        return true;
    }
    
    return false;
}

void ISOComponentNode::updateMapCoordinate(float mapX,float mapY)
{
    m_fMapX=mapX;
    m_fMapY=mapY;
}

//void ISOComponentNode::draw()
//{
//	CCSprite::draw();
//	ccDrawColor4B(0,0,255,255);
//	ccDrawRect(ccp(0,0),ccp(m_obContentSize.width,m_obContentSize.height));
//}

NS_CC_YHGE_END
