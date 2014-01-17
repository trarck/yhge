//
//  ComponentEntity.h
//  GameComponents
//
//  Created by duanhouhai on 12-9-19.
//

#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_COMPONENTENTITYINTERFACE_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTSCCOMPONENTENTITYINTERFACE_H_

#include "cocos2d.h"

NS_CC_YHGE_BEGIN

class Component;

class ComponentEntityInterface
{
public:
    
    virtual Component* getComponent(const std::string& name)=0;
    virtual void addComponent(Component* component)=0;
    virtual void addComponent(Component* component,const std::string& name)=0;
    virtual void removeComponent(const std::string& name)=0;
    virtual void removeComponent(Component* component)=0;
    /**
     * 清除组件
     * 主要是注册的消息
     */
    virtual void cleanupComponents()=0;
};

NS_CC_YHGE_END


#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_COMPONENTENTITYINTERFACE_H_
