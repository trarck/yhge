//
//  AstarNode.h
//  isometric
//
#ifndef YHGE_ISOMETRIC_ISOMAP_H_
#define YHGE_ISOMETRIC_ISOMAP_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class ISOLayer;

/**
 *
 */
class ISOMap : public CCNode{

public:
	
	ISOMap();
    
	~ISOMap();
    
    static ISOMap* createWithXMLFile(const char* xmlFile);
    
    static ISOMap* createWithXML(const char* xmlString,const char* resourcePath);
    
    static ISOMap* createWithJSONFile(const char* mapFile);
    
    static ISOMap* createWithJSON(const char* jsonString,const char* resourcePath);
	
    virtual bool init();
    
    virtual bool initWithXMLFile(const char* xmlFile);
    
    virtual bool initWithJSONFile(const char* jsonFile);
    
    virtual bool initWithXML(const char* xmlString,const char* resourcePath);
    
    virtual bool initWithJSON(const char* jsonString,const char* resourcePath);
    
    
    ISOLayer * layerNamed(const std::string& layerName);
    
    /**
     * 取得属性
     */
	CCString *propertyNamed(const std::string& propertyName);
    
    /**
     * 通知layer，地图的显示位置改变。
     * 有可能是map的位置改变，有可能是game world改变引起
     */
    virtual void scrollLayer(const CCPoint& pos);

	/**
	 * 显示地图的坐标线
	 */
	virtual void showCoordLine();
    
    /**
	 *检查某个单元是否可以通过
	 */
	virtual bool isWorkable(int x,int y);

public://==============属性===============//
	
	inline void setMapSize(CCSize tMapSize)
	{
		m_tMapSize = tMapSize;
	}

	inline CCSize getMapSize()
	{
		return m_tMapSize;
	}

	inline void setTileSize(const CCSize& tTileSize)
	{
		m_tTileSize = tTileSize;
	}

	inline const CCSize& getTileSize()
	{
		return m_tTileSize;
	}

	inline void setName(const char* pName)
	{
		m_pName = pName;
	}

	inline const std::string& getName()
	{
		return m_pName;
	}

	inline void setMapOrientation(int nMapOrientation)
	{
		m_nMapOrientation = nMapOrientation;
	}

	inline int getMapOrientation()
	{
		return m_nMapOrientation;
	}

	inline void setIdentifier(int nIdentifier)
	{
		m_nIdentifier=nIdentifier;
	}

	inline int getIdentifier()
	{
		return m_nIdentifier;
	}
    
    inline void setVisibleSize(const CCSize& visibleSize)
    {
        m_visibleSize = visibleSize;
    }
    
    inline CCSize getOrignalVisibleSize()
    {
        return m_visibleSize;
    }
    
    virtual CCSize getVisibleSize();
    
	inline void setProperties(CCDictionary* pProperties)
	{
		CC_SAFE_RETAIN(pProperties);
		CC_SAFE_RELEASE(m_pProperties);
		m_pProperties = pProperties;
	}
    
	inline CCDictionary* getProperties()
	{
		return m_pProperties;
	}
    
    inline void setLayers(CCArray* layers)
    {
        CC_SAFE_RETAIN(layers);
        CC_SAFE_RELEASE(m_layers);
        m_layers = layers;
    }
    
    inline CCArray* getLayers()
    {
        return m_layers;
    }
    
    virtual void setActiveLayer(ISOLayer* activeLayer);
    
    inline ISOLayer* getActiveLayer()
    {
        return m_activeLayer;
    }
    
protected:
    /**
     * 地图大小，格子数，单位为格子。
     */
	CCSize m_tMapSize;
    
    /**
     * 地图格子大小。
     */
    CCSize m_tTileSize;
    
    /**
     * 地图名称
     */
    std::string m_pName;
    
    /**
     * 地图编号
     */
    int m_nIdentifier;
    
    /**
     * 地图类型
     */
    int m_nMapOrientation;
    
    /**
     * 地图的可视区域
     */
    CCSize m_visibleSize;
    
    /**
     * 属性列表
     */
    CCDictionary* m_pProperties;

    //地图中所有的层
    CCArray* m_layers;
    
    ISOLayer* m_activeLayer;
    
};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOMAP_H_
