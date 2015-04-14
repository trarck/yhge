#ifndef YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_
#define YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/CocosExt/Support/List.h>
#include <yhge/EntityComponent/Components/Component.h>
#include <yhge/DataStructure/LinkedList.h>
#include "ECManager.h"

NS_CC_YHGE_BEGIN

class UpdateHandler:public Ref
{
public:
    UpdateHandler()
    :_target(NULL)
    ,_handle(NULL)
    ,_priority(0)
    ,_markedForDeletion(false)
    {
        
    }
    
    UpdateHandler(Ref* target,SEL_SCHEDULE handle,int priority)
    :_target(target)
    ,_handle(handle)
    ,_priority(priority)
    ,_markedForDeletion(false)
    {
        CC_SAFE_RETAIN(target);
    }
    
    ~UpdateHandler()
    {
        CC_SAFE_RELEASE_NULL(_target);
    }
    
    void update(float delta)
    {
        (_target->*_handle)(delta);
    }
    
public:
    
    inline void setTarget( Ref* target)
    {
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE(_target);
        _target = target;
    }
    
    inline  Ref* getTarget()
    {
        return _target;
    }
    
    inline void setHandle( SEL_SCHEDULE handle)
    {
        _handle = handle;
    }
    
    inline  SEL_SCHEDULE getHandle()
    {
        return _handle;
    }
    
    inline void setPriority( int priority)
    {
        _priority = priority;
    }
    
    inline  int getPriority()
    {
        return _priority;
    }
    
    inline void setMarkedForDeletion(bool markedForDeletion)
    {
        _markedForDeletion = markedForDeletion;
    }
    
    inline bool isMarkedForDeletion()
    {
        return _markedForDeletion;
    }
    
protected:
    Ref* _target;
    SEL_SCHEDULE _handle;
    int _priority;
    bool _markedForDeletion;
};


/**
 * 更新管理器
 * 负责组件的更新统一处理
 */
class UpdateManager : public ECManager
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
        return _updateList.empty();
    }
    
    inline size_t size()
    {
        return _updateList.size();
    }
    
    virtual void update(float delta);
    
    /**
     * @brief 添加一个更新器
     */
    virtual void addUpdater(Ref* target,SEL_SCHEDULE handle,int priority);

    /**
     * @brief 移除一个更新器
     */
    virtual void removeUpdater(Ref* target);
    
    /**
     * @brief 移除一个更新器
     */
    virtual void removeUpdater(Ref* target,SEL_SCHEDULE handle);
    
    /**
     * @brief 移除一个更新器
     */
    virtual void removeUpdater(Ref* target,SEL_SCHEDULE handle,int priority);
    
    /**
     * @brief 按优先级移除一组更新器
     */
    virtual void removeUpdaterByPriority(int priority);
    
    /**
     * @brief 创建一个更新器组
     */
    virtual UpdateManager* createGroup(int groupId,int priority);
    
    /**
     * @brief 取得一个更新器组
     */
    virtual UpdateManager* getGroup(int groupId);
    
    /**
     * @brief 删除一个更新器组
     */
    virtual void removeGroup(int groupId);
    
    /**
     * @brief 添加一个更新器到一个组里
     */
    virtual void addUpdaterToGroup(int groupId,Ref* target,SEL_SCHEDULE handle,int priority,int groupPriority=0);
    
    /**
     * @brief 从组里移除一个更新器
     */
    virtual void removeUpdaterFromGroup(int groupId,Ref* target);
    
    /**
     * @brief 按优先级从组里移除一组更新器
     */
    virtual void removeUpdaterFromGroupByPriority(int groupId,int priority);

    /**
     * @brief 消除更新器组
     */
    virtual void clearGroup();
    
public:
    
    inline void setId(int id)
    {
        _id = id;
    }
    
    inline int getId()
    {
        return _id;
    }
    
    inline void setPaused(bool paused)
    {
        _paused = paused;
    }
    
    inline bool isPaused()
    {
        return _paused;
    }

protected:
    
    int _id;
    
    bool _updating;
    
    UpdateList _updateList;
    
    UpdateGroupMap _updateGroup;
    
    bool _paused;
    
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_MANAGERS_UPDATEMANAGER_H_
