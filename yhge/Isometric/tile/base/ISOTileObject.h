#ifndef YHGE_ISOMETRIC_ISOTileObject_H_
#define YHGE_ISOMETRIC_ISOTileObject_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ISOTileObjectPart.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 地图上要显示的对象
 * 如果对象大于一个格子，则要拆分成几个部分
 */
class ISOTileObject : public Ref{

public:
	typedef Vector<ISOTileObjectPart*> ISOTileObjectPartVector;

    ISOTileObject();   
  
    ~ISOTileObject();
   
    bool init();
    
public:
    
    inline const std::string& getName(){ return _name; }
    inline void setName(const std::string& name){ _name = name; }

	inline void setType(const std::string& type)
	{
		_type = type;
	}

	inline std::string& getType()
	{
		return _type;
	}

	inline void setPosition(Vec2 position)
	{
		_position = position;
	}

	inline Vec2 getPosition()
	{
		return _position;
	}

	void setSize(Size size)
	{
		_size = size;
	}

	inline Size getSize()
	{
		return _size;
	}

	inline void setGid(unsigned int gid)
	{
		_gid = gid;
	}

	inline unsigned int getGid()
	{
		return _gid;
	}

	inline void setVisible(bool visible)
	{
		_visible = visible;
	}

	inline bool getVisible()
	{
		return _visible;
	}
    
	inline void setParts(const ISOTileObjectPartVector& parts)
    {
        _parts = parts;
    }
    
	inline ISOTileObjectPartVector& getParts()
    {
        return _parts;
    }
    
	inline void setProperties(const ValueMap& properties)
	{
		_properties = properties;
	}

	inline ValueMap& getProperties()
	{
		return _properties;
	}
    
protected:
    
    /**
     * 对象的名称
     */
    std::string _name;
    
    /**
     * 对象的类型
     */
    std::string _type;
    
    /**
     * 对象的位置
     * 格子坐标
     */
    Vec2 _position;
    
    /**
     * 对象的大小
     */
    Size _size;
    
    /**
     * 对象的gid
     */
    unsigned int _gid;
    
    /**
     * 对象是否可见
     */
    bool _visible;
    
    /**
     * 组成部分
     */
	ISOTileObjectPartVector _parts;

    /**
     * 属性
     */
	ValueMap _properties;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOTileObject_H_
