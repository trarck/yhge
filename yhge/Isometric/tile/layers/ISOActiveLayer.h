#ifndef YHGE_ISOMETRIC_ISOACTIVELAYER_H_
#define YHGE_ISOMETRIC_ISOACTIVELAYER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Isometric/ISOLayer.h>
#include "../base/ISOObjectGroup.h"

NS_CC_YHGE_BEGIN

class ISOTileMap;

/**
 * 活动层。
 * 提供场景活动元素的层
 * 对于tiled创建的地图文件，可以是tile layer,也可以是object layer。
 */
class ISOActiveLayer : public ISOLayer {

public:
	
	ISOActiveLayer();
    
	virtual ~ISOActiveLayer(void);
	
    virtual bool init();
    
    static ISOActiveLayer* create();

    /**
     * 设置层
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
    virtual void scroll(const CCPoint& tOffset);
    
    /**
     * 取得zOrder值，处理遮挡使用.zOrder vertexZ二者使用一
     */
    int zOrderForPos(const CCPoint& pos);
    
    /**
     * 取得z值，处理遮挡使用
     */
    int vertexZForPos(const CCPoint& pos);
    
    virtual void setMap(ISOMap* pMap);

public:
 
    
    inline void setVertexZvalue(int vertexZvalue)
    {
        m_vertexZvalue = vertexZvalue;
    }
    
    inline int getVertexZvalue()
    {
        return m_vertexZvalue;
    }
    
    inline void setObjects(CCArray* objects)
    {
        CC_SAFE_RETAIN(objects);
        CC_SAFE_RELEASE(m_objects);
        m_objects = objects;
    }
    
    inline CCArray* getObjects()
    {
        return m_objects;
    }
    
protected:
    
    /**
     * 使用gid从tileset中取出一个图片显示
     */
    CCSprite* createObject(int gid,const CCPoint& position);
    
    /**
     * 处理扩展属性
     */
    virtual void parseInternalProperties();
    
protected:
    
    //! Only used when vertexZ is used
    int m_vertexZvalue;
    
    //对地图的引用。
    ISOTileMap* m_tileMap;
    
    /**
     * 所有对象
     */
    CCArray* m_objects;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOACTIVELAYER_H_
