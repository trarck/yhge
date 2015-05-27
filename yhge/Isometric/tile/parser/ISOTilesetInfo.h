﻿#ifndef YHGE_ISOMETRIC_ISOTILESETINFO_H_
#define YHGE_ISOMETRIC_ISOTILESETINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ISOTileInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 块集合
 */
class ISOTilesetInfo : public Ref{

public:

	typedef Vector<ISOTileInfo*> ISOTileInfoVector;
    
    ISOTilesetInfo();
    
    ~ISOTilesetInfo();
    
    inline const std::string& getName(){
        return _name;
    }
    inline void setName(const std::string& name){
        _name = name;
    }
    
    inline const std::string& getSourceFile(){
        return _sourceFile;
    }
    inline void setSourceFile(const std::string& sourceFile){
        _sourceFile = sourceFile;
    }
       
    inline void setFirstGid(unsigned int uFirstGid)
    {
        _uFirstGid = uFirstGid;
    }
    
    inline unsigned int getFirstGid()
    {
        return _uFirstGid;
    }
    
    inline void setTileSize(Size& tileSize)
    {
        _tileSize = tileSize;
    }
    
    inline Size& getTileSize()
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
    
    inline void setileOffset( Vec2& tileOffset)
    {
        _tileOffset = tileOffset;
    }
    
    inline  Vec2& getileOffset()
    {
        return _tileOffset;
    }
    
    inline void setImageSource(const std::string&  pImageSource)
    {
        _imageSource = pImageSource;
    }
    
    inline const std::string&  getImageSource()
    {
        return _imageSource.c_str();
    }
    
    inline void setImageSize(Size& imageSize)
    {
        _imageSize = imageSize;
    }
    
    inline Size& getImageSize()
    {
        return _imageSize;
    }
    
	inline void setTiles(const ISOTileInfoVector& tiles)
    {
        _tiles = tiles;
    }
    
	inline ISOTileInfoVector& getTiles()
    {
        return _tiles;
    }
    
	inline void setProperties(const ValueMap& properties)
    {
        _properties = properties;
    }
    
	inline ValueMap& getProperties()
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
    std::string     _sourceFile;
    
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
    Vec2 _tileOffset;
    
    /**
     * 集合用到的图片
     * filename containing the tiles (should be spritesheet / texture atlas)
     */
    std::string        _imageSource;
    
    /**
     * 集合用到的图片的大小
     * size in pixels of the image
     */
    Size            _imageSize;
    
    /**
     * 所有小格子
     */
	ISOTileInfoVector _tiles;
    
    /**
     * 属性
     */
	ValueMap _properties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILESETINFO_H_
