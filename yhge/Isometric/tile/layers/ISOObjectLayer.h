#ifndef YHGE_ISOMETRIC_ISOOBJECTLAYER_H_
#define YHGE_ISOMETRIC_ISOOBJECTLAYER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Isometric/ISOLayer.h>
#include "../base/ISOObjectGroup.h"

NS_CC_YHGE_BEGIN

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
    virtual void scroll(const CCPoint& tOffset);
    virtual void scroll(float x,float y);
    
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

    inline void setObjectGroup(ISOObjectGroup* objectGroup)
    {
        CC_SAFE_RETAIN(objectGroup);
        CC_SAFE_RELEASE(m_objectGroup);
        m_objectGroup = objectGroup;
    }
    
    inline ISOObjectGroup* getObjectGroup()
    {
        return m_objectGroup;
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
     * 使用object group
     */
    ISOObjectGroup* m_objectGroup;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOOBJECTLAYER_H_
