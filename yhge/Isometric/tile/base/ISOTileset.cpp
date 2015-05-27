#include "ISOTileset.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileset::ISOTileset()
:_name("")
,_fileName("")
,_imageSource("")
,_tileWidth(0)
,_tileHeight(0)
,_tileSpacing(0)
,_margin(0)
,_tileOffset(CCPointZero)
//,_imageWidth(0)
//,_imageHeight(0)
,_imageSize(CCSizeZero)
,_columnCount(0)
,_tiles(NULL)
,_firstGid(0)
,_lastGid(0)
,_properties(NULL)
,_tileProperties(NULL)
,_texture(NULL)
,_composeType(0)
{
    
}

ISOTileset::~ISOTileset()
{
    CCLOG("ISOTileset destroy");
    CC_SAFE_RELEASE(_tiles);
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_tileProperties);
    CC_SAFE_RELEASE(_texture);
}

bool ISOTileset::init()
{
    _tiles=new CCArray();
    _tiles->init();
    
    _properties=new CCDictionary();
    
    _tileProperties=new CCDictionary();
    return true;
}

//void ISOTileset::cleanImageSourceTiles()
//{
//    if(!_imageSource.empty()){
//        int column=columnCountForWidth(_imageSize.width);
//        int row=rowCountForHeight(_imageSize.height);
//        
//        int imageTileCount=row*column;
//        
//        if(_tiles->count()>imageTileCount){
//            int leftCount=_tiles->count()-imageTileCount;
//            //还有独立的tile定义.剩下的放入新的tiles里
//            CCArray* newTiles=new CCArray(leftCount);
//            Ref* pObj;
//                                                            
//            for(Ref** arr = _tiles->data->arr+imageTileCount, **end = _tiles->data->arr + _tiles->data->num-1;
//                arr <= end && ((pObj = *arr) != NULL/* || true*/);                                                
//                arr++){
//                newTiles->addObject(pObj);
//            }
//            setTiles(newTiles);
//            newTiles->release();
//        }else{
//            _tiles->removeAllObjects();
//        }
//    }
//}

void ISOTileset::loadFromImageSource()
{
    if(!_imageSource.empty()){
        
        setTexture(CCTextureCache::sharedTextureCache()->addImage(_imageSource.c_str()));
        
        if(_imageSize.width==0 || _imageSize.height==0){
            _imageSize=_texture->getContentSize();
        }
        
        int column=columnCountForWidth(_imageSize.width);
        int row=rowCountForHeight(_imageSize.height);
        
        int idx=0;
        int oldTilesSize=_tiles->count();
        for (int j=0; j<row; ++j) {
            for(int i=0;i<column;++i){
                ISOTile* tile=new ISOTile();
                CCRect rect=rectForId(idx);
                tile->init(idx, this,_texture,rect);
                if(idx<oldTilesSize){
                    _tiles->replaceObjectAtIndex(idx, tile);
                }else{
                    _tiles->addObject(tile);
                }
                tile->release();
                ++idx;
            }
        }
        _lastGid=lastGid();
    }
}

int ISOTileset::columnCountForWidth(float width)
{
    CCAssert(_tileWidth > 0,"ISOTileset::columnCountForWidth _tileWidth must big then 0");
    return (int)(width - _margin + _tileSpacing) / (_tileWidth + _tileSpacing);
}

int ISOTileset::rowCountForHeight(float height)
{
    CCAssert(_tileHeight > 0,"ISOTileset::columnRowForHeight _tileHeight must big then 0");
    return (int)(height - _margin + _tileSpacing) / (_tileHeight + _tileSpacing);
}

CCRect ISOTileset::rectForId(unsigned int id)
{
    CCRect rect;
    rect.size = CCSizeMake(_tileWidth, _tileHeight);
    int max_x = (int)((_imageSize.width - _margin*2 + _tileSpacing) / (_tileWidth + _tileSpacing));
    rect.origin.x = (id % max_x) * (_tileWidth + _tileSpacing) + _margin;
    rect.origin.y = (id / max_x) * (_tileHeight + _tileSpacing) + _margin;
    return rect;
}

CCSprite* ISOTileset::tileSpriteForId(unsigned int id)
{
    CCSprite* sprite=new CCSprite();
    CCRect rect=rectForId(id);
    sprite->initWithTexture(_texture,rect);
    sprite->autorelease();
    
    return sprite;
}

ISOTile* ISOTileset::tileForId(unsigned int id)
{
    return (ISOTile*)_tiles->objectAtIndex(id);
//    //dynamic
//       CCSprite* sprite=tileSpriteForId(id);
//    ISOTile* tile=new ISOTile();
//    tile->init(id, this, sprite);
//    tile->autorelease();
//    return tile;
}

unsigned int ISOTileset::lastGid()
{
    return _firstGid+_tiles->count()-1;
//    CCAssert(_imageSize.width>0 && _imageSize.height>0, "ISOTileset::lastGid the image size shuold not 0");
//    int column=columnCountForWidth(_imageSize.width);
//    int row=rowCountForHeight(_imageSize.height);
//    CCAssert(column*row>0, "ISOTileset::lastGid column*row must big then 0");
//    return _firstGid+(column*row-1);
}

bool ISOTileset::contains(unsigned int gid)
{
    return _firstGid<=gid && _lastGid>=gid;
}

CCRect ISOTileset::rectForGid(unsigned int gid)
{
    return rectForId(gid - _firstGid);
}

CCSprite* ISOTileset::tileSpriteForGid(unsigned int gid)
{
    return tileSpriteForId(gid - _firstGid);
}

ISOTile* ISOTileset::tileForGid(unsigned int gid)
{
    return tileForId(gid - _firstGid);
}

void ISOTileset::appendTile(const char* imageName)
{
    CCTexture2D* texture=CCTextureCache::sharedTextureCache()->addImage(imageName);
    
    appendTile(texture);
}

void ISOTileset::appendTile(CCTexture2D* texture)
{
    ISOTile* tile=new ISOTile();
    tile->init(tileCount(), this, texture);
    _tiles->addObject(tile);
    tile->release();
    
    _lastGid=lastGid();
}

void ISOTileset::setTile(unsigned int id,const char* imageName)
{
    CCTexture2D* texture=CCTextureCache::sharedTextureCache()->addImage(imageName);
    setTile(id, texture);
}

void ISOTileset::setTile(unsigned int id,CCTexture2D* texture)
{
    ISOTile* tile=(ISOTile*)_tiles->objectAtIndex(id);
    if(tile){
        tile->setTexture(texture);
    }else{
        ISOTile* tile=new ISOTile();
        tile->init(id, this, texture);
        _tiles->replaceObjectAtIndex(id, tile);
        tile->release();
    }
}

void ISOTileset::addTile(unsigned int id,const char* imageName)
{
    CCTexture2D* texture=CCTextureCache::sharedTextureCache()->addImage(imageName);
    addTile(id, texture);
}

void ISOTileset::addTile(unsigned int id,CCTexture2D* texture)
{
    //如果index大于tile count，则中间插入空的
    unsigned int tileCount=this->tileCount();
    if(id<tileCount){
        //replace
        setTile(id, texture);
    }else if(id==tileCount){
        appendTile(texture);
    }else{
        //补充空的tile
        unsigned int padCount=id-tileCount;
        for(unsigned int i=0;i<padCount;++i){
            _tiles->addObject(NULL);
        }
        //增加新的tile
        appendTile(texture);
    }
}

void ISOTileset::addTile(ISOTile* tile)
{
    //如果index大于tile count，则中间插入空的
    unsigned int tileCount=this->tileCount();
    unsigned int id=tile->getId();
    if(id<tileCount){
        //replace
        _tiles->replaceObjectAtIndex(id, tile);
    }else if(id==tileCount){
        _tiles->addObject(tile);
    }else{
        //补充空的tile
        unsigned int padCount=id-tileCount;
        for(unsigned int i=0;i<padCount;++i){
            _tiles->addObject(NULL);
        }
        //增加新的tile
        _tiles->addObject(tile);
    }
}


void ISOTileset::setFileName(const char* pFileName)
{
    _fileName = pFileName;
}

std::string& ISOTileset::getFileName()
{
    return _fileName;
}

void ISOTileset::setImageSource(const char* pImageSource)
{
    _imageSource = pImageSource;    
}

std::string& ISOTileset::getImageSource()
{
    return _imageSource;
}

void ISOTileset::setTileWidth(int tileWidth)
{
    _tileWidth = tileWidth;
}

int ISOTileset::getTileWidth()
{
    return _tileWidth;
}

void ISOTileset::setTileHeight(int tileHeight)
{
    _tileHeight = tileHeight;
}

int ISOTileset::getTileHeight()
{
    return _tileHeight;
}

void ISOTileset::setTileSpacing(int tileSpacing)
{
    _tileSpacing = tileSpacing;
}

int ISOTileset::getTileSpacing()
{
    return _tileSpacing;
}

void ISOTileset::setMargin(int margin)
{
    _margin = margin;
}

int ISOTileset::getMargin()
{
    return _margin;
}

void ISOTileset::setTileOffset(Vec2 tileOffset)
{
    _tileOffset = tileOffset;
}

Vec2 ISOTileset::getileOffset()
{
    return _tileOffset;
}

//void ISOTileset::setImageWidth(int imageWidth)
//{
//    _imageWidth = imageWidth;
//}
//
//int ISOTileset::getImageWidth()
//{
//    return _imageWidth;
//}
//
//void ISOTileset::setImageHeight(int imageHeight)
//{
//    _imageHeight = imageHeight;
//}
//
//int ISOTileset::getImageHeight()
//{
//    return _imageHeight;
//}

void ISOTileset::setColumnCount(int columnCount)
{
    _columnCount = columnCount;
}

int ISOTileset::getColumnCount()
{
    return _columnCount;
}

void ISOTileset::setTiles(CCArray* tiles)
{
    CC_SAFE_RETAIN(tiles);
    CC_SAFE_RELEASE(_tiles);
    _tiles = tiles;
}

CCArray* ISOTileset::getTiles()
{
    return _tiles;
}

void ISOTileset::setFirstGid(unsigned int firstGid)
{
    _firstGid = firstGid;
}

unsigned int ISOTileset::getFirstGid()
{
    return _firstGid;
}

unsigned int ISOTileset::getLastGid()
{
    return this->_lastGid;
}

void ISOTileset::setLastGid(unsigned int gid)
{
    this->_lastGid=gid;
}

void ISOTileset::setTileProperties(CCDictionary* tileProperties)
{
    _tileProperties=tileProperties;
}

CCDictionary* ISOTileset::getTileProperties()
{
    return _tileProperties;
}

void ISOTileset::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(_properties);
    _properties = pProperties;
}

CCDictionary* ISOTileset::getProperties()
{
    return _properties;
}

NS_CC_YHGE_ISOMETRIC_END
