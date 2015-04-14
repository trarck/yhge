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

    bool isExternal() const { return !_sFileName.empty(); }
    
    int tileCount() const { return _pTiles->count(); }
    
    /**
     * 删除image tile
     */
//    virtual void cleanImageSourceTiles();
    
    virtual void loadFromImageSource();
    
    void appendTile(const char* imageName);
    
    void appendTile(CCTexture2D* pTexture);
    
    void setTile(unsigned int id,const char* imageName);
    
    void setTile(unsigned int id,CCTexture2D* pTexture);
    
    void addTile(unsigned int id,const char* imageName);
    
    void addTile(unsigned int id,CCTexture2D* pTexture);
    
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
    
    inline const char* getName(){ return _sName.c_str(); }
    inline void setName(const char *name){ _sName = name; }
    
    virtual void setFileName(const char* pFileName);
    virtual std::string& getFileName();
    virtual void setImageSource(const char* pImageSource);
    virtual std::string& getImageSource();
    virtual void setTileWidth(int nTileWidth);
    virtual int getTileWidth();
    virtual void setTileHeight(int nTileHeight);
    virtual int getTileHeight();
    
    virtual void setTileSize(CCSize& tTileSize){
        _nTileWidth=(int)tTileSize.width;
        _nTileHeight=(int)tTileSize.height;
    }
    
    virtual CCSize getTileSize(){
        return CCSizeMake(_nTileWidth, _nTileHeight);
    }
    
    virtual void setTileSpacing(int nTileSpacing);
    virtual int getTileSpacing();
    virtual void setMargin(int nMargin);
    virtual int getMargin();
    virtual void setTileOffset(CCPoint tTileOffset);
    virtual CCPoint getTileOffset();
//    virtual void setImageWidth(int nImageWidth);
//    virtual int getImageWidth();
//    virtual void setImageHeight(int nImageHeight);
//    virtual int getImageHeight();
    virtual void setColumnCount(int nColumnCount);
    virtual int getColumnCount();
    virtual void setTiles(CCArray* pTiles);
    virtual CCArray* getTiles();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
    inline void setImageSize(CCSize& tImageSize)
    {
        _tImageSize = tImageSize;
    }
    
    inline CCSize& getImageSize()
    {
        return _tImageSize;
    }


    virtual void setFirstGid(unsigned int uFirstGid);
    virtual unsigned int getFirstGid();
    
    virtual unsigned int getLastGid();
    /**
     * set zero to clear lastGid
     */
    virtual void setLastGid(unsigned int uLastGid);
    
    
    virtual void setTileProperties(CCDictionary* pTileProperties);
    virtual CCDictionary* getTileProperties();
    
    inline void setTexture(CCTexture2D* pTexture)
    {
        CC_SAFE_RETAIN(pTexture);
        CC_SAFE_RELEASE(_pTexture);
        _pTexture = pTexture;
    }
    
    inline CCTexture2D* getTexture()
    {
        return _pTexture;
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
    std::string _sName;
    
    /**
     * 单独定义的文件名
     */
    std::string _sFileName;
    
    /**
     * 每个tile的宽
     */
    int _nTileWidth;
    
    /**
     * 每个tile的高
     */
    int _nTileHeight;
    
    /**
     * 在tile图片里每个tile的内部空白
     */
    int _nTileSpacing;
    
    /**
     * 整个tile图片边框的空白
     */
    int _nMargin;
    
    /**
     * 整个tile图片的偏移
     */
    CCPoint _tTileOffset;
    
    /**
     * tile拼成的图片名
     */
    std::string _sImageSource;
    
//    /**
//     * tile拼成的图片宽
//     */
//    int _nImageWidth;
//    
//    /**
//     * tile拼成的图片高
//     */
//    int _nImageHeight;
    
    CCSize _tImageSize;
    
    /**
     * tile拼成的图片
     */
    CCTexture2D* _pTexture;
    
    /**
     * 图片的格子栏数
     */
    int _nColumnCount;
    
    /**
     * 所有小格子
     */
    CCArray* _pTiles;
    
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
    CCDictionary* _pProperties;
    
    /**
     * tile的属性
     */
    CCDictionary* _pTileProperties;
    
    unsigned int _uComposeType;
    
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILESET_H_
