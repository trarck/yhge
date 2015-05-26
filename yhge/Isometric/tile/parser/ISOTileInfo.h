﻿#ifndef YHGE_ISOMETRIC_ISOTILEINFO_H_
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
        _sImageSource = pImageSource;
    }
    
    inline const char * getImageSource()
    {
        return _sImageSource.c_str();
    }
    
    inline void setImageSize(Size& tImageSize)
    {
        _tImageSize = tImageSize;
    }
    
    inline Size& getImageSize()
    {
        return _tImageSize;
    }
    
    inline void setProperties(CCDictionary* pProperties)
    {
        CC_SAFE_RETAIN(pProperties);
        CC_SAFE_RELEASE(_properties);
        _properties = pProperties;
    }
    
    inline CCDictionary* getProperties()
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
    std::string _sImageSource;
    
    /**
     * 图像大小。像素大小
     */
    Size _tImageSize;
    
    /**
     * 格子扩展属性
     */
    CCDictionary* _properties;
    

};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILEINFO_H_
