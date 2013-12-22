#include "ISOOptimizedTileLayer.h"
#include "ISOCoordinate.h"

NS_CC_YHGE_BEGIN



ISOOptimizedTileLayer::ISOOptimizedTileLayer()
:m_iLastStartX(0)
,m_iLastStartY(0)
{
	
}

ISOOptimizedTileLayer::~ISOOptimizedTileLayer()
{
//	CC_SAFE_RELEASE();
}

bool ISOOptimizedTileLayer::init()
{
    if(ISOTileLayer::init()){
        m_iLastStartX=-999999;
        m_iLastStartY=-999999;
        m_tScreenSize=CCSizeMake(480,320);//CCDirector::sharedDirector()->getWinSize();//CCSizeMake(480,320);
        return true;
    }
    return false;
}

void ISOOptimizedTileLayer::initOffset(const CCPoint& tOffset)
{
    ISOTileLayer::initOffset(tOffset);
	m_iLastStartX=m_iStartX;
	m_iLastStartY=m_iStartY;
}

void ISOOptimizedTileLayer::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}

/**
 * 检查是否需要由于位置的改变而更新显示内容。
 * 并记录新位置对应的地图坐标，为更新使用。
 */
bool ISOOptimizedTileLayer::beforeUpdateContent()
{
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//CCPoint startMapCoord=isoViewToGame2F(0,0);
	//only for test
	CCPoint startMapCoord=isoViewToGamePoint(m_tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
	return m_iStartX!=m_iLastStartX || m_iStartY!=m_iLastStartY;
}

void ISOOptimizedTileLayer::doUpdateContent()
{
    CCLOG("doVisit#########");
	
	int startX=m_iStartX,startY=m_iStartY;
    
	//移动的格子数.为了确保显示的完全，每个角相应移动一个格子。左右在一起就加2，同样上下在一起也要加2
	int columnCount=floor(m_tScreenSize.width/m_tMapTileSize.width)+2;
	//会有一行浪费掉的。所以要减去1.
	int rowCount=(floor(m_tScreenSize.height/m_tMapTileSize.height)+2)*2-1;
    
    int evenColumnCount=columnCount;
	int oddColumnCount=columnCount-1;
	//后移一步.由于是在左下角，则只需移动x轴
	startX-=1;
    
	int mx=0,my=0;
	for(int j=0;j<rowCount;j++){
	
		for(int i=0;i<columnCount;i++){
			mx=startX+i;
			my=startY-i;
			//CCLOG("visit:%f,%f",mx,my);
			//有了map坐标就可以显示内容。
			addTileAt(mx,my);
		}
		//if((j+1)&1){
		//	columnCount++;
		//	startY++;
		//}else{
		//	columnCount--;
		//	startX++;
		//}
		//这里可以使j+1，再调换true和false的body,就是正常逻辑
		if(j&1){
			//下个循环为偶
			columnCount=evenColumnCount;
			startY++;
		}else{
			//下个循环为奇
			columnCount=oddColumnCount;
            startX++;
		}
	}
}


bool ISOOptimizedTileLayer::isCellChange()
{
	
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//CCPoint startMapCoord=isoViewToGame2F(0,0);
	//only for test
	CCPoint startMapCoord=isoViewToGamePoint(m_tOffset);
	int startX=(int)startMapCoord.x,startY=(int)startMapCoord.y;
	//CCLOG("checkMoveable:%d,%d:%d,%d  %f,%f:%f,%f",startX,startY,(int)m_iLastStartX,(int)m_iLastStartY,startMapCoord.x,startMapCoord.y,m_iLastStartX,m_iLastStartY);
	return startX!=m_iLastStartX || startY!=m_iLastStartY;
}

void ISOOptimizedTileLayer::visitTileShowable()
{
    CCLOG("in visit#########");
	
	//屏幕的四个点。使用gl坐标系统，地图坐标x正方向右上，y正方向左上。初始点为屏幕左下角。也就是gl坐标的原点
	//CCPoint startMapCoord=isoViewToGame2F(0,0);
	//only for test
	CCPoint startMapCoord=isoViewToGamePoint(m_tOffset);
	int startX=(int)startMapCoord.x,startY=(int)startMapCoord.y;
	if(startX!=(int)m_iLastStartX || startY!=(int)m_iLastStartY){
		m_iLastStartX=startX;
		m_iLastStartY=startY;
		//移动的格子数.为了确保显示的完全，每个角相应移动一个格子。左右在一起就加2，同样上下在一起也要加2
		int columnCount=floor(m_tScreenSize.width/m_tMapTileSize.width)+2;
		//会有一行浪费掉的。所以要减去1.
		int rowCount=(floor(m_tScreenSize.height/m_tMapTileSize.height)+2)*2-1;
		int oggColumnCount=columnCount+1;
		//后移一步.由于是在左下角，则只需移动x轴
		startX-=1;
    
		CCLOG("state:column=%d,rowCount=%d,start=%f,%f:%f,%f",columnCount,rowCount,startMapCoord.x,startMapCoord.y,this->getPosition().x,this->getPosition().y);

		
		int mx=0,my=0;
		for(int j=0;j<rowCount;j++){
			//if(j>0){
			//	if(j&1){
			//		columnCount++;
			//		startY++;
			//	}else{
			//		columnCount--;
			//		startX++;
			//	}
			//}
			for(int i=0;i<columnCount;i++){
				mx=startX+i;
				my=startY-i;
				//CCLOG("visit:%f,%f",mx,my);
				//有了map坐标就可以显示内容。
				addTileAt(mx,my);
			}
			//if((j+1)&1){
			//	columnCount++;
			//	startY++;
			//}else{
			//	columnCount--;
			//	startX++;
			//}
			//这里可以使j+1，再调换true和false的body,就是正常逻辑
			if(j&1){
				//下个循环为偶
				columnCount--;
				startX++;
			}else{
				//下个循环为奇
				columnCount++;
				startY++;
			}
		}
	}
}

//ios game book 上的方法
void ISOOptimizedTileLayer::visitTileShowable2()
{
	//屏幕的四个点。目前按原点在左上角，需要转成gl坐标系。
	CCPoint screenLeftTop=isoViewToGame2F(0,0);
	CCPoint screenRightTop=isoViewToGame2F(m_tScreenSize.width,0);
	CCPoint screenLeftBottom=isoViewToGame2F(0,m_tScreenSize.height);
	CCPoint screenRightBottom=isoViewToGame2F(m_tScreenSize.width,m_tScreenSize.height);

	screenLeftTop.x-=1;
	screenRightBottom.x+=1;
	screenRightTop.y-=1;
	screenLeftBottom.y+=1;

	
	CCPoint rowStart=screenLeftTop;
	CCPoint rowEnd=screenRightTop;

	//由于是按对角移动，只需要x移轴
	
	int mx=0,my=0;
	float x=rowStart.x,y=rowStart.y;
	int rowCount=0;
	//在左下角之上
	while(rowStart.x<screenLeftBottom.x||rowStart.y<screenLeftBottom.y){
		while(x!=rowEnd.x && y!=rowEnd.y){
			mx=x;
			my=y;
            x+=1;
            y-=1;
		}
		if(++rowCount&1){
			rowStart.y+=1;
			rowEnd.x+=1;
		}else{
			rowStart.x+=1;
			rowEnd.y+=1;
		}
	}
}




void ISOOptimizedTileLayer::draw()
{
	
	ccDrawColor4B(255,0,0,255);
    ccDrawRect(m_tOffset,ccp(m_tOffset.x+m_tScreenSize.width,m_tOffset.y+m_tScreenSize.height));
}



void ISOOptimizedTileLayer::scroll(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	if(this->beforeUpdateContent()){
		m_iLastStartX=m_iStartX;
		m_iLastStartY=m_iStartY;
		//TODO 不删除所有tile,只修改改变的tile.
		this->removeAllChildrenWithCleanup(true);
		this->doUpdateContent();
	}
}

void ISOOptimizedTileLayer::scroll(float x,float y)
{
    this->scroll(ccp(x,y));
}

void ISOOptimizedTileLayer::setScreenSize(const CCSize& screenSize)
{
    m_tScreenSize=screenSize;
}

NS_CC_YHGE_END
