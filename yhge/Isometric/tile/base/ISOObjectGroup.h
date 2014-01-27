#ifndef YHGE_ISOMETRIC_ISOOBJECTGROUP_H_
#define YHGE_ISOMETRIC_ISOOBJECTGROUP_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/**
 * 对象层数据
 * 保存对象层的数据。
 * 和ISOObjectGroupInfo的区别是info只保存数据，而这里会加入一些逻辑。
 */
class ISOObjectGroup : public CCObject
{

public:

    ISOObjectGroup();
    
    virtual ~ISOObjectGroup();

    bool init();
    
    inline const char* getName(){ return m_sName.c_str(); }
    inline void setName(const char *name){ m_sName = name; }

    /** return the value for the specific property name */
    CCString *propertyNamed(const char* propertyName);

    /** return the dictionary for the specific object name.
    It will return the 1st object found on the array for the given name.
    */
    CCDictionary* objectNamed(const char *objectName);
    
    //============get set===========//
    virtual void setOffset(const CCPoint& tOffset);
    
    virtual const CCPoint& getOffset();
    
    virtual void setProperties(CCDictionary* pProperties);
    
    virtual CCDictionary* getProperties();
    
    virtual void setObjects(CCArray* pObjects);
    
    virtual CCArray* getObjects();
    
    inline void setRenderIndex(int renderIndex)
    {
        m_renderIndex = renderIndex;
    }
    
    inline int getRenderIndex()
    {
        return m_renderIndex;
    }
    
protected:    
    /** name of the group */
    std::string m_sName;
    
    CCPoint m_tOffset;
    
    CCDictionary* m_pProperties;
    
    CCArray* m_pObjects;
    
    /**
     * 在地图文件中出现的顺序。
     * 如果要显示Object，则要保证ObjectLayer和TileLayer之间的显示顺序正确
     */
    int m_renderIndex;

};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOOBJECTGROUP_H_