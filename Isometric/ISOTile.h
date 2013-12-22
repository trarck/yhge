#ifndef YHGE_ISOMETRIC_ISOTILE_H_
#define YHGE_ISOMETRIC_ISOTILE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

class ISOTileset;

/**
 * 直接使用texure。如果使用sprite，则无法共用。
 *
 */
class ISOTile : public CCObject{

public:
    ISOTile();
    
    ~ISOTile();
    
    bool init();
    
    bool init(int id,ISOTileset* tileset);
    
    bool init(int id,ISOTileset* tileset,CCTexture2D* texture);
    
    bool init(int id,ISOTileset* tileset,CCTexture2D* texture,CCRect& textureRect);
   
    CCSize size(){return m_tTextureRect.size;}

public:
    
    virtual int getGId();
    
    
    virtual void setId(int nId);
    
    virtual int getId();    
    
    virtual void setTileset(ISOTileset* pTileset);
    
    virtual ISOTileset* getTileset();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
    inline void setTexture(CCTexture2D* pTexture)
    {
        CC_SAFE_RETAIN(pTexture);
        CC_SAFE_RELEASE(m_pTexture);
        m_pTexture = pTexture;
    }
    
    inline CCTexture2D* getTexture()
    {
        return m_pTexture;
    }
    
    inline void setTextureRect(CCRect& tTextureRect)
    {
        m_tTextureRect = tTextureRect;
    }
    
    inline CCRect& getTextureRect()
    {
        return m_tTextureRect;
    }
    
protected:
    
    int m_nId;
    
    //支持tile大小不同
    CCTexture2D* m_pTexture;
    
    CCRect m_tTextureRect;
    
    //weak reference
    ISOTileset* m_pTileset;
    
    /**
     * 属性
     */
    CCDictionary* m_pProperties;
};


NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOTILE_H_
