//
//  ComponentEntity.h
//  GameComponents
//
//  Created by duanhouhai on 12-9-19.
//

#ifndef YHGE_COMPONENTS_COMPONENTENTITYINTERFACE_H_
#define YHGE_COMPONENTSCCOMPONENTENTITYINTERFACE_H_

#include "cocos2d.h"
#include "Component.h"


NS_CC_YHGE_BEGIN

class ComponentEntityInterface
{
public:
    
    virtual void setupComponents();
    
    void addComponent(Component* component);
    void addComponent(Component* component,const char* name);
};

NS_CC_YHGE_END


#endif //YHGE_COMPONENTS_COMPONENTENTITYINTERFACE_H_
