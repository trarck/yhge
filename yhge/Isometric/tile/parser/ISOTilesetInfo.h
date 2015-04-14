#ifndef YHGE_ISOMETRIC_ISOTILESETINFO_H_
#define YHGE_ISOMETRIC_ISOTILESETINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 块集合
 */
class ISOTilesetInfo : public Ref{

public:
    
    ISOTilesetInfo();
    
    ~ISOTilesetInfo();

    
public:
    
    inline const char* getName(){
        return _sName.c_str();
    }
    inline void setName(const char *name){
        _sName = name;
    }
    
    inline const char* getSourceFile(){
        return _sSourceFile.c_str();
    }
    inline void setSourceFile(const char *sourceFile){
        _sSourceFile = sourceFile;
    }
       
    inline void setFirstGid(unsigned int uFirstGid)
    {
        _uFirstGid = uFirstGid;
    }
    
    inline unsigned int getFirstGid()
    {
        return _uFirstGid;
    }
    
    inline void setTileSize(CCSize& tTileSize)
    {
        _tTileSize = tTileSize;
    }
    
    inline CCSize& getTileSize()
    {
        return _tTileSize;
    }
    
    inline void setSpacing(unsigned int uSpacing)
    {
        _uSpacing = uSpacing;
    }
    
    inline unsigned int getSpacing()
    {
        return _uSpacing;
    }
    
    inline void setMargin(unsigned int uMargin)
    {
        _uMargin = uMargin;
    }
    
    inline unsigned int getMargin()
    {
        return _uMargin;
    }
    
    inline void setTileOffset( CCPoint& tTileOffset)
    {
        _tTileOffset = tTileOffset;
    }
    
    inline  CCPoint& getTileOffset()
    {
        return _tTileOffset;
    }
    
    inline void setImageSource(const char * pImageSource)
    {
        _sImageSource = pImageSource;
    }
    
    inline const char * getImageSource()
    {
        return _sImageSource.c_str();
    }
    
    inline void setImageSize(CCSize& tImageSize)
    {
        _tImageSize = tImageSize;
    }
    
    inline CCSize& getImageSize()
    {
        return _tImageSize;
    }
    
    inline void setTiles(CCArray* pTiles)
    {
        CC_SAFE_RETAIN(pTiles);
        CC_SAFE_RELEASE(_pTiles);
        _pTiles = pTiles;
    }
    
    inline CCArray* getTiles()
    {
        return _pTiles;
    }
    
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

protected:
    /**
     * 集合名称
     */
    std::string     _sName;
    
    /**
     * 定义文件
     * 把tileset的定义放在单独的文件里
     */
    std::string     _sSourceFile;
    
    /**
     * 集合开始块的全局id
     */
    unsigned int    _uFirstGid;
    
    /**
     * 集合中每块的大小
     */
    CCSize          _tTileSize;
    
    /**
     * 块的内间距
     */
    unsigned int    _uSpacing;
    
    /**
     * 块的外间距
     */
    unsigned int    _uMargin;
    
    /**
     * 整个tile图片的偏移
     */
    CCPoint _tTileOffset;
    
    /**
     * 集合用到的图片
     * filename containing the tiles (should be spritesheet / texture atlas)
     */
    std::string        _sImageSource;
    
    /**
     * 集合用到的图片的大小
     * size in pixels of the image
     */
    CCSize            _tImageSize;
    
    /**
     * 所有小格子
     */
    CCArray* _pTiles;
    
    /**
     * 属性
     */
    CCDictionary* _pProperties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILESETINFO_H_
