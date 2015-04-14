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
   
    CCSize size(){return _tTextureRect.size;}

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
        CC_SAFE_RELEASE(_pTexture);
        _pTexture = pTexture;
    }
    
    inline CCTexture2D* getTexture()
    {
        return _pTexture;
    }
    
    inline void setTextureRect(CCRect& tTextureRect)
    {
        _tTextureRect = tTextureRect;
    }
    
    inline CCRect& getTextureRect()
    {
        return _tTextureRect;
    }
    
    inline void setAnimation(CCAnimation* pAnimation)
    {
        CC_SAFE_RETAIN(pAnimation);
        CC_SAFE_RELEASE(_pAnimation);
        _pAnimation = pAnimation;
    }
    
    inline CCAnimation* getAnimation()
    {
        return _pAnimation;
    }
    
protected:
    
    //id
    int _nId;
    
    //支持tile大小不同
    CCTexture2D* _pTexture;
    
    //tile在texture的位置
    CCRect _tTextureRect;
    
    /**
     * 动画
     */
    CCAnimation* _pAnimation;
    
    //所属的tileset.weak reference
    ISOTileset* _pTileset;
    
    /**
     * 属性
     */
    CCDictionary* _pProperties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILE_H_
