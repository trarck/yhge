#ifndef YHGE_ANIMATION_CHARACTER_H_
#define YHGE_ANIMATION_CHARACTER_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "Resource.h"

NS_CC_YHGE_BEGIN

class Character:public Ref
{
    
public:
    
    Character();
    
    ~Character();
    
    virtual bool init();
    
    
public:
    
    inline void setId(int id)
    {
        m_id = id;
    }
    
    inline int getId()
    {
        return m_id;
    }
    
    inline void setResource(Resource* resource)
    {
        CC_SAFE_RETAIN(resource);
        CC_SAFE_RELEASE(m_resource);
        m_resource = resource;
    }
    
    inline Resource* getResource()
    {
        return m_resource;
    }
    
    inline void setAnchor(CCPoint anchor)
    {
        m_anchor = anchor;
    }
    
    inline CCPoint getAnchor()
    {
        return m_anchor;
    }

    
protected:
   
    int m_id;
    
    Resource* m_resource;
    
    CCPoint m_anchor;
    
};


NS_CC_YHGE_END

#endif //YHGE_ANIMATION_CHARACTER_H_