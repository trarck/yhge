#ifndef YHGE_ISOMETRIC_ISOXMLPARSER_H_
#define YHGE_ISOMETRIC_ISOXMLPARSER_H_

#include "cocos2d.h"
#include "ISOMapInfo.h"
#include "ISOLayerInfo.h"

NS_CC_YHGE_BEGIN

/**
 * map标签
 */
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

/**
 * layer内容保存格式
 */
enum {
    ISOParseLayerAttribNone = 1 << 0,
    ISOParseLayerAttribBase64 = 1 << 1,
    ISOParseLayerAttribGzip = 1 << 2,
    ISOParseLayerAttribZlib = 1 << 3,
};


/**
 * 使用xml解析tmx
 */
class ISOXMLParser : public CCObject, public CCSAXDelegator
{

public:
    
    ISOXMLParser();
    
    ~ISOXMLParser();
    

    static ISOXMLParser * formatWithXMLFile(const char *tmxFile);
    /** creates a TMX Format with an XML string and a TMX resource path */
    static ISOXMLParser * formatWithXML(const char* tmxString, const char* resourcePath);
    /** initializes a TMX format with a  tmx file */
    bool initWithTMXFile(const char *tmxFile);
    /** initializes a TMX format with an XML string and a TMX resource path */
    bool initWithXML(const char* tmxString, const char* resourcePath);
    /** initializes parsing of an XML file, either a tmx (Map) file or tsx (Tileset) file */
    bool parseXMLFile(const char *xmlFilename);
    /* initializes parsing of an XML string, either a tmx (Map) string or tsx (Tileset) string */
    bool parseXMLString(const char *xmlString);
    

    
    // implement pure virtual methods of CCSAXDelegator
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
    inline const char* getCurrentString(){ return m_sCurrentString.c_str(); }
    inline void setCurrentString(const char *currentString){ m_sCurrentString = currentString; }
    inline const char* getTMXFileName(){ return m_sTMXFileName.c_str(); }
    inline void setTMXFileName(const char *fileName){ m_sTMXFileName = fileName; }
    
    virtual ISOMapInfo* getMapInfo();
    
    inline void setTranslateLayerData(bool bTranslateLayerData)
    {
        m_bTranslateLayerData = bTranslateLayerData;
    }
    
    inline bool getTranslateLayerData()
    {
        return m_bTranslateLayerData;
    }

    inline void setTranslateObjectCoord(bool translateObjectCoord)
    {
        m_translateObjectCoord = translateObjectCoord;
    }
    
    inline bool isTranslateObjectCoord()
    {
        return m_translateObjectCoord;
    }
    
protected:
    
    void internalInit(const char* tmxFileName, const char* resourcePath);
    
    //把地图坐标左上角为原点的转为左下角。
    void translateMapTiles(unsigned int * pTiles,ISOLayerInfo* layerInfo,unsigned int **out);
    
    //把tiled里的object坐标转成地图格子坐标
    CCPoint translateObjectCoord(const CCPoint& pos);
    
	//把tiled里的object格式像素大小转成坐标大小
	CCSize translateObjectSize(const CCSize& size);

protected:

    //xml file related
    int m_nCurrentElement;
    
    unsigned int m_uCurrentGid;
    
    int m_nLayerAttribs;
    
    bool m_bStoringCharacters;


    //! tmx filename
    std::string m_sTMXFileName;
    // tmx resource path
    std::string m_sResources;
    //! current string
    std::string m_sCurrentString;
    //! tile properties
//    CCDictionary* m_pTileProperties;

    ISOMapInfo* m_pMapInfo;	
    
    bool m_bTranslateLayerData;
    
    bool m_translateObjectCoord;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOXMLPARSER_H_
