#include "ISOTileset.h"
#include "ISOCoordinate.h"



NS_CC_YHGE_BEGIN

ISOTileset::ISOTileset()
:m_sName("")
,m_sFileName("")
,m_sImageSource("")
,m_nTileWidth(0)
,m_nTileHeight(0)
,m_nTileSpacing(0)
,m_nMargin(0)
,m_tTileOffset(CCPointZero)
//,m_nImageWidth(0)
//,m_nImageHeight(0)
,m_tImageSize(CCSizeZero)
,m_nColumnCount(0)
,m_pTiles(NULL)
,m_uFirstGid(0)
,m_uLastGid(0)
,m_pProperties(NULL)
,m_pTileProperties(NULL)
,m_pTexture(NULL)
{
    
}

ISOTileset::~ISOTileset()
{
    CCLOG("ISOTileset destroy");
    CC_SAFE_RELEASE(m_pTiles);
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pTileProperties);
    CC_SAFE_RELEASE(m_pTexture);
}

bool ISOTileset::init()
{
    m_pTiles=new CCArray();
    m_pTiles->init();
    
    m_pProperties=new CCDictionary();
    
    m_pTileProperties=new CCDictionary();
    return true;
}

//void ISOTileset::cleanImageSourceTiles()
//{
//    if(!m_sImageSource.empty()){
//        int column=columnCountForWidth(m_tImageSize.width);
//        int row=rowCountForHeight(m_tImageSize.height);
//        
//        int imageTileCount=row*column;
//        
//        if(m_pTiles->count()>imageTileCount){
//            int leftCount=m_pTiles->count()-imageTileCount;
//            //还有独立的tile定义.剩下的放入新的tiles里
//            CCArray* newTiles=new CCArray(leftCount);
//            CCObject* pObj;
//                                                            
//            for(CCObject** arr = m_pTiles->data->arr+imageTileCount, **end = m_pTiles->data->arr + m_pTiles->data->num-1;
//                arr <= end && ((pObj = *arr) != NULL/* || true*/);                                                
//                arr++){
//                newTiles->addObject(pObj);
//            }
//            setTiles(newTiles);
//            newTiles->release();
//        }else{
//            m_pTiles->removeAllObjects();
//        }
//    }
//}

void ISOTileset::loadFromImageSource()
{
    if(!m_sImageSource.empty()){
        
        setTexture(CCTextureCache::sharedTextureCache()->addImage(m_sImageSource.c_str()));
        
        if(m_tImageSize.width==0 || m_tImageSize.height==0){
            m_tImageSize=m_pTexture->getContentSize();
        }
        
        int column=columnCountForWidth(m_tImageSize.width);
        int row=rowCountForHeight(m_tImageSize.height);
        
        int idx=0;
        int oldTilesSize=m_pTiles->count();
        for (int j=0; j<row; ++j) {
            for(int i=0;i<column;++i){
                ISOTile* tile=new ISOTile();
                CCRect rect=rectForId(idx);
                tile->init(idx, this,m_pTexture,rect);
                if(idx<oldTilesSize){
                    m_pTiles->replaceObjectAtIndex(idx, tile);
                }else{
                    m_pTiles->addObject(tile);
                }
                tile->release();
                ++idx;
            }
        }
        m_uLastGid=lastGid();
    }
}

int ISOTileset::columnCountForWidth(float width)
{
    CCAssert(m_nTileWidth > 0,"ISOTileset::columnCountForWidth m_nTileWidth must big then 0");
    return (int)(width - m_nMargin + m_nTileSpacing) / (m_nTileWidth + m_nTileSpacing);
}

int ISOTileset::rowCountForHeight(float height)
{
    CCAssert(m_nTileHeight > 0,"ISOTileset::columnRowForHeight m_nTileHeight must big then 0");
    return (int)(height - m_nMargin + m_nTileSpacing) / (m_nTileHeight + m_nTileSpacing);
}

CCRect ISOTileset::rectForId(unsigned int id)
{
    CCRect rect;
    rect.size = CCSizeMake(m_nTileWidth, m_nTileHeight);
    int max_x = (int)((m_tImageSize.width - m_nMargin*2 + m_nTileSpacing) / (m_nTileWidth + m_nTileSpacing));
    rect.origin.x = (id % max_x) * (m_nTileWidth + m_nTileSpacing) + m_nMargin;
    rect.origin.y = (id / max_x) * (m_nTileHeight + m_nTileSpacing) + m_nMargin;
    return rect;
}

CCSprite* ISOTileset::tileSpriteForId(unsigned int id)
{
    CCSprite* sprite=new CCSprite();
    CCRect rect=rectForId(id);
    sprite->initWithTexture(m_pTexture,rect);
    sprite->autorelease();
    
    return sprite;
}

ISOTile* ISOTileset::tileForId(unsigned int id)
{
    return (ISOTile*)m_pTiles->objectAtIndex(id);
//    //dynamic
//       CCSprite* sprite=tileSpriteForId(id);
//    ISOTile* tile=new ISOTile();
//    tile->init(id, this, sprite);
//    tile->autorelease();
//    return tile;
}

unsigned int ISOTileset::lastGid()
{
    return m_uFirstGid+m_pTiles->count()-1;
//    CCAssert(m_tImageSize.width>0 && m_tImageSize.height>0, "ISOTileset::lastGid the image size shuold not 0");
//    int column=columnCountForWidth(m_tImageSize.width);
//    int row=rowCountForHeight(m_tImageSize.height);
//    CCAssert(column*row>0, "ISOTileset::lastGid column*row must big then 0");
//    return m_uFirstGid+(column*row-1);
}

bool ISOTileset::contains(unsigned int gid)
{
    return m_uFirstGid<=gid && m_uLastGid>=gid;
}

CCRect ISOTileset::rectForGid(unsigned int gid)
{
    return rectForId(gid - m_uFirstGid);
}

CCSprite* ISOTileset::tileSpriteForGid(unsigned int gid)
{
    return tileSpriteForId(gid - m_uFirstGid);
}

ISOTile* ISOTileset::tileForGid(unsigned int gid)
{
    return tileForId(gid - m_uFirstGid);
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
    m_pTiles->addObject(tile);
    tile->release();
    
    m_uLastGid=lastGid();
}

void ISOTileset::setTile(unsigned int id,const char* imageName)
{
    CCTexture2D* pTexture=CCTextureCache::sharedTextureCache()->addImage(imageName);
    setTile(id, pTexture);
}

void ISOTileset::setTile(unsigned int id,CCTexture2D* pTexture)
{
    ISOTile* tile=(ISOTile*)m_pTiles->objectAtIndex(id);
    if(tile){
        tile->setTexture(pTexture);
    }else{
        ISOTile* tile=new ISOTile();
        tile->init(id, this, pTexture);
        m_pTiles->replaceObjectAtIndex(id, tile);
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
            m_pTiles->addObject(NULL);
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
        m_pTiles->replaceObjectAtIndex(id, tile);
    }else if(id==tileCount){
        m_pTiles->addObject(tile);
    }else{
        //补充空的tile
        unsigned int padCount=id-tileCount;
        for(unsigned int i=0;i<padCount;++i){
            m_pTiles->addObject(NULL);
        }
        //增加新的tile
        m_pTiles->addObject(tile);
    }
}


void ISOTileset::setFileName(const char* pFileName)
{
    m_sFileName = pFileName;
}

std::string& ISOTileset::getFileName()
{
    return m_sFileName;
}

void ISOTileset::setImageSource(const char* pImageSource)
{
    m_sImageSource = pImageSource;    
}

std::string& ISOTileset::getImageSource()
{
    return m_sImageSource;
}

void ISOTileset::setTileWidth(int nTileWidth)
{
    m_nTileWidth = nTileWidth;
}

int ISOTileset::getTileWidth()
{
    return m_nTileWidth;
}

void ISOTileset::setTileHeight(int nTileHeight)
{
    m_nTileHeight = nTileHeight;
}

int ISOTileset::getTileHeight()
{
    return m_nTileHeight;
}

void ISOTileset::setTileSpacing(int nTileSpacing)
{
    m_nTileSpacing = nTileSpacing;
}

int ISOTileset::getTileSpacing()
{
    return m_nTileSpacing;
}

void ISOTileset::setMargin(int nMargin)
{
    m_nMargin = nMargin;
}

int ISOTileset::getMargin()
{
    return m_nMargin;
}

void ISOTileset::setTileOffset(CCPoint tTileOffset)
{
    m_tTileOffset = tTileOffset;
}

CCPoint ISOTileset::getTileOffset()
{
    return m_tTileOffset;
}

//void ISOTileset::setImageWidth(int nImageWidth)
//{
//    m_nImageWidth = nImageWidth;
//}
//
//int ISOTileset::getImageWidth()
//{
//    return m_nImageWidth;
//}
//
//void ISOTileset::setImageHeight(int nImageHeight)
//{
//    m_nImageHeight = nImageHeight;
//}
//
//int ISOTileset::getImageHeight()
//{
//    return m_nImageHeight;
//}

void ISOTileset::setColumnCount(int nColumnCount)
{
    m_nColumnCount = nColumnCount;
}

int ISOTileset::getColumnCount()
{
    return m_nColumnCount;
}

void ISOTileset::setTiles(CCArray* pTiles)
{
    CC_SAFE_RETAIN(pTiles);
    CC_SAFE_RELEASE(m_pTiles);
    m_pTiles = pTiles;
}

CCArray* ISOTileset::getTiles()
{
    return m_pTiles;
}

void ISOTileset::setFirstGid(unsigned int uFirstGid)
{
    m_uFirstGid = uFirstGid;
}

unsigned int ISOTileset::getFirstGid()
{
    return m_uFirstGid;
}

unsigned int ISOTileset::getLastGid()
{
    return this->m_uLastGid;
}

void ISOTileset::setLastGid(unsigned int gid)
{
    this->m_uLastGid=gid;
}

void ISOTileset::setTileProperties(CCDictionary* pTileProperties)
{
    m_pTileProperties=pTileProperties;
}

CCDictionary* ISOTileset::getTileProperties()
{
    return m_pTileProperties;
}

void ISOTileset::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* ISOTileset::getProperties()
{
    return m_pProperties;
}

NS_CC_YHGE_END
