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
   
    Size size(){return _textureRect.size;}

public:
    
    virtual int getGId();
    
    
    virtual void setId(int id);
    
    virtual int getId();    
    
    virtual void setTileset(ISOTileset* tileset);
    
    virtual ISOTileset* getTileset();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
    inline void setTexture(CCTexture2D* texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }
    
    inline CCTexture2D* getTexture()
    {
        return _texture;
    }
    
    inline void setTextureRect(CCRect& textureRect)
    {
        _textureRect = textureRect;
    }
    
    inline CCRect& getTextureRect()
    {
        return _textureRect;
    }
    
    inline void setAnimation(CCAnimation* animation)
    {
        CC_SAFE_RETAIN(animation);
        CC_SAFE_RELEASE(_animation);
        _animation = animation;
    }
    
    inline CCAnimation* getAnimation()
    {
        return _animation;
    }
    
protected:
    
    //id
    int _id;
    
    //支持tile大小不同
    CCTexture2D* _texture;
    
    //tile在texture的位置
    CCRect _textureRect;
    
    /**
     * 动画
     */
    CCAnimation* _animation;
    
    //所属的tileset.weak reference
    ISOTileset* _tileset;
    
    /**
     * 属性
     */
    CCDictionary* _properties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILE_H_
