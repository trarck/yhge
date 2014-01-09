#ifndef YHGE_ISOMETRIC_ISOBATCHTILELAYER_H_
#define YHGE_ISOMETRIC_ISOBATCHTILELAYER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/CocosExt/Support/ccCArray.h>
#include "../ISOInfos.h"
#include "ISOTileLayer.h"


NS_CC_YHGE_BEGIN

/**
 * 使用batch node来渲染layer.(TMX的渲染方式)
 * 一个layer只有一个tileset,tileset只有一个拼图。
 * 暂不支持多个tileset
 */
class ISOBatchTileLayer : public ISOTileLayer {

public:
	
	ISOBatchTileLayer();
    
	~ISOBatchTileLayer(void);

    bool init();
    /**
     * 初始化显示tiles
     */
    virtual void setupTiles();
    
    void setTileGID(unsigned int gid, const CCPoint& pos);
    
    void removeChild(CCNode* node, bool cleanup);
    
    /**
     * 获取tile
     */
    
	virtual CCSprite* tileSpriteAt(const CCPoint& pos);
    
    /**
     * 删除tile
     */
    void removeTileSpriteAt(const CCPoint& pos);
    
public:
    
    void setTileset(ISOTileset* pTileset);
    ISOTileset* getTileset();
    
    void setTileSets(CCArray* pTileSets);
    CCArray* getTileSets();
    
    inline void setMinGID(unsigned int uMinGID)
    {
        m_uMinGID = uMinGID;
    }
    
    inline unsigned int getMinGID()
    {
        return m_uMinGID;
    }
    
    inline void setMaxGID(unsigned int uMaxGID)
    {
        m_uMaxGID = uMaxGID;
    }
    
    inline unsigned int getMaxGID()
    {
        return m_uMaxGID;
    }

protected:
   
    /**
     * 设置tile
     */
    void setupTileSprite(CCSprite* sprite, CCPoint mapCoord, unsigned int gid);
    CCSprite* reusedTileWithRect(CCRect rect);
    
    CCSprite* appendTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* insertTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* updateTileForGID(unsigned int gid, const CCPoint& pos);
    
    unsigned int atlasIndexForExistantZ(unsigned int z);
    unsigned int atlasIndexForNewZ(int z);
    
    void addQuadFromSprite(CCSprite *sprite, unsigned int index);
    void addSpriteWithoutQuad(CCSprite*child, unsigned int z, int aTag);
    
protected:

    ISOTileset* m_pTileset;
    //对于多个tileSet的支持。这样就不能使用batch node。所以最好一个layer使用一个tileSet
    CCArray* m_pTileSets;
    
    CCSpriteBatchNode* m_pSpriteBatchNode;
    
    
    
    unsigned int        m_uMinGID;
    unsigned int        m_uMaxGID;
       
    //! used for optimization
    CCSprite*           m_pReusedTile;
    yhge::ccCArray*           m_pAtlasIndexArray;
    
    // used for retina display
    float               m_fContentScaleFactor;

};



NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOBATCHTILELAYER_H_
