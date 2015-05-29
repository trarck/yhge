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
    
    bool init(int id,ISOTileset* tileset,Texture2D* texture);
    
    bool init(int id,ISOTileset* tileset,CCTexture2D* texture,CCRect& textureRect);
   
    Size size(){return _textureRect.size;}

public:
    
    virtual int getGId();
    
    
	inline void setId(int id)
	{
		_id = id;
	}

	inline int getId()
	{
		return _id;
	}
    
	inline void setTileset(ISOTileset* tileset)
	{
		_tileset = tileset;
	}

	inline ISOTileset* getTileset()
	{
		return _tileset;
	}
    
	inline void setProperties(const ValueMap& properties)
	{
		_properties = properties;
	}

	inline ValueMap& getProperties()
	{
		return _properties;
	}

    inline void setTexture(Texture2D* texture)
    {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(_texture);
        _texture = texture;
    }
    
    inline Texture2D* getTexture()
    {
        return _texture;
    }
    
    inline void setTextureRect(Rect& textureRect)
    {
        _textureRect = textureRect;
    }
    
    inline CCRect& getextureRect()
    {
        return _textureRect;
    }
    
    inline void setAnimation(Animation* animation)
    {
        CC_SAFE_RETAIN(animation);
        CC_SAFE_RELEASE(_animation);
        _animation = animation;
    }
    
    inline Animation* getAnimation()
    {
        return _animation;
    }
    
protected:
    
    //id
    int _id;
    
    //支持tile大小不同
    Texture2D* _texture;
    
    //tile在texture的位置
    Rect _textureRect;
    
    /**
     * 动画
     */
    Animation* _animation;
    
    //所属的tileset.weak reference
    ISOTileset* _tileset;
    
    /**
     * 属性
     */
	ValueMap _properties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILE_H_
