#include "ISOTileLayer.h"
#include <yhge/Isometric/CoordinateFormulae.h>
#include "../base/ISOTileset.h"
#include "../ISOTileMap.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileLayer::ISOTileLayer()
:_startX(0)
,_startY(0)
,_tiles(NULL)
,_tileMap(NULL)
{
	
}

ISOTileLayer::~ISOTileLayer()
{
    if(_tiles )
    {
        delete [] _tiles;
        _tiles = NULL;
    }
}
//
//bool ISOTileLayer::init()
//{
//    _properties=new CCDictionary();
//    
//	return true;
//}
//
//bool ISOTileLayer::init(Size& mapTileSize)
//{
//    if(init()){
//        _mapTileSize=mapTileSize;
//        return true;
//    }
//    return false;
//}
//
//bool ISOTileLayer::init(Size& mapTileSize,Vec2& offset)
//{
//    if(init(mapTileSize)){
//        _offset=offset;
//        return true;
//    }
//    return false;
//}


void ISOTileLayer::initOffset(const Vec2& offset)
{
//    this->setPosition(offset);
	this->setOffset(offset);
	Vec2 startMapCoord=YHGE_ISO_COORD_TRANSLATE_WRAP(isoViewToGamePoint(offset));
	_startX=(int)startMapCoord.x;
	_startY=(int)startMapCoord.y;
}

void ISOTileLayer::initOffset(float x,float y)
{
	this->inioffset(ccp(x,y));
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
    setutiles();
}

void ISOTileLayer::releaseLayer()
{
    if (_tiles)
    {
        delete [] _tiles;
        _tiles = NULL;
    }
}

void ISOTileLayer::setutiles()
{
    CCAssert(false, "you must impl ISOTileLayer::setutiles");
}

void ISOTileLayer::addTileAt(float x,float y)
{
    addTileAt(ccp(x,y));
}

void ISOTileLayer::addTileAt(const Vec2& pos)
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


ISOTile* ISOTileLayer::tileAt(const Vec2& pos)
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

void ISOTileLayer::removeTileAt(const Vec2& pos)
{
    CCAssert(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer::removeTileAt: invalid position");
    
    int idx = (int)(pos.x + pos.y * _layerSize.width);
    _tiles[idx]=0;
}

unsigned int ISOTileLayer::tileGIDAt(float x,float y)
{
    return tileGIDAt(ccp(x,y));
}

unsigned int ISOTileLayer::tileGIDAt(const Vec2& pos)
{
    if(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0){
        int idx = (int)(pos.x + pos.y * _layerSize.width);
        unsigned int gid = _tiles[idx];
        
        return gid;
    }
    return 0;
}


//TODO 
void ISOTileLayer::setTileGID(unsigned int gid, const Vec2& pos)
{
    CCAssert(pos.x < _layerSize.width && pos.y < _layerSize.height && pos.x >=0 && pos.y >=0, "ISOTileLayer::setTileGID: invalid position");
    int idx = (int)(pos.x + pos.y * _layerSize.width);
    _tiles[idx]=gid;
}

void ISOTileLayer::setTileGID(unsigned int gid, float x,float y)
{
    setTileGID(gid,ccp(x,y));
}

void ISOTileLayer::scroll(const Vec2& offset)
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
    
	Value vertexz = getProperty("cc_vertexz");
    if (!vertexz.isNull())
    {
		std::string vertexZStr = vertexz.asString();
        // If "automatic" is on, then parse the "cc_alpha_func" too
		if (vertexZStr == "automatic")
        {
            _useAutomaticVertexZ = true;
			Value alphaFuncVal = getProperty("cc_alpha_func");
			float alphaFuncValue = alphaFuncVal.asFloat();
               setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest));
            
            GLint alphaValueLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kCCUniformAlphaTestValue);
            
            // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
            getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, alphaFuncValue);
        }
        else
        {
			_vertexZvalue = vertexz.asInt();
        }
    }
}

unsigned int  ISOTileLayer::indexForPos(const Vec2& pos)
{
    unsigned int index=(unsigned int)(pos.x + pos.y * _layerSize.width);
    return index;
}

unsigned int ISOTileLayer::zOrderToIndex(int z)
{
	return (unsigned int)(_layerSize.width*_layerSize.height-z);
}

void ISOTileLayer::setTiles(unsigned int* tiles)
{
    _tiles = tiles;
}

unsigned int* ISOTileLayer::getTiles()
{
    return _tiles;
}

//===============tile sprite===============

/**
 * 获取tile
 */
Sprite* ISOTileLayer::tileSpriteAt(float x,float y)
{
    return tileSpriteAt(ccp(x,y));
}

Sprite* ISOTileLayer::tileSpriteAt(const Vec2& pos)
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

void ISOTileLayer::removeTileSpriteAt(const Vec2& pos)
{
    CCAssert(false, "you must impl ISOTileLayer::removeSpriteTileAt");
}

void ISOTileLayer::setMap(ISOMap* pMap)
{
    _tileMap=static_cast<ISOTileMap*>(pMap);
}
NS_CC_YHGE_ISOMETRIC_END
