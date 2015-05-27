#ifndef YHGE_ISOMETRIC_ISOOBJECTGROUP_H_
#define YHGE_ISOMETRIC_ISOOBJECTGROUP_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>

NS_CC_YHGE_ISOMETRIC_BEGIN

/**
 * 对象层数据
 * 保存对象层的数据。
 * 和ISOObjectGroupInfo的区别是info只保存数据，而这里会加入一些逻辑。
 */
class ISOObjectGroup : public Ref
{

public:

    ISOObjectGroup();
    
    virtual ~ISOObjectGroup();

    bool init();
    
    inline const std::string& getName(){ return _name; }
    inline void setName(const std::string& name){ _name = name; }

    /** return the value for the specific property name */
	Value getProperty(const std::string& propertyName);

    /** return the dictionary for the specific object name.
    It will return the 1st object found on the array for the given name.
    */
    CCDictionary* objectNamed(const std::string& objectName);
    
    //============get set===========//
    virtual void seoffset(const Vec2& offset);
    
    virtual const Vec2& geoffset();
    
    virtual void setProperties(CCDictionary* pProperties);
    
    virtual CCDictionary* getProperties();
    
    virtual void setObjects(CCArray* objects);
    
    virtual CCArray* getObjects();
    
    inline void setRenderIndex(int renderIndex)
    {
        _renderIndex = renderIndex;
    }
    
    inline int getRenderIndex()
    {
        return _renderIndex;
    }
    
protected:    
    /** name of the group */
    std::string _name;
    
    Vec2 _offset;
    
    ValueMap _properties;
    
    CCArray* _objects;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int _renderIndex;

};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ISOOBJECTGROUP_H_