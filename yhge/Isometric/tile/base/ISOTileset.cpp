#include "ISOTileset.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileset::ISOTileset()
:_sName("")
,_sFileName("")
,_sImageSource("")
,_nTileWidth(0)
,_nTileHeight(0)
,_nTileSpacing(0)
,_nMargin(0)
,_tTileOffset(CCPointZero)
//,_nImageWidth(0)
//,_nImageHeight(0)
,_tImageSize(CCSizeZero)
,_nColumnCount(0)
,_pTiles(NULL)
,_uFirstGid(0)
,_uLastGid(0)
,_pProperties(NULL)
,_pTileProperties(NULL)
,_pTexture(NULL)
,_uComposeType(0)
{
    
}

ISOTileset::~ISOTileset()
{
    CCLOG("ISOTileset destroy");
    CC_SAFE_RELEASE(_pTiles);
    CC_SAFE_RELEASE(_pProperties);
    CC_SAFE_RELEASE(_pTileProperties);
    CC_SAFE_RELEASE(_pTexture);
}

bool ISOTileset::init()
{
    _pTiles=new CCArray();
    _pTiles->init();
    
    _pProperties=new CCDictionary();
    
    _pTileProperties=new CCDictionary();
    return true;
}

//void ISOTileset::cleanImageSourceTiles()
//{
//    if(!_sImageSource.empty()){
//        int column=columnCountForWidth(_tImageSize.width);
//        int row=rowCountForHeight(_tImageSize.height);
//        
//        int imageTileCount=row*column;
//        
//        if(_pTiles->count()>imageTileCount){
//            int leftCount=_pTiles->count()-imageTileCount;
//            //还有独立的tile定义.剩下的放入新的tiles里
//            CCArray* newTiles=new CCArray(leftCount);
//            Ref* pObj;
//                                                            
//            for(Ref** arr = _pTiles->data->arr+imageTileCount, **end = _pTiles->data->arr + _pTiles->data->num-1;
//                arr <= end && ((pObj = *arr) != NULL/* || true*/);                                                
//                arr++){
//                newTiles->addObject(pObj);
//            }
//            setTiles(newTiles);
//            newTiles->release();
//        }else{
//            _pTiles->removeAllObjects();
//        }
//    }
//}

void ISOTileset::loadFromImageSource()
{
    if(!_sImageSource.empty()){
        
        setTexture(CCTextureCache::sharedTextureCache()->addImage(_sImageSource.c_str()));
        
        if(_tImageSize.width==0 || _tImageSize.height==0){
            _tImageSize=_pTexture->getContentSize();
        }
        
        int column=columnCountForWidth(_tImageSize.width);
        int row=rowCountForHeight(_tImageSize.height);
        
        int idx=0;
        int oldTilesSize=_pTiles->count();
        for (int j=0; j<row; ++j) {
            for(int i=0;i<column;++i){
                ISOTile* tile=new ISOTile();
                CCRect rect=rectForId(idx);
                tile->init(idx, this,_pTexture,rect);
                if(idx<oldTilesSize){
                    _pTiles->replaceObjectAtIndex(idx, tile);
                }else{
                    _pTiles->addObject(tile);
                }
                tile->release();
                ++idx;
            }
        }
        _uLastGid=lastGid();
    }
}

int ISOTileset::columnCountForWidth(float width)
{
    CCAssert(_nTileWidth > 0,"ISOTileset::columnCountForWidth _nTileWidth must big then 0");
    return (int)(width - _nMargin + _nTileSpacing) / (_nTileWidth + _nTileSpacing);
}

int ISOTileset::rowCountForHeight(float height)
{
    CCAssert(_nTileHeight > 0,"ISOTileset::columnRowForHeight _nTileHeight must big then 0");
    return (int)(height - _nMargin + _nTileSpacing) / (_nTileHeight + _nTileSpacing);
}

CCRect ISOTileset::rectForId(unsigned int id)
{
    CCRect rect;
    rect.size = CCSizeMake(_nTileWidth, _nTileHeight);
    int max_x = (int)((_tImageSize.width - _nMargin*2 + _nTileSpacing) / (_nTileWidth + _nTileSpacing));
    rect.origin.x = (id % max_x) * (_nTileWidth + _nTileSpacing) + _nMargin;
    rect.origin.y = (id / max_x) * (_nTileHeight + _nTileSpacing) + _nMargin;
    return rect;
}

CCSprite* ISOTileset::tileSpriteForId(unsigned int id)
{
    CCSprite* sprite=new CCSprite();
    CCRect rect=rectForId(id);
    sprite->initWithTexture(_pTexture,rect);
    sprite->autorelease();
    
    return sprite;
}

ISOTile* ISOTileset::tileForId(unsigned int id)
{
    return (ISOTile*)_pTiles->objectAtIndex(id);
//    //dynamic
//       CCSprite* sprite=tileSpriteForId(id);
//    ISOTile* tile=new ISOTile();
//    tile->init(id, this, sprite);
//    tile->autorelease();
//    return tile;
}

unsigned int ISOTileset::lastGid()
{
    return _uFirstGid+_pTiles->count()-1;
//    CCAssert(_tImageSize.width>0 && _tImageSize.height>0, "ISOTileset::lastGid the image size shuold not 0");
//    int column=columnCountForWidth(_tImageSize.width);
//    int row=rowCountForHeight(_tImageSize.height);
//    CCAssert(column*row>0, "ISOTileset::lastGid column*row must big then 0");
//    return _uFirstGid+(column*row-1);
}

bool ISOTileset::contains(unsigned int gid)
{
    return _uFirstGid<=gid && _uLastGid>=gid;
}

CCRect ISOTileset::rectForGid(unsigned int gid)
{
    return rectForId(gid - _uFirstGid);
}

CCSprite* ISOTileset::tileSpriteForGid(unsigned int gid)
{
    return tileSpriteForId(gid - _uFirstGid);
}

ISOTile* ISOTileset::tileForGid(unsigned int gid)
{
    return tileForId(gid - _uFirstGid);
}

void ISOTileset::appendTile(const char* imageName)
{
    CCTexture2D* pTexture=CCTextureCache::sharedTextureCache()->addImage(imageName);
    
    appendTile(pTexture);
}

void ISOTileset::appendTile(CCTexture2D* pTexture)
{
    ISOTile* tile=new ISOTile();
    tile->init(tileCount(), this, pTexture);
    _pTiles->addObject(tile);
    tile->release();
    
    _uLastGid=lastGid();
}

void ISOTileset::setTile(unsigned int id,const char* imageName)
{
    CCTexture2D* pTexture=CCTextureCache::sharedTextureCache()->addImage(imageName);
    setTile(id, pTexture);
}

void ISOTileset::setTile(unsigned int id,CCTexture2D* pTexture)
{
    ISOTile* tile=(ISOTile*)_pTiles->objectAtIndex(id);
    if(tile){
        tile->setTexture(pTexture);
    }else{
        ISOTile* tile=new ISOTile();
        tile->init(id, this, pTexture);
        _pTiles->replaceObjectAtIndex(id, tile);
        tile->release();
    }
}

void ISOTileset::addTile(unsigned int id,const char* imageName)
{
    CCTexture2D* pTexture=CCTextureCache::sharedTextureCache()->addImage(imageName);
    addTile(id, pTexture);
}

void ISOTileset::addTile(unsigned int id,CCTexture2D* pTexture)
{
    //如果index大于tile count，则中间插入空的
    unsigned int tileCount=this->tileCount();
    if(id<tileCount){
        //replace
        setTile(id, pTexture);
    }else if(id==tileCount){
        appendTile(pTexture);
    }else{
        //补充空的tile
        unsigned int padCount=id-tileCount;
        for(unsigned int i=0;i<padCount;++i){
            _pTiles->addObject(NULL);
        }
        //增加新的tile
        appendTile(pTexture);
    }
}

void ISOTileset::addTile(ISOTile* tile)
{
    //如果index大于tile count，则中间插入空的
    unsigned int tileCount=this->tileCount();
    unsigned int id=tile->getId();
    if(id<tileCount){
        //replace
        _pTiles->replaceObjectAtIndex(id, tile);
    }else if(id==tileCount){
        _pTiles->addObject(tile);
    }else{
        //补充空的tile
        unsigned int padCount=id-tileCount;
        for(unsigned int i=0;i<padCount;++i){
            _pTiles->addObject(NULL);
        }
        //增加新的tile
        _pTiles->addObject(tile);
    }
}


void ISOTileset::setFileName(const char* pFileName)
{
    _sFileName = pFileName;
}

std::string& ISOTileset::getFileName()
{
    return _sFileName;
}

void ISOTileset::setImageSource(const char* pImageSource)
{
    _sImageSource = pImageSource;    
}

std::string& ISOTileset::getImageSource()
{
    return _sImageSource;
}

void ISOTileset::setTileWidth(int nTileWidth)
{
    _nTileWidth = nTileWidth;
}

int ISOTileset::getTileWidth()
{
    return _nTileWidth;
}

void ISOTileset::setTileHeight(int nTileHeight)
{
    _nTileHeight = nTileHeight;
}

int ISOTileset::getTileHeight()
{
    return _nTileHeight;
}

void ISOTileset::setTileSpacing(int nTileSpacing)
{
    _nTileSpacing = nTileSpacing;
}

int ISOTileset::getTileSpacing()
{
    return _nTileSpacing;
}

void ISOTileset::setMargin(int nMargin)
{
    _nMargin = nMargin;
}

int ISOTileset::getMargin()
{
    return _nMargin;
}

void ISOTileset::setTileOffset(CCPoint tTileOffset)
{
    _tTileOffset = tTileOffset;
}

CCPoint ISOTileset::getTileOffset()
{
    return _tTileOffset;
}

//void ISOTileset::setImageWidth(int nImageWidth)
//{
//    _nImageWidth = nImageWidth;
//}
//
//int ISOTileset::getImageWidth()
//{
//    return _nImageWidth;
//}
//
//void ISOTileset::setImageHeight(int nImageHeight)
//{
//    _nImageHeight = nImageHeight;
//}
//
//int ISOTileset::getImageHeight()
//{
//    return _nImageHeight;
//}

void ISOTileset::setColumnCount(int nColumnCount)
{
    _nColumnCount = nColumnCount;
}

int ISOTileset::getColumnCount()
{
    return _nColumnCount;
}

void ISOTileset::setTiles(CCArray* pTiles)
{
    CC_SAFE_RETAIN(pTiles);
    CC_SAFE_RELEASE(_pTiles);
    _pTiles = pTiles;
}

CCArray* ISOTileset::getTiles()
{
    return _pTiles;
}

void ISOTileset::setFirstGid(unsigned int uFirstGid)
{
    _uFirstGid = uFirstGid;
}

unsigned int ISOTileset::getFirstGid()
{
    return _uFirstGid;
}

unsigned int ISOTileset::getLastGid()
{
    return this->_uLastGid;
}

void ISOTileset::setLastGid(unsigned int gid)
{
    this->_uLastGid=gid;
}

void ISOTileset::setTileProperties(CCDictionary* pTileProperties)
{
    _pTileProperties=pTileProperties;
}

CCDictionary* ISOTileset::getTileProperties()
{
    return _pTileProperties;
}

void ISOTileset::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(_pProperties);
    _pProperties = pProperties;
}

CCDictionary* ISOTileset::getProperties()
{
    return _pProperties;
}

NS_CC_YHGE_ISOMETRIC_END
