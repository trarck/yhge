#ifndef YHGE_ISOMETRIC_ISOXMLPARSER_H_
#define YHGE_ISOMETRIC_ISOXMLPARSER_H_

#include "cocos2d.h"
#include "ISOMapInfo.h"
#include "ISOLayerInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

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
class ISOXMLParser : public Ref, public CCSAXDelegator
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
    
    inline const char* getCurrentString(){ return _sCurrentString.c_str(); }
    inline void setCurrentString(const char *currentString){ _sCurrentString = currentString; }
    inline const char* getTMXFileName(){ return _sTMXFileName.c_str(); }
    inline void setTMXFileName(const char *fileName){ _sTMXFileName = fileName; }
    
    virtual ISOMapInfo* getMapInfo();
    
    inline void setTranslateLayerData(bool bTranslateLayerData)
    {
        _bTranslateLayerData = bTranslateLayerData;
    }
    
    inline bool getTranslateLayerData()
    {
        return _bTranslateLayerData;
    }

    inline void setTranslateObjectCoord(bool translateObjectCoord)
    {
        _translateObjectCoord = translateObjectCoord;
    }
    
    inline bool isTranslateObjectCoord()
    {
        return _translateObjectCoord;
    }
    
protected:
    
    void internalInit(const char* tmxFileName, const char* resourcePath);
    
    //把地图坐标左上角为原点的转为左下角。
    void translateMapTiles(unsigned int * pTiles,ISOLayerInfo* layerInfo,unsigned int **out);
    
    //把tiled里的object坐标转成地图格子坐标
    Vec2 translateObjectCoord(const Vec2& pos);
    
	//把tiled里的object格式像素大小转成坐标大小
	Size translateObjectSize(const Size& size);

protected:

    //xml file related
    int _nCurrentElement;
    
    unsigned int _uCurrentGid;
    
    int _nLayerAttribs;
    
    bool _bStoringCharacters;


    //! tmx filename
    std::string _sTMXFileName;
    // tmx resource path
    std::string _sResources;
    //! current string
    std::string _sCurrentString;
    //! tile properties
//    CCDictionary* _pTileProperties;

    ISOMapInfo* _pMapInfo;	
    
    bool _bTranslateLayerData;
    
    bool _translateObjectCoord;
    
    //tile layer,object group出现在tmx中的顺序
    int _childIndex;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOXMLPARSER_H_
