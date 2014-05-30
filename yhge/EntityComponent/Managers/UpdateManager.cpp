#include "UpdateManager.h"
#include <yhge/Base/Log.h>

NS_CC_YHGE_BEGIN


UpdateManager::UpdateManager()
:m_id(0)
,m_updateList()
,m_updateGroup()
{
    YHDEBUG("UpdateManager create");
}

UpdateManager::~UpdateManager()
{
    YHDEBUG("UpdateManager destroy");
    m_updateList.clear();
    clearGroup();
}

bool UpdateManager::init(void)
{
    YHDEBUG("UpdateManager init");
    return true;
}

bool UpdateManager::init(int managerId)
{
    m_id=managerId;
    return true;
}

void UpdateManager::update(float delta)
{
    for (UpdateList::iterator iter=m_updateList.begin(); iter!=m_updateList.end(); ++iter) {
        (*iter)->update(delta);
    }
}

void UpdateManager::addUpdater(CCObject* target,SEL_SCHEDULE handle,int priority)
{
    for (UpdateList::iterator iter=m_updateList.begin(); iter!=m_updateList.end(); ++iter) {
        if (priority<(*iter)->getPriority()) {
            //insert here
            UpdateHandler* updateHandler=new UpdateHandler(target,handle,priority);
            
            m_updateList.insert(iter, updateHandler);

            updateHandler->release();
            
            break;
        }
    }
}

void UpdateManager::removeUpdater(CCObject* target)
{
    for (UpdateList::iterator iter=m_updateList.begin(); iter!=m_updateList.end(); ++iter) {
        if (target==(*iter)->getTarget()) {
            m_updateList.erase(iter);
            break;
        }
    }
}

void UpdateManager::removeUpdaterByPriority(int priority)
{
    for (UpdateList::iterator iter=m_updateList.begin(); iter!=m_updateList.end(); ++iter) {
        if (priority==(*iter)->getPriority()) {
            m_updateList.erase(iter);
        }
    }
}

UpdateManager* UpdateManager::createGroup(int groupId,int priority)
{
    UpdateManager* group=new UpdateManager();
    group->init(groupId);
    m_updateGroup[groupId]=group;
    //m_updateGroup should retain .
    
    //add to update list
    
    //retain by update list
    addUpdater(group, schedule_selector(UpdateHandler::update), priority);
    
    //auto release
    return group;
}

UpdateManager* UpdateManager::getGroup(int groupId)
{
    UpdateManager* group=NULL;
    
    UpdateGroupMap::iterator iter=m_updateGroup.find(groupId);
    if (iter!=m_updateGroup.end()) {
        group=iter->second;
    }
    
    return group;
}

void UpdateManager::removeGroup(int groupId)
{
    UpdateGroupMap::iterator iter=m_updateGroup.find(groupId);
    if (iter!=m_updateGroup.end()) {
        iter->second->release();
        m_updateGroup.erase(iter);
    }
}

void UpdateManager::addUpdaterToGroup(int groupId,CCObject* target,SEL_SCHEDULE handle,int priority)
{
    UpdateManager* group=getGroup(groupId);
    if (!group) {
        group=createGroup(groupId, priority);
    }
    
    group->addUpdater(target, handle, priority);
}

void UpdateManager::removeUpdaterFromGroup(int groupId,CCObject* target)
{
    UpdateManager* group=getGroup(groupId);
    
    if (group) {
        group->removeUpdater(target);
        
        //remove empty group
        if (group->empty()) {
            removeGroup(groupId);
        }
    }
}

void UpdateManager::removeUpdaterFromGroupByPriority(int groupId,int priority)
{
    UpdateManager* group=getGroup(groupId);
    if (group) {
        group->removeUpdaterByPriority(priority);
        
        //remove empty group
        if (group->empty()) {
            removeGroup(groupId);
        }
    }
}

void UpdateManager::clearGroup()
{
    for (UpdateGroupMap::iterator iter=m_updateGroup.begin(); iter!=m_updateGroup.end(); ++iter) {
        iter->second->release();
    }
    m_updateGroup.clear();
}

NS_CC_YHGE_END