#ifndef YHGE_ISOMETRIC_ISOTILE_H_
#define YHGE_ISOMETRIC_ISOTILE_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

class ISOTileset;

/**
 * 地图的显示单元
 * 直接使用texure。如果使用sprite，则无法共用。
 */
class ISOTile : public Ref{

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
    
    inline void setAnimation(CCAnimation* pAnimation)
    {
        CC_SAFE_RETAIN(pAnimation);
        CC_SAFE_RELEASE(m_pAnimation);
        m_pAnimation = pAnimation;
    }
    
    inline CCAnimation* getAnimation()
    {
        return m_pAnimation;
    }
    
protected:
    
    //id
    int m_nId;
    
    //支持tile大小不同
    CCTexture2D* m_pTexture;
    
    //tile在texture的位置
    CCRect m_tTextureRect;
    
    /**
     * 动画
     */
    CCAnimation* m_pAnimation;
    
    //所属的tileset.weak reference
    ISOTileset* m_pTileset;
    
    /**
     * 属性
     */
    CCDictionary* m_pProperties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILE_H_
