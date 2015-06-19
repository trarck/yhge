#include "ISOBatchDynamicComponent.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include <yhge/Isometric/tile/base/ISOTile.h>
#include "ISOTileLayer.h"
#include "ISOBatchDynamicTileLayer.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

//const Size testSize=CCSizeMake(256,160);

ISOBatchDynamicComponent::ISOBatchDynamicComponent()
:_batchNode(NULL)
{
	
}

ISOBatchDynamicComponent::~ISOBatchDynamicComponent()
{
	CC_SAFE_RELEASE(_batchNode);
}

bool ISOBatchDynamicComponent::init()
{
	return true;
}

void ISOBatchDynamicComponent::createComponents()
{
	int totalColumn=2*_iComponentTileColumn;
	int totalRow=2*_iComponentTileRow;
	unsigned int capacity=totalColumn*totalRow;
	_components=ISODynamicComponent::ComponentNodeVecotr(totalColumn*totalRow);

	CCLOG("createComponents start:%d,%d",totalColumn,totalRow);

	ISOBatchDynamicTileLayer* tileLayer=(ISOBatchDynamicTileLayer*)_tileLayer;
	
	Texture2D *texture = tileLayer->getTileset()->getTexture();
    CCAssert(texture, "Texture is null");

	_batchNode = SpriteBatchNode::createWithTexture(texture, capacity);
	//fuck new version private initXXX
	_batchNode->retain();
    
	ISOComponentNode* node;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<_iComponentTileColumn;i++){
			node = ISOComponentNode::createWithTexture(texture);// new ISOComponentNode();
            //node->initWithTexture(texture);
			node->setColumn(i*2+(j&1));
			node->setRow(j);
			node->setAnchorPoint(ccp(0.5f,0.0f));
			_components.pushBack(node);
            _batchNode->addChild(node);
			node->setBatchNode(_batchNode);
			//node->release();
		}
    }
	_tileLayer->addChild(_batchNode);
}

void ISOBatchDynamicComponent::updateNode(ISOComponentNode* node,float mx,float my)
{
    Vec2 pos=ccp(mx,my);
    //更新位置属性
    node->updateMapCoordinate(mx, my);
       
    ISOTile* tile=_tileLayer->tileAt(pos);
    
    // if GID == 0, then no tile is present
    if (tile)
    {
        //更新位置
        node->setPosition(YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(mx, my)));
        
		_batchNode->reorderChild(node,_tileLayer->zOrderForPos(pos));
        
        //更新显示内容
        node->setVisible(true);

        node->setTextureRect(tile->getTextureRect());
		node->setDirty(true);
		node->updateTransform();
    }else{
        node->setVisible(false);
    }
    
}
NS_CC_YHGE_ISOMETRIC_END
