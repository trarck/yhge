#ifndef YHGE_ISOMETRIC_ISOMAPINFO_H_
#define YHGE_ISOMETRIC_ISOMAPINFO_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

enum {
    ISOParseLayerAttribNone = 1 << 0,
    ISOParseLayerAttribBase64 = 1 << 1,
    ISOParseLayerAttribGzip = 1 << 2,
    ISOParseLayerAttribZlib = 1 << 3,
};

enum {
    ISOParsePropertyNone,
    ISOParsePropertyMap,
    ISOParsePropertyTileset,
    ISOParsePropertyLayer,
    ISOParsePropertyObjectGroup,
    ISOParsePropertyObject,
    ISOParsePropertyTile,
    ISOParsePropertyImage
};


class ISOMapInfo : public CCObject{

public:
    
    ISOMapInfo();
    
    ~ISOMapInfo();
    
    virtual bool init();
    
    virtual void setOrientation(int nOrientation);
    virtual int getOrientation();
    
    virtual void setMapSize(const CCSize& tMapSize);
    virtual const CCSize& getMapSize();
    
    virtual void setTileSize(const CCSize& tTileSize);
    virtual const CCSize& getTileSize();
    
    virtual void setLayers(CCArray* pLayers);
    virtual CCArray* getLayers();
    
    virtual void setTilesets(CCArray* pTilesets);
    virtual CCArray* getTilesets();
    
    virtual void setObjectGroups(CCArray* pObjectGroups);
    virtual CCArray* getObjectGroups();
       
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
        
    inline void setBackgroundColor(ccColor3B& tBackgroundColor)
    {
        m_tBackgroundColor = tBackgroundColor;
    }
    
    inline ccColor3B& getBackgroundColor()
    {
        return m_tBackgroundColor;
    }
    
protected:
    int m_nOrientation;  
    CCSize m_tMapSize;
    CCSize m_tTileSize;
    ccColor3B m_tBackgroundColor;
    
    CCArray* m_pLayers;
    CCArray* m_pTilesets;
    CCArray* m_pObjectGroups;

    CCDictionary* m_pProperties;
   
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOMAPINFO_H_
