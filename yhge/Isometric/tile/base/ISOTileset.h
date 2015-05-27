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
    
    ISOTileset();
    
    ~ISOTileset();
    
    bool init();

    bool isExternal() const { return !_fileName.empty(); }
    
    int tileCount() const { return _tiles->count(); }
    
    /**
     * 删除image tile
     */
//    virtual void cleanImageSourceTiles();
    
    virtual void loadFromImageSource();
    
    void appendTile(const char* imageName);
    
    void appendTile(CCTexture2D* texture);
    
    void setTile(unsigned int id,const char* imageName);
    
    void setTile(unsigned int id,CCTexture2D* texture);
    
    void addTile(unsigned int id,const char* imageName);
    
    void addTile(unsigned int id,CCTexture2D* texture);
    
    void addTile(ISOTile* tile);
    
    
    /**
     * 内置索引id
     */
    CCRect rectForId(unsigned int id);
    
    CCSprite* tileSpriteForId(unsigned int id);
    
    ISOTile* tileForId(unsigned int id);
    
    /**
     * 是否包含某个id
     */
    bool contains(unsigned int gid);
    
    CCRect rectForGid(unsigned int gid);
    
    CCSprite* tileSpriteForGid(unsigned int gid);
    
    ISOTile* tileForGid(unsigned int gid);
    
    unsigned int lastGid();
    
    int columnCountForWidth(float width);
    
    int rowCountForHeight(float height);    
    
    
    
public:
    
    inline const char* getName(){ return _name.c_str(); }
    inline void setName(const char *name){ _name = name; }
    
    virtual void setFileName(const char* pFileName);
    virtual std::string& getFileName();
    virtual void setImageSource(const char* pImageSource);
    virtual std::string& getImageSource();
    virtual void setTileWidth(int tileWidth);
    virtual int getTileWidth();
    virtual void setTileHeight(int tileHeight);
    virtual int getTileHeight();
    
    virtual void setTileSize(Size& tTileSize){
        _tileWidth=(int)tTileSize.width;
        _tileHeight=(int)tTileSize.height;
    }
    
    virtual Size getTileSize(){
        return CCSizeMake(_tileWidth, _tileHeight);
    }
    
    virtual void setTileSpacing(int tileSpacing);
    virtual int getTileSpacing();
    virtual void setMargin(int margin);
    virtual int getMargin();
    virtual void setileOffset(Vec2 tileOffset);
    virtual Vec2 getileOffset();
//    virtual void setImageWidth(int imageWidth);
//    virtual int getImageWidth();
//    virtual void setImageHeight(int imageHeight);
//    virtual int getImageHeight();
    virtual void setColumnCount(int columnCount);
    virtual int getColumnCount();
    virtual void setTiles(CCArray* tiles);
    virtual CCArray* getTiles();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
    inline void setImageSize(Size& imageSize)
    {
        _imageSize = imageSize;
    }
    
    inline Size& getImageSize()
    {
        return _imageSize;
    }


    virtual void setFirstGid(unsigned int uFirstGid);
    virtual unsigned int getFirstGid();
    
    virtual unsigned int getLastGid();
    /**
     * set zero to clear lastGid
     */
    virtual void setLastGid(unsigned int uLastGid);
    
    
    virtual void setTileProperties(CCDictionary* tileProperties);
    virtual CCDictionary* getTileProperties();
    
    inline void setTexture(CCTexture2D* texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }
    
    inline CCTexture2D* getTexture()
    {
        return _texture;
    }
    
    inline void setComposeType(unsigned int uComposeType)
    {
        _uComposeType = uComposeType;
    }
    
    inline unsigned int getComposeType()
    {
        return _uComposeType;
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
    CCTexture2D* _texture;
    
    /**
     * 图片的格子栏数
     */
    int _columnCount;
    
    /**
     * 所有小格子
     */
    CCArray* _tiles;
    
    /**
     * 开始的gid
     */
    unsigned int _uFirstGid;
    
    /**
     * 结束的gid
     */
    unsigned int _uLastGid;
    
    /**
     * 属性
     */
    CCDictionary* _properties;
    
    /**
     * tile的属性
     */
    CCDictionary* _tileProperties;
    
    unsigned int _uComposeType;
    
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILESET_H_
