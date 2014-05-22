#ifndef YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_
#define YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/CocosExt/Support/List.h>
#include <yhge/EntityComponent/Components/Component.h>
#include <yhge/DataStructure/LinkedList.h>

NS_CC_YHGE_BEGIN

class UpdateHandler:public CCObject
{
public:
    UpdateHandler()
    :m_target(NULL)
    ,m_handle(NULL)
    {
        
    }
    
    UpdateHandler(CCObject* target,SEL_SCHEDULE handle,int priority)
    :m_target(target)
    ,m_handle(handle)
    ,m_priority(priority)
    {
        CC_SAFE_RETAIN(target);
    }
    
    ~UpdateHandler()
    {
        CC_SAFE_RELEASE_NULL(m_target);
    }
    
    void update(float delta)
    {
        (m_target->*m_handle)(delta);
    }
    
public:
    
    inline void setTarget( CCObject* target)
    {
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE(m_target);
        m_target = target;
    }
    
    inline  CCObject* getTarget()
    {
        return m_target;
    }
    
    inline void setHandle( SEL_SCHEDULE handle)
    {
        m_handle = handle;
    }
    
    inline  SEL_SCHEDULE getHandle()
    {
        return m_handle;
    }
    
    inline void setPriority( int priority)
    {
        m_priority = priority;
    }
    
    inline  int getPriority()
    {
        return m_priority;
    }
    
protected:
    CCObject* m_target;
    SEL_SCHEDULE m_handle;
    int m_priority;
};


/**
 * 更新管理器
 * 负责组件的更新统一处理
 */
class UpdateManager : public CCObject
{
protected:
    
//    typedef ds::LinkedList<UpdateHandler*> UpdateList;
    typedef List<UpdateHandler*> UpdateList;
    typedef std::map<int, UpdateManager*> UpdateGroupMap;
public:
    
    UpdateManager();
    
    virtual ~UpdateManager();
    
    virtual bool init(void);
    
    virtual bool init(int managerId);
    
    inline bool empty()
    {
        return m_updateList.empty();
    }
    
    size_t size()
    {
        return m_updateList.size();
    }
    
    void update(float delta);
    
    /**
     * @brief 添加一个更新器
     */
    void addUpdater(CCObject* target,SEL_SCHEDULE handle,int priority);

    /**
     * @brief 移除一个更新器
     */
    void removeUpdater(CCObject* target);
    
    /**
     * @brief 按优先级移除一组更新器
     */
    void removeUpdaterByPriority(int priority);
    
    /**
     * @brief 创建一个更新器组
     */
    UpdateManager* createGroup(int groupId,int priority);
    
    /**
     * @brief 取得一个更新器组
     */
    UpdateManager* getGroup(int groupId);
    
    /**
     * @brief 删除一个更新器组
     */
    void removeGroup(int groupId);
    
    /**
     * @brief 添加一个更新器到一个组里
     */
    void addUpdaterToGroup(int groupId,CCObject* target,SEL_SCHEDULE handle,int priority);
    
    /**
     * @brief 从组里移除一个更新器
     */
    void removeUpdaterFromGroup(int groupId,CCObject* target);
    
    /**
     * @brief 按优先级从组里移除一组更新器
     */
    void removeUpdaterFromGroupByPriority(int groupId,int priority);

    /**
     * @brief 消除更新器组
     */
    void clearGroup();
    
public:
    
    inline void setId(int id)
    {
        m_id = id;
    }
    
    inline int getId()
    {
        return m_id;
    }

protected:
    
    int m_id;
    
    UpdateList m_updateList;
    
    UpdateGroupMap m_updateGroup;
    
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_
