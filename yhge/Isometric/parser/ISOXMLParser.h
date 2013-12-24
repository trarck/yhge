#ifndef YHGE_ISOMETRIC_ISOXMLPARSER_H_
#define YHGE_ISOMETRIC_ISOXMLPARSER_H_

#include "cocos2d.h"
#include "ISOMapInfo.h"
#include "ISOLayerInfo.h"

NS_CC_YHGE_BEGIN

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

    
private:
    
    void internalInit(const char* tmxFileName, const char* resourcePath);
    
    //把地图坐标左上角为原点的转为左下角。
    void translateMapTiles(unsigned int * pTiles,ISOLayerInfo* layerInfo,unsigned int **out);

    //xml file related
    int m_nCurrentElement;
    
    unsigned int m_uCurrentGid;
    
    int m_nLayerAttribs;
    
    bool m_bStoringCharacters;

protected:
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
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOXMLPARSER_H_
