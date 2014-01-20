#ifndef YHGE_ISOMETRIC_ISOACTIVELAYER_H_
#define YHGE_ISOMETRIC_ISOACTIVELAYER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "../base/ISOObjectGroup.h"

NS_CC_YHGE_BEGIN

class ISOTileMap;

/**
 * 活动层。
 * 不能是TileLayer
 * 提供场景活动人物的层
 */
class ISOActiveLayer : public CCNode {

public:
	
	ISOActiveLayer();
    
	virtual ~ISOActiveLayer(void);
	
    virtual bool init();
    
    static ISOActiveLayer* create();
    
    /**
     * 初始化显示tiles
     */
    virtual void setupObjects();
    
    /**
     * 释放本层的内容
     */
    virtual void releaseLayer();
    
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

    /**
     * 获取属性名称
     */
    CCString *propertyNamed(const char *propertyName);
    

public:
    
    inline void setLayerName(const std::string& layerName)
    {
        m_layerName = layerName;
    }
    
    inline const std::string& getLayerName()
    {
        return m_layerName;
    }
    
    inline void setOffset(const CCPoint& offset)
    {
        m_offset = offset;
    }
    
    inline const CCPoint& getOffset()
    {
        return m_offset;
    }
    
    inline void setProperties(CCDictionary* properties)
    {
        CC_SAFE_RETAIN(properties);
        CC_SAFE_RELEASE(m_properties);
        m_properties = properties;
    }
    
    inline CCDictionary* getProperties()
    {
        return m_properties;
    }
    
    inline void setLayerOrientation(unsigned int layerOrientation)
    {
        m_layerOrientation = layerOrientation;
    }
    
    inline unsigned int getLayerOrientation()
    {
        return m_layerOrientation;
    }
    
    inline void setOpacity(unsigned char opacity)
    {
        m_opacity = opacity;
    }
    
    inline unsigned char getOpacity()
    {
        return m_opacity;
    }
    
    inline void setVertexZvalue(int vertexZvalue)
    {
        m_vertexZvalue = vertexZvalue;
    }
    
    inline int getVertexZvalue()
    {
        return m_vertexZvalue;
    }
    
    inline void setMap(ISOTileMap* map)
    {
        m_map = map;
    }
    
    inline ISOTileMap* getMap()
    {
        return m_map;
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
    /**
     * 层的名称
     */
    std::string m_layerName;
    
    /**
     * 地图的偏移量。屏幕坐标
     * 可能层的原点和地图的原点不在一起。
     */
    CCPoint m_offset;
    
    /**
     * 属性
     */
    CCDictionary* m_properties;
    
    /**
     * 地图类型，斜视角，直角，六角。
     * 这里直接使用斜视角。所以用不到，保留将来或许有用。
     */
    unsigned int m_layerOrientation;
    
    /**
     * 透明度。
     */
    unsigned char m_opacity;
    
    //! Only used when vertexZ is used
    int m_vertexZvalue;
    
    //对地图的引用。
    ISOTileMap* m_map;

    /**
     * 使用object group
     */
    ISOObjectGroup* m_objectGroup;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOACTIVELAYER_H_
