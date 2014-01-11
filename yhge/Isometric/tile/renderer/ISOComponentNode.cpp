#include "ISOComponentNode.h"
#include <yhge/Isometric/ISOCoordinate.h>



NS_CC_YHGE_BEGIN

ISOComponentNode::ISOComponentNode()
:m_iColumn(0)
,m_iRow(0)
,m_iMapCellX(0)
,m_iMapCellY(0)
//,m_pTile(NULL)
{

}

ISOComponentNode::~ISOComponentNode()
{
//    CCLOG("ISOComponentNode destroy");
//    CC_SAFE_RELEASE(m_pTile);
}

bool ISOComponentNode::init()
{
    if(CCSprite::init()){
        return true;
    }
//    m_pTile=new CCSprite();
//    m_pTile->init();
    
    return false;
}

void ISOComponentNode::updateMapCoordinate(float mapX,float mapY)
{
    m_fMapX=mapX;
    m_fMapY=mapY;
////    CCPoint pos=isoGameToView2F(mapX, mapY);
////    CCLOG("updateMapCoordinate:%f,%f:%f,%f",mapX,mapY,pos.x,pos.y);
//    if(m_pTile)
//        m_pTile->setPosition(isoGameToView2F(mapX, mapY));
}

//void ISOComponentNode::draw()
//{
//	CCSprite::draw();
//	ccDrawColor4B(0,0,255,255);
//	ccDrawRect(ccp(0,0),ccp(m_obContentSize.width,m_obContentSize.height));
//}

NS_CC_YHGE_END
