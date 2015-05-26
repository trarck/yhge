#ifndef YHGE_ISOMETRIC_ISOOBJECTLAYER_H_
#define YHGE_ISOMETRIC_ISOOBJECTLAYER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include <yhge/Isometric/ISOLayer.h>
#include "../base/ISOObjectGroup.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOTileMap;

/**
 * object layer。
 * 显示object group
 * 通常一个object group对应一个ObjectLayer
 * 目前只支持显示图块,失量图形暂不支持。
 * 按对象的y值做遮挡处理
 */

class ISOObjectLayer : public ISOLayer {

public:
	
	ISOObjectLayer();
    
	virtual ~ISOObjectLayer(void);
    
    static ISOObjectLayer* create();
    
    /**
     * 初始化显示
     */
    virtual void setupLayer();
    
    /**
     * 释放本层的内容
     */
    virtual void releaseLayer();
    
    /**
     * 初始化显示tiles
     */
    virtual void setupObjects();
    
    //移动
    virtual void scroll(const Vec2& tOffset);
    virtual void scroll(float x,float y);
    
    virtual void setMap(ISOMap* pMap);

public:

    inline void setObjectGroup(ISOObjectGroup* objectGroup)
    {
        CC_SAFE_RETAIN(objectGroup);
        CC_SAFE_RELEASE(_objectGroup);
        _objectGroup = objectGroup;
    }
    
    inline ISOObjectGroup* getObjectGroup()
    {
        return _objectGroup;
    }
    
protected:
    
    /**
     * 使用gid从tileset中取出一个图片显示
     */
    CCSprite* createObject(int gid,const Vec2& coord);
    
    /**
     * 处理扩展属性
     */
    virtual void parseInternalProperties();
    
protected:
    
    //对地图的引用。
    ISOTileMap* _tileMap;

    /**
     * 使用object group
     */
    ISOObjectGroup* _objectGroup;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOOBJECTLAYER_H_
