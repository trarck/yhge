#include "ISOTileLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../base/ISOTileset.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileLayer::ISOTileLayer()
:_startX(0)
,_startY(0)
,_pTiles(NULL)
,_tileMap(NULL)
{
	
}

ISOTileLayer::~ISOTileLayer()
{
    if(_pTiles )
    {
        delete [] _pTiles;
        _pTiles = NULL;
    }
}
//
//bool ISOTileLayer::init()
//{
//    _pProperties=new CCDictionary();
//    
//	return true;
//}
//
//bool ISOTileLayer::init(CCSize& mapTileSize)
//{
//    if(init()){
//        _tMapTileSize=mapTileSize;
//        return true;
//    }
//    return false;
//}
//
//bool ISOTileLayer::init(CCSize& mapTileSize,CCPoint& offset)
//{
//    if(init(mapTileSize)){
//        _tOffset=offset;
//        return true;
//    }
//    return false;
//}


void ISOTileLayer::initOffset(const CCPoint& tOffset)
{
//    this->setPosition(tOffset);
	this->setOffset(tOffset);
	CCPoint startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(tOffset));
	_startX=(int)startMapCoord.x;
	_startY=(int)startMapCoord.y;
}

void ISOTileLayer::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}

ISOTileLayer* ISOTileLayer::create()
{
    ISOTileLayer* pRet=new ISOTileLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}

/**
 * 初始化显示
 */
void ISOTileLayer::setupLayer()
{
    setupTiles();
}

void ISOTileLayer::releaseLayer()
{
    if (_pTiles)
    {
        delete [] _pTiles;
        _pTiles = NULL;
    }
}

void ISOTileLayer::setupTiles()
{
    CCAssert(false, "you must impl ISOTileLayer::setupTiles");
}

void ISOTileLayer::addTileAt(float x,float y)
{
    addTileAt(ccp(x,y));
}

void ISOTileLayer::addTileAt(const CCPoint& pos)
{
    CCAssert(false, "you must impl ISOTileLayer::addTileAt");
}

/**
 * 获取tile
 */
ISOTile* ISOTileLayer::tileAt(float x,float y)
{
    return tileAt(ccp(x,y));
}


ISOTile* ISOTileLayer::tileAt(const CCPoint& pos)
{
    ISOTile* tile=NULL;
    unsigned int gid=tileGIDAt(pos);
    
    if(gid>0){
        ISOTileset* tileset=_tileMap->getTilesetGroup()->getTilesetByGid(gid);
        tile=tileset->tileForGid(gid);
    }
    
    return tile;
}

void ISOTileLayer::removeTileAt(float x,float y)
{
    removeTileAt(ccp(x,y));
}

void ISOTileLayer::removeTileAt(const CCPoint& pos)
{
    CCAssert(pos.x < _tLayerSize.width && pos.y < _tLayerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer::removeTileAt: invalid position");
    
    int idx = (int)(pos.x + pos.y * _tLayerSize.width);
    _pTiles[idx]=0;
}

unsigned int ISOTileLayer::tileGIDAt(float x,float y)
{
    return tileGIDAt(ccp(x,y));
}

unsigned int ISOTileLayer::tileGIDAt(const CCPoint& pos)
{
    if(pos.x < _tLayerSize.width && pos.y < _tLayerSize.height && pos.x >=0 && pos.y >=0){
        int idx = (int)(pos.x + pos.y * _tLayerSize.width);
        unsigned int gid = _pTiles[idx];
        
        return gid;
    }
    return 0;
}


//TODO 
void ISOTileLayer::setTileGID(unsigned int gid, const CCPoint& pos)
{
    CCAssert(pos.x < _tLayerSize.width && pos.y < _tLayerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer::setTileGID: invalid position");
    int idx = (int)(pos.x + pos.y * _tLayerSize.width);
    _pTiles[idx]=gid;
}

void ISOTileLayer::setTileGID(unsigned int gid, float x,float y)
{
    setTileGID(gid,ccp(x,y));
}

void ISOTileLayer::scroll(const CCPoint& tOffset)
{
//    CCLOG("ISOTileLayer::scroll");
}

void ISOTileLayer::scroll(float x,float y)
{
    scroll(ccp(x,y));
}

/**
 * 地图的缩放值
 */
void ISOTileLayer::onMapScaleChange(float orignalScale,float newScale)
{
    
}

void ISOTileLayer::parseInternalProperties()
{
    CCLOG("ISOTileLayer::parseInternalProperties");
    // if cc_vertex=automatic, then tiles will be rendered using vertexz
    
    CCString *vertexz = propertyNamed("cc_vertexz");
    if (vertexz)
    {
        // If "automatic" is on, then parse the "cc_alpha_func" too
        if (vertexz->_sString == "automatic")
        {
            _useAutomaticVertexZ = true;
            CCString *alphaFuncVal = propertyNamed("cc_alpha_func");
            float alphaFuncValue = 0.0f;
            if (alphaFuncVal != NULL)
            {
                alphaFuncValue = alphaFuncVal->floatValue();
            }
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest));
            
            GLint alphaValueLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kCCUniformAlphaTestValue);
            
            // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
            getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, alphaFuncValue);
        }
        else
        {
            _vertexZvalue = vertexz->intValue();
        }
    }
}

unsigned int  ISOTileLayer::indexForPos(const CCPoint& pos)
{
    unsigned int index=(unsigned int)(pos.x + pos.y * _tLayerSize.width);
    return index;
}

unsigned int ISOTileLayer::zOrderToIndex(int z)
{
	return (unsigned int)(_tLayerSize.width*_tLayerSize.height-z);
}

void ISOTileLayer::setTiles(unsigned int* pTiles)
{
    _pTiles = pTiles;
}

unsigned int* ISOTileLayer::getTiles()
{
    return _pTiles;
}

//===============tile sprite===============

/**
 * 获取tile
 */
CCSprite* ISOTileLayer::tileSpriteAt(float x,float y)
{
    return tileSpriteAt(ccp(x,y));
}

CCSprite* ISOTileLayer::tileSpriteAt(const CCPoint& pos)
{
    CCSprite* sprite=NULL;
    
    ISOTile* tile=tileAt(pos);
    if(tile){
        sprite=CCSprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    }
    
    return sprite;
}

/**
 * 删除tile
 */
void ISOTileLayer::removeTileSpriteAt(float x,float y)
{
    removeTileSpriteAt(ccp(x,y));
}

void ISOTileLayer::removeTileSpriteAt(const CCPoint& pos)
{
    CCAssert(false, "you must impl ISOTileLayer::removeSpriteTileAt");
}

void ISOTileLayer::setMap(ISOMap* pMap)
{
    _tileMap=static_cast<ISOTileMap*>(pMap);
}
NS_CC_YHGE_ISOMETRIC_END
