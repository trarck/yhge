#ifndef YHGE_ISOMETRIC_ISOTileObject_H_
#define YHGE_ISOMETRIC_ISOTileObject_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 地图上要显示的对象
 * 如果对象大于一个格子，则要拆分成几个部分
 */
class ISOTileObject : public Ref{

public:
    
    ISOTileObject();   
  
    ~ISOTileObject();
   
    bool init();
    
public:
    
    inline const char* getName(){ return _sName.c_str(); }
    inline void setName(const char *name){ _sName = name; }
    
    virtual void setType(const char *pType);
    virtual std::string& getType();
    
    virtual void setPosition(CCPoint tPosition);
    virtual CCPoint getPosition();
    
    virtual void setSize(CCSize tSize);
    virtual CCSize getSize();
    
    virtual void setGid(unsigned int uGid);
    virtual unsigned int getGid();
    
    virtual void setVisible(bool bVisible);
    virtual bool getVisible();
    
    inline void setParts(CCArray* pParts)
    {
        CC_SAFE_RETAIN(pParts);
        CC_SAFE_RELEASE(_pParts);
        _pParts = pParts;
    }
    
    inline CCArray* getParts()
    {
        return _pParts;
    }
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
protected:
    
    /**
     * 对象的名称
     */
    std::string _sName;
    
    /**
     * 对象的类型
     */
    std::string _sType;
    
    /**
     * 对象的位置
     * 格子坐标
     */
    CCPoint _tPosition;
    
    /**
     * 对象的大小
     */
    CCSize _tSize;
    
    /**
     * 对象的gid
     */
    unsigned int _uGid;
    
    /**
     * 对象是否可见
     */
    bool _bVisible;
    
    /**
     * 组成部分
     */
    CCArray* _pParts;

    /**
     * 属性
     */
    CCDictionary* _pProperties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTileObject_H_
