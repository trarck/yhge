#include "ISODynamicComponent.h"
#include <yhge/CocosExt/CCDefaultTexture.h>
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../base/ISOTile.h"
#include "ISOTileLayer.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

static const int kComponentExtendCount=2;

//const Size testSize=CCSizeMake(256,160);

ISODynamicComponent::ISODynamicComponent()
:_components(NULL)
,_iStartX(0)
,_iStartY(0)
,_iLastStartX(-999999)
,_iLastStartY(-999999)
,_iComponentIndexX(0)
,_iComponentIndexY(0)
,_iComponentNodeExtendCount(kComponentExtendCount)
,_updateDelegator(NULL)
,_createDelegator(NULL)
,_offset(CCPointZero)
,_iComponentTileTotalRow(0)
,_iComponentTileTotalColumn(0)
,_iComponentTileColumn(0)
,_iComponentTileRow(0)
,_tileLayer(NULL)
{
	
}

ISODynamicComponent::~ISODynamicComponent()
{
	CC_SAFE_RELEASE_NULL(_components);
}

bool ISODynamicComponent::init()
{
	return true;
}

void ISODynamicComponent::createComponents()
{
	int totalColumn=2*_iComponentTileColumn;
	int totalRow=2*_iComponentTileRow;
	_components=new CCArray(totalColumn*totalRow);
    
	//使用数组在win32下第二次加载地图过程会变更很慢.
    //由于在sprite初始化的时候会设置默认texture.而这个texture的获取要调用CCFileUtils里的fullPathForFilename，
    //而fullPathForFilename最终会调用CCFileUtilsWin32的isFileExist，进而又会调用windows的api的GetFileAttributesA。
    //如果同时大量调用GetFileAttributesA，性能会下将。
    //因此最好不要同时大量初始化默认sprite
    CCTexture2D* defaultTexture=CCDefaultTexture::getInstance()->getTexture();
	ISOComponentNode* node=NULL;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<_iComponentTileColumn;i++){
            //CCLOG("cc:%d,%d",i,j);
			node=new ISOComponentNode();
            node->initWithTexture(defaultTexture);
			node->setColumn(i*2+(j&1));
			node->setRow(j);
			node->setAnchorPoint(ccp(0.5f,0.0f));
            _components->addObject(node);
            _tileLayer->addChild(node);
			node->release();
		}
		//if(j&1){
		//	//奇
		//	for(int i=0;i<_iComponentTileColumn;i++){
		//		node=new ISOComponentNode();
		//		node->setColumn(i*2+1);
		//		node->setRow(j);
		//		_components->addObject(node);
		//		node->release();
		//	}
		//}else{
		//	//偶
		//	for(int i=0;i<_iComponentTileColumn;i++){
		//		node=new ISOComponentNode();
		//		node->setColumn(i*2);
		//		node->setRow(j);
		//		_components->addObject(node);
		//		node->release();
		//	}
		//}
    }
}

void ISODynamicComponent::initComponents()
{
    int totalRow=2*_iComponentTileRow;
    
    
    int startX=_iStartX-_iComponentNodeExtendCount-1;
    int startY=_iStartY;
    CCLOG("initComponents start:%d,%d",startX,startY);
	ISOComponentNode* node;
    int row=0,col=0,index=0;
    int mx=0,my=0;
    for(int j=0;j<totalRow;j++){
		for(int i=0;i<_iComponentTileColumn;i++){
            col=(i*2+(j&1));
            row=j;
            index=j*_iComponentTileColumn+col/2;
            
			node=(ISOComponentNode*)_components->objectAtIndex(j*_iComponentTileColumn+col/2);
            mx=startX+i;
            my=startY-i;
            updateNode(node, mx, my);
//            CCLOG("index:%d,%d,%d:%d,%d",index,i,j,mx,my);
		}
        if(j&1){
			//下个循环为偶
			startY++;
		}else{
			//下个循环为奇
            startX++;
		}
    }
}

/**
 * 检查是否需要由于位置的改变而更新显示内容。
 * 并记录新位置对应的地图坐标，为更新使用。
 */
bool ISODynamicComponent::beforeUpdateContent()
{
	
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//Vec2 startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGame2F(0,0));
	//only for test
	Vec2 startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(_offset));
	_iStartX=(int)startMapCoord.x;
	_iStartY=(int)startMapCoord.y;
    //CCLOG("start:%d,%d %f,%f",_iStartX,_iStartY,_position.x,_position.y);
	return _iStartX!=_iLastStartX || _iStartY!=_iLastStartY;
}

void ISODynamicComponent::doUpdateComponents()
{
    
    int totalRow=2*_iComponentTileRow;
    int totalColumn=2*_iComponentTileColumn;
    
    int dx=_iStartX-_iLastStartX;
    int dy=_iStartY-_iLastStartY;
    
    int dirX=dx>0?1:dx<0?-1:0;
    int dirY=dy>0?1:dy<0?-1:0;
    
    int loopX=abs(dx);
    int loopY=abs(dy);
    
//	CCLOG("updateCompoents:%d,%d loops:%d,%d",dx,dy,loopX,loopY);
    int moveComponentIndexX=0,moveComponentIndexY=0;
    int index,row,col;
    
//    float mx=0,my=0;
//    ISOComponentNode* node=NULL;
    
    //注意正向，反向node移动的序列位置
    if(dx!=0){
        for(int k=0;k<loopX;k++){
            //横向移动 移动列
            if(dirX>0){
                moveComponentIndexX=_iComponentIndexX;
                _iComponentIndexX=(_iComponentIndexX+dirX)%totalColumn;
            }else if(dirX<0){
                _iComponentIndexX=(_iComponentIndexX+dirX+totalColumn)%totalColumn;
                moveComponentIndexX=_iComponentIndexX;
            }
            
            for(int j=0;j<_iComponentTileRow;j++){
                //如果行列的奇偶性一至，则从当前位置开始。如果互为奇奇偶，则要把行加1，变为奇或偶。
                row=(j*2+_iComponentIndexY+((_iComponentIndexY&1)^(moveComponentIndexX&1)))%totalRow;
                index=row*_iComponentTileColumn+moveComponentIndexX/2;
                //CCLOG("updateComponents x:%d,%d,%d",index,moveComponentIndexX,row);
                this->updateMapCoordinate(index, dirX*_iComponentTileColumn, -dirX*_iComponentTileColumn);

//                node=(ISOComponentNode*) _components->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirX*_iComponentTileColumn, my-dirX*_iComponentTileColumn);
            }
                    
            //纵向移动 移动行
            if(dirX>0){
                moveComponentIndexY=_iComponentIndexY;
                _iComponentIndexY=(_iComponentIndexY+dirX)%totalRow;
                
            }else if(dirX<0){
                _iComponentIndexY=(_iComponentIndexY+dirX+totalRow)%totalRow;
                moveComponentIndexY=_iComponentIndexY;
            }
            
            for(int i=0;i<_iComponentTileColumn;i++){
                //如果行列的奇偶性一至，则从当前位置开始。如果互为奇奇偶，则要把行加1，变为奇或偶。
                col=(i*2+_iComponentIndexX+((_iComponentIndexX & 1)^(moveComponentIndexY & 1)))%totalColumn;
                index=moveComponentIndexY*_iComponentTileColumn+col/2;
//                CCLOG("updateComponents y:%d,%d,%d",index,col,moveComponentIndexY);
                this->updateMapCoordinate(index, dirX*_iComponentTileRow, dirX*_iComponentTileRow);
//                node=(ISOComponentNode*) _components->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirX*_iComponentTileRow, my+dirX*_iComponentTileRow);
            }
        }
    }
    
	if(dy!=0){
        for(int k=0;k<loopY;k++){
            //横向移动
            if(dirY>0){
                _iComponentIndexX=(_iComponentIndexX-1+totalColumn)%totalColumn;
                moveComponentIndexX=_iComponentIndexX;
            }else if(dirY<0){
                moveComponentIndexX=_iComponentIndexX;
                _iComponentIndexX=(_iComponentIndexX+1)%totalColumn;
            }

            
            for(int j=0;j<_iComponentTileRow;j++){
                row=(j*2+_iComponentIndexY+((_iComponentIndexY&1)^(moveComponentIndexX&1)))%totalRow;
                index=row*_iComponentTileColumn+moveComponentIndexX/2;
//                CCLOG("updateComponents x:%d,%d,%d",index,moveComponentIndexX,row);
                this->updateMapCoordinate(index, -dirY*_iComponentTileColumn, dirY*_iComponentTileColumn);
//                node=(ISOComponentNode*) _components->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx-dirY*_iComponentTileColumn, my+dirY*_iComponentTileColumn);
            }
            
            if(dirY>0){
                moveComponentIndexY=_iComponentIndexY;
                _iComponentIndexY=(_iComponentIndexY+1)%totalRow;
            }else if(dirY<0){
                _iComponentIndexY=(_iComponentIndexY-1+totalRow)%totalRow;
                moveComponentIndexY=_iComponentIndexY;
            }
            //纵向移动
            
            for(int i=0;i<_iComponentTileColumn;i++){
                col=(i*2+_iComponentIndexX+((_iComponentIndexX & 1)^(moveComponentIndexY & 1)))%totalColumn;
                index=moveComponentIndexY*_iComponentTileColumn+col/2;
//                CCLOG("updateComponents y:%d,%d,%d",index,col,moveComponentIndexY);
                this->updateMapCoordinate(index,dirY*_iComponentTileRow, dirY*_iComponentTileRow);
//                node=(ISOComponentNode*) _components->objectAtIndex(index);
//                mx=node->getMapX();
//                my=node->getMapY();
//                node->updateMapCoordinate(mx+dirY*_iComponentTileRow, my+dirY*_iComponentTileRow);
            }
        }
    }
}

void ISODynamicComponent::updateMapCoordinate(unsigned int nodeIndex,float deltaMapX,float deltaMapY)
{
    //if(_updateDelegator) _updateDelegator->onUpdateComponentMapCoordinate(nodeIndex, deltaMapX, deltaMapY);
    
    updateNodeBy(nodeIndex,deltaMapX,deltaMapY);
}

void ISODynamicComponent::updateNodeBy(unsigned int nodeIndex,float deltaMapX,float deltaMapY)
{
	ISOComponentNode* node=(ISOComponentNode*) _components->objectAtIndex(nodeIndex);
    float mx=node->getMapX();
    float my=node->getMapY();
    float newMx=mx+deltaMapX;
    float newMy=my+deltaMapY;
    
//    CCLOG("ISODynamicComponent::updateMapCoordinate from:%f,%f to:%f,%f",mx,my,newMx,newMy);
    
    updateNode(node,newMx,newMy);
}

void ISODynamicComponent::updateNode(ISOComponentNode* node,float mx,float my)
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
        
        _tileLayer->reorderChild(node,_tileLayer->zOrderForPos(pos));
//        node->reorderChild(_tileLayer->zOrderForPos(pos));
        
        //更新显示内容
        node->setVisible(true);
        
        node->setTexture(tile->getTexture());
        node->setTextureRect(tile->getTextureRect());
    }else{
        node->setVisible(false);
    }
}

void ISODynamicComponent::calcComponentsCount()
{    
    _iComponentTileColumn+=_iComponentNodeExtendCount;
    _iComponentTileRow+=_iComponentNodeExtendCount;
    _iComponentTileTotalColumn=2*_iComponentTileColumn;
    _iComponentTileTotalRow=2*_iComponentTileRow;
	CCLOG("calcComponentsCount:%d,%d",_iComponentTileColumn,_iComponentTileRow);
}

void ISODynamicComponent::setucomponents()
{
	struct timeval start;
	struct timeval end;

	gettimeofday(&start,0);

    this->calcComponentsCount();

	gettimeofday(&end,NULL);

	CCLOG("setucomponents1:%ld",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);

	gettimeofday(&start,0);

    this->createComponents();
	
	gettimeofday(&end,NULL);

	CCLOG("setucomponents2:%ld",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);

	gettimeofday(&start,0);

    this->initComponents();

	gettimeofday(&end,NULL);

	CCLOG("setucomponents3:%ld",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
}


void ISODynamicComponent::setucomponents(const Vec2& position)
{
    this->inioffset(position);
    setucomponents();
}


CCArray* ISODynamicComponent::getComponents(){
    return _components;
}

void ISODynamicComponent::setComponentTileColumn(int iComponentTileColumn)
{
    _iComponentTileColumn = iComponentTileColumn;
}

int ISODynamicComponent::getComponentTileColumn()
{
    return _iComponentTileColumn;
}

void ISODynamicComponent::setComponentTileRow(int iComponentTileRow)
{
    _iComponentTileRow = iComponentTileRow;
}

int ISODynamicComponent::getComponentTileRow()
{
    return _iComponentTileRow;
}

void ISODynamicComponent::setComponentTileExtendCount(int iComponentNodeExtendCount)
{
    _iComponentNodeExtendCount = iComponentNodeExtendCount;
}

int ISODynamicComponent::getComponentTileExtendCount()
{
    return _iComponentNodeExtendCount;
}

void ISODynamicComponent::inioffset(const Vec2& offset)
{
    this->setOffset(offset);
	Vec2 startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(offset));
	_iStartX=(int)startMapCoord.x;
	_iStartY=(int)startMapCoord.y;
	_iLastStartX=_iStartX;
	_iLastStartY=_iStartY;
}

void ISODynamicComponent::inioffset(float x,float y)
{
	this->inioffset(ccp(x,y));
}

void ISODynamicComponent::scroll(const Vec2& offset)
{
    this->setOffset(offset);
	if(this->beforeUpdateContent()){
		//TODO 不删除所有tile,只修改改变的tile.
		//this->removeAllChildrenWithCleanup(true);
		//this->doUpdateContent();
		this->doUpdateComponents();
        _iLastStartX=_iStartX;
		_iLastStartY=_iStartY;

	}
}

void ISODynamicComponent::scroll(float x,float y)
{
    this->scroll(ccp(x,y));
}



void ISODynamicComponent::setOffset(const Vec2& offset)
{
    _offset = offset;
}

void ISODynamicComponent::setOffset(float x,float y)
{
    _offset.x=x;
	_offset.y=y;
}

Vec2 ISODynamicComponent::getOffset()
{
    return _offset;
}

void ISODynamicComponent::setUpdateDelegator(ISODynamicComponentUpdateDelegator* updateDelegator)
{
    _updateDelegator=updateDelegator;
}

void ISODynamicComponent::setCreateDelegator(ISODynamicComponentCreateDelegator* createDelegator)
{
    _createDelegator=createDelegator;
}

void ISODynamicComponent::setTileLayer(ISOTileLayer* tileLayer)
{
    _tileLayer = tileLayer;
}

ISOTileLayer* ISODynamicComponent::getTileLayer()
{
    return _tileLayer;
}

NS_CC_YHGE_ISOMETRIC_END
