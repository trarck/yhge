#include "ISOBatchDynamicComponent.h"
#include "ISOCoordinate.h"
#include "ISOTileLayer.h"
#include "ISOTile.h"
#include "ISOBatchDynamicTileLayer.h"


NS_CC_YHGE_BEGIN

//const CCSize testSize=CCSizeMake(256,160);

ISOBatchDynamicComponent::ISOBatchDynamicComponent()
:m_pBatchNode(NULL)
{
	
}

ISOBatchDynamicComponent::~ISOBatchDynamicComponent()
{
	CC_SAFE_RELEASE(m_pBatchNode);
}

bool ISOBatchDynamicComponent::init()
{
	return true;
}

void ISOBatchDynamicComponent::createComponents()
{
	int totalColumn=2*m_iComponentTileColumn;
	int totalRow=2*m_iComponentTileRow;
	unsigned int capacity=totalColumn*totalRow;
	m_pComponents=new CCArray(totalColumn*totalRow);

	CCLOG("createComponents start:%d,%d",totalColumn,totalRow);

	ISOBatchDynamicTileLayer* tileLayer=(ISOBatchDynamicTileLayer*)m_pTileLayer;
	
	CCTexture2D *texture = tileLayer->getTileset()->getTexture();
    CCAssert(texture, "Texture is null");

	m_pBatchNode=new CCSpriteBatchNode();

	if (!m_pBatchNode->initWithTexture(texture, capacity))
    {               
        CCAssert(texture, "m_pBatchNode->initWithTexture fail");
    }
    
	ISOComponentNode* node;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<m_iComponentTileColumn;i++){
			node=new ISOComponentNode();
            node->init();
			node->setColumn(i*2+(j&1));
			node->setRow(j);
			node->setTexture(texture);
			m_pComponents->addObject(node);
            m_pBatchNode->addChild(node);
			node->setBatchNode(m_pBatchNode);
			node->release();
		}
    }
	m_pTileLayer->addChild(m_pBatchNode);
}

void ISOBatchDynamicComponent::updateNode(ISOComponentNode* node,float mx,float my)
{
    CCPoint pos=ccp(mx,my);
    //更新位置属性
    node->updateMapCoordinate(mx, my);
       
    ISOTile* tile=m_pTileLayer->tileAt(pos);
    
    // if GID == 0, then no tile is present
    if (tile)
    {
        //更新位置
        node->setPosition(isoGameToView2F(mx, my));
        
		m_pBatchNode->reorderChild(node,m_pTileLayer->zOrderForPos(pos));
        
        //更新显示内容
        node->setVisible(true);

        node->setTextureRect(tile->getTextureRect());
		node->setDirty(true);
		node->updateTransform();
    }else{
        node->setVisible(false);
    }
    
}
NS_CC_YHGE_END
