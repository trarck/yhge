#ifndef YHGE_ISOMETRIC_ISOXMLPARSER_H_
#define YHGE_ISOMETRIC_ISOXMLPARSER_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOTileMap;

enum {
    ISOLayerAttribNone = 1 << 0,
    ISOLayerAttribBase64 = 1 << 1,
    ISOLayerAttribGzip = 1 << 2,
    ISOLayerAttribZlib = 1 << 3,
};

enum {
    ISOPropertyNone,
    ISOPropertyMap,
    ISOPropertyTileset,
    ISOPropertyLayer,
    ISOPropertyObjectGroup,
    ISOPropertyObject,
    ISOPropertyTile,
    ISOPropertyImage
};

class ISOXMLReader : public CCObject, public CCSAXDelegator
{

public:
    
    ISOXMLReader();
    
    ~ISOXMLReader();
    

    static ISOXMLReader * formatWithXMLFile(ISOTileMap* map,const char *tmxFile);
    /** creates a TMX Format with an XML string and a TMX resource path */
    static ISOXMLReader * formatWithXML(ISOTileMap* map,const char* tmxString, const char* resourcePath);
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
    
    inline const char* getCurrentString(){ return m_currentString.c_str(); }
    inline void setCurrentString(const char *currentString){ m_currentString = currentString; }
    inline const char* getTMXFileName(){ return m_tMXFileName.c_str(); }
    inline void setTMXFileName(const char *fileName){ m_tMXFileName = fileName; }
    
    virtual ISOTileMap* getMap();
    virtual void setMap(ISOTileMap* map);
    
private:
    void internalInit(const char* tmxFileName, const char* resourcePath);
    
    int m_currentElement;
    
    unsigned int m_currentGid;
    
    int m_layerAttribs;
    
    bool m_storingCharacters;
    
protected:
    //! tmx filename
    std::string m_tMXFileName;
    // tmx resource path
    std::string m_resources;
    //! current string
    std::string m_currentString;
    //! tile properties
//    CCDictionary* m_tileProperties;

    ISOTileMap* m_map;	
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOXMLPARSER_H_
