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
    
    inline const std::string& getName(){
        return _name;
    }
    inline void setName(const std::string& name){
        _name = name;
    }
    
    inline const std::string& getSourceFile(){
        return _sSourceFile;
    }
    inline void setSourceFile(const std::string& sourceFile){
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
    
    inline void setileSize(Size& tileSize)
    {
        _tileSize = tileSize;
    }
    
    inline Size& getileSize()
    {
        return _tileSize;
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
    
    inline void setTileOffset( Vec2& tTileOffset)
    {
        _tTileOffset = tTileOffset;
    }
    
    inline  Vec2& getTileOffset()
    {
        return _tTileOffset;
    }
    
    inline void setImageSource(const std::string&  pImageSource)
    {
        _sImageSource = pImageSource;
    }
    
    inline const std::string&  getImageSource()
    {
        return _sImageSource.c_str();
    }
    
    inline void setImageSize(Size& tImageSize)
    {
        _tImageSize = tImageSize;
    }
    
    inline Size& getImageSize()
    {
        return _tImageSize;
    }
    
    inline void setTiles(CCArray* tiles)
    {
        CC_SAFE_RETAIN(tiles);
        CC_SAFE_RELEASE(_tiles);
        _tiles = tiles;
    }
    
    inline CCArray* getTiles()
    {
        return _tiles;
    }
    
    inline void setProperties(CCDictionary* pProperties)
    {
        CC_SAFE_RETAIN(pProperties);
        CC_SAFE_RELEASE(_properties);
        _properties = pProperties;
    }
    
    inline CCDictionary* getProperties()
    {
        return _properties;
    }

protected:
    /**
     * 集合名称
     */
    std::string     _name;
    
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
    Size          _tileSize;
    
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
    Vec2 _tTileOffset;
    
    /**
     * 集合用到的图片
     * filename containing the tiles (should be spritesheet / texture atlas)
     */
    std::string        _sImageSource;
    
    /**
     * 集合用到的图片的大小
     * size in pixels of the image
     */
    Size            _tImageSize;
    
    /**
     * 所有小格子
     */
    CCArray* _tiles;
    
    /**
     * 属性
     */
    CCDictionary* _properties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILESETINFO_H_
