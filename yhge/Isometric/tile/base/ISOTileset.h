#ifndef YHGE_ISOMETRIC_ISOTILESET_H_
#define YHGE_ISOMETRIC_ISOTILESET_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ISOTile.h"

NS_CC_YHGE_ISOMETRIC_BEGIN


/**
 * tile的二种表示方式
 *    1.整张图片。每个tile的id按照从左到右，从下到下增加。静态的物体。
 *    2.分开的图片。可以是精灵动画。比较灵活，占用一定内存。
 *    3.整张不等大图片(sprite sheet).主要用于object。
 *     .前二种的混合。没有实际意义，会使得tileset变的复杂。这里不支持//由于tileset只支持一个imagesouce,所以imagesouce的id先于,tile的定义。如果tile定义的id包含在imagesouce里，则是定义imagesouce的属性。注意先后顺序。
 * TODO:
 *    1.支持sprite sheet.即不规则tile.
 *      id到名称的映射表，一个描述sprite sheet文件。
 */
class ISOTileset : public Ref{

public:
	typedef Vector<ISOTile*> ISOTileVector;
    
    ISOTileset();
    
    ~ISOTileset();
    
    bool init();

    bool isExternal() const { return !_fileName.empty(); }
    
    int tileCount() const { return _tiles.size(); }
    
    /**
     * 删除image tile
     */
//    virtual void cleanImageSourceTiles();
    
    virtual void loadFromImageSource();
    
    void appendTile(const char* imageName);
    
    void appendTile(Texture2D* texture);
    
    void setTile(unsigned int id,const char* imageName);
    
    void setTile(unsigned int id,Texture2D* texture);
    
    void addTile(unsigned int id,const char* imageName);
    
    void addTile(unsigned int id,Texture2D* texture);
    
    void addTile(ISOTile* tile);
    
    
    /**
     * 内置索引id
     */
    Rect rectForId(unsigned int id);
    
    Sprite* tileSpriteForId(unsigned int id);
    
    ISOTile* tileForId(unsigned int id);
    
    /**
     * 是否包含某个id
     */
    bool contains(unsigned int gid);
    
    Rect rectForGid(unsigned int gid);
    
    Sprite* tileSpriteForGid(unsigned int gid);
    
    ISOTile* tileForGid(unsigned int gid);
    
    unsigned int lastGid();
    
    int columnCountForWidth(float width);
    
    int rowCountForHeight(float height);    
    
public:
    
    inline const char* getName(){ return _name.c_str(); }
    inline void setName(const char *name){ _name = name; }
    
	inline void setFileName(const char* pFileName)
	{
		_fileName = pFileName;
	}

	inline std::string& getFileName()
	{
		return _fileName;
	}

	inline void setImageSource(const char* pImageSource)
	{
		_imageSource = pImageSource;
	}

	inline std::string& getImageSource()
	{
		return _imageSource;
	}

	inline void setTileWidth(int tileWidth)
	{
		_tileWidth = tileWidth;
	}

	inline int getTileWidth()
	{
		return _tileWidth;
	}

	inline void setTileHeight(int tileHeight)
	{
		_tileHeight = tileHeight;
	}

	inline int getTileHeight()
	{
		return _tileHeight;
	}
    
	inline virtual void setTileSize(Size& tTileSize){
        _tileWidth=(int)tTileSize.width;
        _tileHeight=(int)tTileSize.height;
    }
    
	inline virtual Size getTileSize(){
        return Size(_tileWidth, _tileHeight);
    }

	inline void setTileSpacing(int tileSpacing)
	{
		_tileSpacing = tileSpacing;
	}

	inline int getTileSpacing()
	{
		return _tileSpacing;
	}

	inline void setMargin(int margin)
	{
		_margin = margin;
	}

	inline int getMargin()
	{
		return _margin;
	}

	inline void setTileOffset(Vec2 tileOffset)
	{
		_tileOffset = tileOffset;
	}

	inline Vec2 getileOffset()
	{
		return _tileOffset;
	}

	inline void setImageSize(Size& imageSize)
	{
		_imageSize = imageSize;
	}

	inline Size& getImageSize()
	{
		return _imageSize;
	}

	//inline void setImageWidth(int imageWidth)
	//{
	//    _imageWidth = imageWidth;
	//}
	//
	//inline int getImageWidth()
	//{
	//    return _imageWidth;
	//}
	//
	//inline void setImageHeight(int imageHeight)
	//{
	//    _imageHeight = imageHeight;
	//}
	//
	//inline int getImageHeight()
	//{
	//    return _imageHeight;
	//}

	inline void setColumnCount(int columnCount)
	{
		_columnCount = columnCount;
	}

	inline int getColumnCount()
	{
		return _columnCount;
	}

	inline void setTiles(const ISOTileVector& tiles)
	{
		_tiles = tiles;
	}

	inline ISOTileVector& getTiles()
	{
		return _tiles;
	}

	inline void setFirstGid(unsigned int firstGid)
	{
		_firstGid = firstGid;
	}

	inline unsigned int getFirstGid()
	{
		return _firstGid;
	}

	inline unsigned int getLastGid()
	{
		return this->_lastGid;
	}

	inline void setLastGid(unsigned int gid)
	{
		this->_lastGid = gid;
	}

	inline void setTileProperties(const ValueMap& tileProperties)
	{
		_tileProperties = tileProperties;
	}

	inline ValueMap& getTileProperties()
	{
		return _tileProperties;
	}

	inline void setProperties(const ValueMap& pProperties)
	{
		_properties = pProperties;
	}

	inline ValueMap& getProperties()
	{
		return _properties;
	}
    
    inline void setTexture(Texture2D* texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }
    
    inline Texture2D* getTexture()
    {
        return _texture;
    }
    
    inline void setComposeType(unsigned int composeType)
    {
        _composeType = composeType;
    }
    
    inline unsigned int getComposeType()
    {
        return _composeType;
    }

public:
    //tileset 的三种方式
    enum ComposeType{
        ComposeTypeOnlyImage,
        ComposeTypeOnlyTiles
//        ComposeTypeImageAndTiles
    };
    
protected:
    /**
     * 名称
     */
    std::string _name;
    
    /**
     * 单独定义的文件名
     */
    std::string _fileName;
    
    /**
     * 每个tile的宽
     */
    int _tileWidth;
    
    /**
     * 每个tile的高
     */
    int _tileHeight;
    
    /**
     * 在tile图片里每个tile的内部空白
     */
    int _tileSpacing;
    
    /**
     * 整个tile图片边框的空白
     */
    int _margin;
    
    /**
     * 整个tile图片的偏移
     */
    Vec2 _tileOffset;
    
    /**
     * tile拼成的图片名
     */
    std::string _imageSource;
    
//    /**
//     * tile拼成的图片宽
//     */
//    int _imageWidth;
//    
//    /**
//     * tile拼成的图片高
//     */
//    int _imageHeight;
    
    Size _imageSize;
    
    /**
     * tile拼成的图片
     */
    Texture2D* _texture;
    
    /**
     * 图片的格子栏数
     */
    int _columnCount;
    
    /**
     * 所有小格子
     */
	ISOTileVector _tiles;
    
    /**
     * 开始的gid
     */
    unsigned int _firstGid;
    
    /**
     * 结束的gid
     */
    unsigned int _lastGid;
    
    /**
     * 属性
     */
    ValueMap _properties;
    
    /**
     * tile的属性
     */
	ValueMap _tileProperties;
    
    unsigned int _composeType;
    
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILESET_H_
