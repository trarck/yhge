#ifndef YHGE_ISOMETRIC_ISOCOMPONENTNODE_H_
#define YHGE_ISOMETRIC_ISOCOMPONENTNODE_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOComponentNode : public CCSprite{

public:
    
    ISOComponentNode();
    
    ~ISOComponentNode();
    
    bool init();
    
    void updateMapCoordinate(float mapX,float mapY);
    
	//void draw();

    inline void changeZOrder(int z){
        _zOrder=z;
    }
    
	inline void setColumn(int iColumn)
	{
		_iColumn = iColumn;
	};

	inline int getColumn()
	{
		return _iColumn;
	};

	inline void setRow(int iRow)
	{
		_iRow = iRow;
	};

	inline int getRow()
	{
		return _iRow;
	};
    
    inline void setMapX(float mapX)
    {
        _mapX = mapX;
    };
    
    inline float getMapX()
    {
        return _mapX;
    };
    
    inline void setMapY(float mapY)
    {
        _mapY = mapY;
    };
    
    inline float getMapY()
    {
        return _mapY;
    };
        
    inline void setMapCellX(int iMapCellX)
    {
        _iMapCellX = iMapCellX;
    };
    
    inline int getMapCellX()
    {
        return _iMapCellX;
    };
    
    inline void setMapCellY(int iMapCellY)
    {
        _iMapCellY = iMapCellY;
    };
    
    inline int getMapCellY()
    {
        return _iMapCellY;
    };

private:
	int _iColumn;
	int _iRow;
    float _mapX;
    float _mapY;
    
    int _iMapCellX;
    int _iMapCellY;
    
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOCOMPONENTNODE_H_
