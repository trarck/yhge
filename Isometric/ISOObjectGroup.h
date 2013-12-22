#ifndef YHGE_ISOMETRIC_ISOOBJECTGROUP_H_
#define YHGE_ISOMETRIC_ISOOBJECTGROUP_H_

#include "cocos2d.h"
#include "YHGEMacros.h"
#include "cocoa/CCGeometry.h"
#include "cocoa/CCString.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCDictionary.h"

NS_CC_YHGE_BEGIN

/**
 * object layer 对象层
 * 只记录该层的对象信息，对于其它格子信息不做记录。
 * 对象包含出现在地图上的坐标和大小等信息，使用字典来记录。
 * 通常坐为中间层，显示人物，怪物，一些做为背景动态的东西，如动态水面，地上的火焰。
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
    
protected:    
    /** name of the group */
    std::string m_sName;
    
    CCPoint m_tOffset;
    
    CCDictionary* m_pProperties;
    
    CCArray* m_pObjects;

};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_ISOOBJECTGROUP_H_