#include "ISOComponentNode.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOComponentNode::ISOComponentNode()
:_iColumn(0)
,_iRow(0)
,_iMapCellX(0)
,_iMapCellY(0)
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
    _mapX=mapX;
    _mapY=mapY;
}

//void ISOComponentNode::draw()
//{
//	CCSprite::draw();
//	ccDrawColor4B(0,0,255,255);
//	ccDrawRect(ccp(0,0),ccp(_obContentSize.width,_obContentSize.height));
//}

ISOComponentNode* ISOComponentNode::createWithTexture(Texture2D* texture)
{
	ISOComponentNode *componentNode = new (std::nothrow) ISOComponentNode();
	componentNode->initWithTexture(texture);
	componentNode->autorelease();

	return componentNode;
}

NS_CC_YHGE_ISOMETRIC_END
