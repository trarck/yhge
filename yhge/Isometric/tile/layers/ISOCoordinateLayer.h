#ifndef YHGE_ISOMETRIC_ISOCOORDINATELAYER_H_
#define YHGE_ISOMETRIC_ISOCOORDINATELAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOCoordinateLayer: public CCLayer
{
public:
	ISOCoordinateLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(ISOCoordinateLayer);
	
	virtual void draw();

	void showCoordinate(bool isShow);

	virtual void setMapWidth(int iMapWidth);
	virtual int getMapWidth();
	virtual void setMapHeight(int iMapHeight);
	virtual int getMapHeight();
private:
	int _iMapWidth;
	int _iMapHeight;
	bool _isShow;
};

NS_CC_YHGE_ISOMETRIC_END

#endif // YHGE_ISOMETRIC_ISOCOORDINATELAYER_H_
