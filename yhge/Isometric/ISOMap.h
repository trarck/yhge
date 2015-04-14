//
//  AstarNode.h
//  isometric
//
#ifndef YHGE_ISOMETRIC_ISOMAP_H_
#define YHGE_ISOMETRIC_ISOMAP_H_

#include "cocos2d.h"
#include "IsometricMacros.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

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
		_tMapSize = tMapSize;
	}

	inline CCSize getMapSize()
	{
		return _tMapSize;
	}

	inline void setTileSize(const CCSize& tTileSize)
	{
		_tTileSize = tTileSize;
	}

	inline const CCSize& getTileSize()
	{
		return _tTileSize;
	}

	inline void setName(const char* pName)
	{
		_pName = pName;
	}

	inline const std::string& getName()
	{
		return _pName;
	}

	inline void setMapOrientation(int nMapOrientation)
	{
		_nMapOrientation = nMapOrientation;
	}

	inline int getMapOrientation()
	{
		return _nMapOrientation;
	}

	inline void setIdentifier(int nIdentifier)
	{
		_nIdentifier=nIdentifier;
	}

	inline int getIdentifier()
	{
		return _nIdentifier;
	}
    
    inline void setVisibleSize(const CCSize& visibleSize)
    {
        _visibleSize = visibleSize;
    }
    
    inline CCSize getOrignalVisibleSize()
    {
        return _visibleSize;
    }
    
    virtual CCSize getVisibleSize();
    
	inline void setProperties(CCDictionary* pProperties)
	{
		CC_SAFE_RETAIN(pProperties);
		CC_SAFE_RELEASE(_pProperties);
		_pProperties = pProperties;
	}
    
	inline CCDictionary* getProperties()
	{
		return _pProperties;
	}
    
    inline void setLayers(CCArray* layers)
    {
        CC_SAFE_RETAIN(layers);
        CC_SAFE_RELEASE(_layers);
        _layers = layers;
    }
    
    inline CCArray* getLayers()
    {
        return _layers;
    }
    
    virtual void setActiveLayer(ISOLayer* activeLayer);
    
    inline ISOLayer* getActiveLayer()
    {
        return _activeLayer;
    }
    
protected:
    /**
     * 地图大小，格子数，单位为格子。
     */
	CCSize _tMapSize;
    
    /**
     * 地图格子大小。
     */
    CCSize _tTileSize;
    
    /**
     * 地图名称
     */
    std::string _pName;
    
    /**
     * 地图编号
     */
    int _nIdentifier;
    
    /**
     * 地图类型
     */
    int _nMapOrientation;
    
    /**
     * 地图的可视区域
     */
    CCSize _visibleSize;
    
    /**
     * 属性列表
     */
    CCDictionary* _pProperties;

    //地图中所有的层
    CCArray* _layers;
    
    ISOLayer* _activeLayer;
    
};



NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOMAP_H_
