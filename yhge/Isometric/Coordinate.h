#ifndef YHGE_ISOMETRIC_COORDINATE_H_
#define YHGE_ISOMETRIC_COORDINATE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

typedef struct {
	int x;
	int y;
} CCCell;

class Coordinate : public CCObject {

public:
    
    Coordinate();
    ~Coordinate(void);
    
	static Coordinate* sharedCoordinate();
	static Coordinate* create();
	static Coordinate* create(int width,int height);
	static Coordinate* create(int xUnit,int yUnit,int zUnit);

    bool init(){
		return true;
	}
   	bool init(int width,int height)
	{
		setTileSize(width ,height);
		return true;
	}

	bool init(int xUnit,int yUnit,int zUnit){
		setCoordinateUnit(xUnit ,yUnit ,zUnit);
		return true;
	}

	void setTileSize(int width ,int height);
	void setCoordinateUnit(int xUnit ,int yUnit ,int zUnit);
	void setCoordinateUnit(int xUnit ,int yUnit);

	CCPoint screenToMap(float x ,float y){
		x=x/m_tileWidth;
		y=y/m_tileHeight;
		return CCPointMake(x+y,y-x);
	}

	CCPoint screenToMap(const CCPoint& point){
		return screenToMap(point.x,point.y);
	}

	CCPoint screenToMapGrid(float x ,float y){
		CCPoint p=screenToMap(x,y);
		p.x=floor(p.x);
		p.y=floor(p.y);
		return p;
	}

	CCPoint screenToMapGrid(const CCPoint& point){
		return screenToMapGrid(point.x ,point.y);
	}

	CCCell screenToMapCell(float x ,float y){
		CCPoint p=screenToMap(x ,y);
		CCCell cell;
		cell.x=(int) p.x;
		cell.y=(int) p.y;
		return cell;
	}

	CCPoint mapToScreen(float x ,float y ,float z){
		double sx=x-y,sy=x+y;
		return CCPointMake(sx*m_xUnit,sy*m_yUnit-z*m_zUnit);
	}

	CCPoint mapToScreen(float x ,float y){
		//return mapToScreen(x ,y ,0);
		double sx=x-y,sy=x+y;
		return CCPointMake(sx*m_xUnit,sy*m_yUnit);
	}

	CCPoint mapToScreen(const CCPoint& point){
		return mapToScreen(point.x,point.y);
	}

	CCSize mapToScreenSize(int l ,int b ,int h);

	CCPoint mapToScreenAnchor(int l ,int b ,int h);

private:
	int m_xUnit;
	int m_yUnit;
	int m_zUnit;
	
	int m_tileWidth;
	int m_tileHeight;
};





NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_COORDINATE_H_
