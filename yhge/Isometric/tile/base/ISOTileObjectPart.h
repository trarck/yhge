#ifndef YHGE_ISOMETRIC_ISOTILEOBJECTPART_H_
#define YHGE_ISOMETRIC_ISOTILEOBJECTPART_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * tile对象的组成部分
 * tile对象的组成分为绝对和相对
 * 绝对:组成部分直接添加到map中，使用map坐标系统，没有具体的对象。
 * 相对:组成部分添加到对象渲染树中，再把对象添加到map中，组成部分使用局部坐标系。
 */
class ISOTileObjectPart : public Ref{

public:
    
    ISOTileObjectPart();   
  
    ~ISOTileObjectPart();
    
public:
    
    inline void setId(int id)
    {
        _id = id;
    }
    
    inline int getId()
    {
        return _id;
    }
    
    inline void setPosition(const CCPoint& position)
    {
        _position = position;
    }
    
    inline const CCPoint& getPosition()
    {
        return _position;
    }
    
    inline void setSize(const CCSize& size)
    {
        _size = size;
    }
    
    inline const CCSize& getSize()
    {
        return _size;
    }
    
    inline void setObjectId(int objectId)
    {
        _objectId = objectId;
    }
    
    inline int getObjectId()
    {
        return _objectId;
    }
    
    inline void setGid(int gid)
    {
        _gid = gid;
    }
    
    inline int getGid()
    {
        return _gid;
    }
    
protected:
    
    /**
     * 对象组成部分的Id
     * 用于标识哪个部分
     */
    int _id;
    
    /**
     * 对象组成部分的位置
     * 根据对象的渲染方式决定坐标系
     */
    CCPoint _position;
    
    /**
     * 对象组成部分的大小
     */
    CCSize _size;
    
    /**
     * 所属对象的Id
     */
    int _objectId;
   
    /**
     * 组成部分的全局gid
     */
    int _gid;

};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTILEOBJECTPART_H_
