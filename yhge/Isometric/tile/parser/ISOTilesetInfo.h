#ifndef YHGE_ISOMETRIC_ISOTILESETINFO_H_
#define YHGE_ISOMETRIC_ISOTILESETINFO_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * 块集合
 */
class ISOTilesetInfo : public CCObject{

public:
    
    ISOTilesetInfo();
    
    ~ISOTilesetInfo();

    
public:
    
    inline const char* getName(){
        return m_sName.c_str();
    }
    inline void setName(const char *name){
        m_sName = name;
    }
    
    inline const char* getSourceFile(){
        return m_sSourceFile.c_str();
    }
    inline void setSourceFile(const char *sourceFile){
        m_sSourceFile = sourceFile;
    }
       
    inline void setFirstGid(unsigned int uFirstGid)
    {
        m_uFirstGid = uFirstGid;
    }
    
    inline unsigned int getFirstGid()
    {
        return m_uFirstGid;
    }
    
    inline void setTileSize(CCSize& tTileSize)
    {
        m_tTileSize = tTileSize;
    }
    
    inline CCSize& getTileSize()
    {
        return m_tTileSize;
    }
    
    inline void setSpacing(unsigned int uSpacing)
    {
        m_uSpacing = uSpacing;
    }
    
    inline unsigned int getSpacing()
    {
        return m_uSpacing;
    }
    
    inline void setMargin(unsigned int uMargin)
    {
        m_uMargin = uMargin;
    }
    
    inline unsigned int getMargin()
    {
        return m_uMargin;
    }
    
    inline void setTileOffset( CCPoint& tTileOffset)
    {
        m_tTileOffset = tTileOffset;
    }
    
    inline  CCPoint& getTileOffset()
    {
        return m_tTileOffset;
    }
    
    inline void setImageSource(const char * pImageSource)
    {
        m_sImageSource = pImageSource;
    }
    
    inline const char * getImageSource()
    {
        return m_sImageSource.c_str();
    }
    
    inline void setImageSize(CCSize& tImageSize)
    {
        m_tImageSize = tImageSize;
    }
    
    inline CCSize& getImageSize()
    {
        return m_tImageSize;
    }
    
    inline void setTiles(CCArray* pTiles)
    {
        CC_SAFE_RETAIN(pTiles);
        CC_SAFE_RELEASE(m_pTiles);
        m_pTiles = pTiles;
    }
    
    inline CCArray* getTiles()
    {
        return m_pTiles;
    }
    
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

protected:
    /**
     * 集合名称
     */
    std::string     m_sName;
    
    /**
     * 定义文件
     * 把tileset的定义放在单独的文件里
     */
    std::string     m_sSourceFile;
    
    /**
     * 集合开始块的全局id
     */
    unsigned int    m_uFirstGid;
    
    /**
     * 集合中每块的大小
     */
    CCSize          m_tTileSize;
    
    /**
     * 块的内间距
     */
    unsigned int    m_uSpacing;
    
    /**
     * 块的外间距
     */
    unsigned int    m_uMargin;
    
    /**
     * 整个tile图片的偏移
     */
    CCPoint m_tTileOffset;
    
    /**
     * 集合用到的图片
     * filename containing the tiles (should be spritesheet / texture atlas)
     */
    std::string        m_sImageSource;
    
    /**
     * 集合用到的图片的大小
     * size in pixels of the image
     */
    CCSize            m_tImageSize;
    
    /**
     * 所有小格子
     */
    CCArray* m_pTiles;
    
    /**
     * 属性
     */
    CCDictionary* m_pProperties;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOTILESETINFO_H_
