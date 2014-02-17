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
        m_nZOrder=z;
    }
    
	inline void setColumn(int iColumn)
	{
		m_iColumn = iColumn;
	};

	inline int getColumn()
	{
		return m_iColumn;
	};

	inline void setRow(int iRow)
	{
		m_iRow = iRow;
	};

	inline int getRow()
	{
		return m_iRow;
	};
    
    inline void setMapX(float fMapX)
    {
        m_fMapX = fMapX;
    };
    
    inline float getMapX()
    {
        return m_fMapX;
    };
    
    inline void setMapY(float fMapY)
    {
        m_fMapY = fMapY;
    };
    
    inline float getMapY()
    {
        return m_fMapY;
    };
        
    inline void setMapCellX(int iMapCellX)
    {
        m_iMapCellX = iMapCellX;
    };
    
    inline int getMapCellX()
    {
        return m_iMapCellX;
    };
    
    inline void setMapCellY(int iMapCellY)
    {
        m_iMapCellY = iMapCellY;
    };
    
    inline int getMapCellY()
    {
        return m_iMapCellY;
    };

private:
	int m_iColumn;
	int m_iRow;
    float m_fMapX;
    float m_fMapY;
    
    int m_iMapCellX;
    int m_iMapCellY;
    
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOCOMPONENTNODE_H_
