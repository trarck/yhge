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

	typedef Vector<ISOLayer*> LayerVector;
	
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
	Value getProperty(const std::string& propertyName);
    
    /**
     * 通知layer，地图的显示位置改变。
     * 有可能是map的位置改变，有可能是game world改变引起
     */
    virtual void scrollLayer(const Vec2& pos);

	/**
	 * 显示地图的坐标线
	 */
	virtual void showCoordLine();
    
    /**
	 *检查某个单元是否可以通过
	 */
	virtual bool isWorkable(int x,int y);

public://==============属性===============//
	
	inline void semapSize(Size mapSize)
	{
		_mapSize = mapSize;
	}

	inline Size gemapSize()
	{
		return _mapSize;
	}

	inline void setileSize(const Size& tileSize)
	{
		_tileSize = tileSize;
	}

	inline const Size& getileSize()
	{
		return _tileSize;
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
    
    inline void setVisibleSize(const Size& visibleSize)
    {
        _visibleSize = visibleSize;
    }
    
    inline Size getOrignalVisibleSize()
    {
        return _visibleSize;
    }
    
    virtual Size getVisibleSize();
    
	inline void setProperties(const ValueMap& pProperties)
	{
		_properties = pProperties;
	}
    
	inline ValueMap& getProperties()
	{
		return _properties;
	}
    
	inline void setLayers(const LayerVector& layers)
    {
        _layers = layers;
    }
    
	inline LayerVector& getLayers()
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
	Size _mapSize;
    
    /**
     * 地图格子大小。
     */
    Size _tileSize;
    
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
    Size _visibleSize;
    
    /**
     * 属性列表
     */
    ValueMap _properties;

    //地图中所有的层
	LayerVector _layers;
    
    ISOLayer* _activeLayer;
    
};



NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOMAP_H_
