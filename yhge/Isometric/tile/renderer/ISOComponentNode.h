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
        _nZOrder=z;
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
    
    inline void setMapX(float fMapX)
    {
        _fMapX = fMapX;
    };
    
    inline float getMapX()
    {
        return _fMapX;
    };
    
    inline void setMapY(float fMapY)
    {
        _fMapY = fMapY;
    };
    
    inline float getMapY()
    {
        return _fMapY;
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
    float _fMapX;
    float _fMapY;
    
    int _iMapCellX;
    int _iMapCellY;
    
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOCOMPONENTNODE_H_
