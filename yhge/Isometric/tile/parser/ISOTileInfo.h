#ifndef YHGE_ISOMETRIC_ISOTILEINFO_H_
#define YHGE_ISOMETRIC_ISOTILEINFO_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 格子信息
 */
class ISOTileInfo : public Ref{

public:
    
    ISOTileInfo();
    
    ~ISOTileInfo();

    
public:
           
    inline void setId(unsigned int uId)
    {
        _uId = uId;
    }
    
    inline unsigned int getId()
    {
        return _uId;
    }

    inline void setImageSource(const char * pImageSource)
    {
        _imageSource = pImageSource;
    }
    
    inline const char * getImageSource()
    {
        return _imageSource.c_str();
    }
    
    inline void setImageSize(Size& imageSize)
    {
        _imageSize = imageSize;
    }
    
    inline Size& getImageSize()
    {
        return _imageSize;
    }
    
	inline void setProperties(const ValueMap& pProperties)
    {
        _properties = pProperties;
    }
    
	inline ValueMap& getProperties()
    {
        return _properties;
    }
    
protected:
    /**
     * 格子id
     */
    unsigned int _uId;
    
    /**
     * 图像路径
     */
    std::string _imageSource;
    
    /**
     * 图像大小。像素大小
     */
    Size _imageSize;
    
    /**
     * 格子扩展属性
     */
	ValueMap _properties;
    

};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILEINFO_H_
