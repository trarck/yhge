#ifndef YHGE_ISOMETRIC_ISOCOMPONENTNODE_H_
#define YHGE_ISOMETRIC_ISOCOMPONENTNODE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

class ISOComponentNode : public CCSprite{

public:
    
    ISOComponentNode();
    
    ~ISOComponentNode();
    
    bool init();
    
    void updateMapCoordinate(float mapX,float mapY);
    
    void changeZOrder(int z){
        m_nZOrder=z;
    }
    
	void setColumn(int iColumn)
	{
		m_iColumn = iColumn;
	};

	int getColumn()
	{
		return m_iColumn;
	};

	void setRow(int iRow)
	{
		m_iRow = iRow;
	};

	int getRow()
	{
		return m_iRow;
	};
    
    void setMapX(float fMapX)
    {
        m_fMapX = fMapX;
    };
    
    float getMapX()
    {
        return m_fMapX;
    };
    
    void setMapY(float fMapY)
    {
        m_fMapY = fMapY;
    };
    
    float getMapY()
    {
        return m_fMapY;
    };
        
    void setMapCellX(int iMapCellX)
    {
        m_iMapCellX = iMapCellX;
    };
    
    int getMapCellX()
    {
        return m_iMapCellX;
    };
    
    void setMapCellY(int iMapCellY)
    {
        m_iMapCellY = iMapCellY;
    };
    
    int getMapCellY()
    {
        return m_iMapCellY;
    };
    
    void setTile( CCSprite* pTile)
    {
        CC_SAFE_RETAIN(pTile);
        CC_SAFE_RELEASE(m_pTile);
        m_pTile = pTile;
    };
    
    CCSprite* getTile()
    {
        return m_pTile;
    };

private:
	int m_iColumn;
	int m_iRow;
    float m_fMapX;
    float m_fMapY;

    CCSprite* m_pTile;
    
    int m_iMapCellX;
    int m_iMapCellY;
    
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOCOMPONENTNODE_H_
