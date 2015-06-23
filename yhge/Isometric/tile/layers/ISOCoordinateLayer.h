#ifndef YHGE_ISOMETRIC_ISOCOORDINATELAYER_H_
#define YHGE_ISOMETRIC_ISOCOORDINATELAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOCoordinateLayer: public Layer
{
public:
	ISOCoordinateLayer();
	
	ISOCoordinateLayer(int mapWidth, int mapHeight);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(ISOCoordinateLayer);

	static ISOCoordinateLayer* create(int mapWidth, int mapHeight);
	
	virtual void show();

	void showCoordinate(bool isShow);

	virtual void setMapWidth(int mapWidth);
	virtual int getMapWidth();
	virtual void setMapHeight(int mapHeight);
	virtual int getMapHeight();
private:
	int _mapWidth;
	int _mapHeight;
	bool _isShow;

	DrawNode* _content;
};

NS_CC_YHGE_ISOMETRIC_END

#endif // YHGE_ISOMETRIC_ISOCOORDINATELAYER_H_
