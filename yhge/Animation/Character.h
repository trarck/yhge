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
        _id = id;
    }
    
    inline int getId()
    {
        return _id;
    }
    
    inline void setResource(Resource* resource)
    {
        CC_SAFE_RETAIN(resource);
        CC_SAFE_RELEASE(_resource);
        _resource = resource;
    }
    
    inline Resource* getResource()
    {
        return _resource;
    }
    
    inline void setAnchor(CCPoint anchor)
    {
        _anchor = anchor;
    }
    
    inline CCPoint getAnchor()
    {
        return _anchor;
    }

    
protected:
   
    int _id;
    
    Resource* _resource;
    
    CCPoint _anchor;
    
};


NS_CC_YHGE_END

#endif //YHGE_ANIMATION_CHARACTER_H_