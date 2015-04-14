#include "UpdateManager.h"
#include <yhge/Base/Log.h>

NS_CC_YHGE_BEGIN


UpdateManager::UpdateManager()
:_id(0)
,_updateList()
,_updateGroup()
,_paused(false)
,_updating(false)
{
    YHDEBUG("UpdateManager create");
}

UpdateManager::~UpdateManager()
{
    YHDEBUG("UpdateManager destroy");
    _updateList.clear();
    clearGroup();
}

bool UpdateManager::init(void)
{
    YHDEBUG("UpdateManager init");
    return true;
}

bool UpdateManager::init(int managerId)
{
    _id=managerId;
    return true;
}

void UpdateManager::update(float delta)
{
    if (_paused) {
        return;
    }
    
    _updating=true;
    for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
        if(!(*iter)->isMarkedForDeletion()){
            (*iter)->update(delta);
        }
    }
    _updating=false;
    
    //remove mark delete
    
    for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
        if((*iter)->isMarkedForDeletion()){
            iter=_updateList.erase(iter)-1;
        }
    }
}

void UpdateManager::addUpdater(Ref* target,SEL_SCHEDULE handle,int priority)
{
    UpdateHandler* updateHandler=new UpdateHandler(target,handle,priority);
    
    if (_updateList.size()==0) {
        _updateList.pushBack(updateHandler);
    }else{
        bool insered=false;
        for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
            if (priority<(*iter)->getPriority()) {
                //insert here
                _updateList.insert(iter, updateHandler);

                insered=true;
                
                break;
            }
        }
        
        if (!insered) {
            _updateList.pushBack(updateHandler);
        }
    }
    
    updateHandler->release();
}

void UpdateManager::removeUpdater(Ref* target)
{
    if (_updating) {
        for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
            if (target==(*iter)->getTarget()) {
                (*iter)->setMarkedForDeletion(true);
            }
        }
    }else{
        for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
            if (target==(*iter)->getTarget()) {
                iter=_updateList.erase(iter)-1;
            }
        }
    }
}

void UpdateManager::removeUpdater(Ref* target,SEL_SCHEDULE handle)
{
    if (_updating) {
        for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
            if (target==(*iter)->getTarget() && handle==(*iter)->getHandle()) {
                (*iter)->setMarkedForDeletion(true);
            }
        }
    }else{
        for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
            if (target==(*iter)->getTarget() && handle==(*iter)->getHandle()) {
                iter=_updateList.erase(iter)-1;
            }
        }
    }
}

void UpdateManager::removeUpdater(Ref* target,SEL_SCHEDULE handle,int priority)
{
    if (_updating) {
        for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
            if (target==(*iter)->getTarget() && handle==(*iter)->getHandle() && priority==(*iter)->getPriority()) {
                (*iter)->setMarkedForDeletion(true);
                break;
            }
        }
    }else{
        for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
            if (target==(*iter)->getTarget() && handle==(*iter)->getHandle() && priority==(*iter)->getPriority()) {
                _updateList.erase(iter);
                break;
            }
        }
    }
}

void UpdateManager::removeUpdaterByPriority(int priority)
{
    if (_updating) {
        for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
            if (priority==(*iter)->getPriority()) {
                (*iter)->setMarkedForDeletion(true);
            }
        }
    }else{
        for (UpdateList::iterator iter=_updateList.begin(); iter!=_updateList.end(); ++iter) {
            if (priority==(*iter)->getPriority()) {
                iter=_updateList.erase(iter)-1;
            }
        }
    }
}

UpdateManager* UpdateManager::createGroup(int groupId,int priority)
{
    UpdateManager* group=new UpdateManager();
    group->init(groupId);
    _updateGroup[groupId]=group;
    //_updateGroup should retain .
    
    //add to update list
    
    //retain by update list
    addUpdater(group, schedule_selector(UpdateManager::update), priority);
    
    //auto release
    return group;
}

UpdateManager* UpdateManager::getGroup(int groupId)
{
    UpdateManager* group=NULL;
    
    UpdateGroupMap::iterator iter=_updateGroup.find(groupId);
    if (iter!=_updateGroup.end()) {
        group=iter->second;
    }
    
    return group;
}

void UpdateManager::removeGroup(int groupId)
{
    UpdateGroupMap::iterator iter=_updateGroup.find(groupId);
    if (iter!=_updateGroup.end()) {
        //remove from updater
        removeUpdater(iter->second);
        iter->second->release();
        _updateGroup.erase(iter);
    }
}

void UpdateManager::addUpdaterToGroup(int groupId,Ref* target,SEL_SCHEDULE handle,int priority,int groupPriority)
{
    UpdateManager* group=getGroup(groupId);
    if (!group) {
        group=createGroup(groupId, groupPriority);
    }
    
    group->addUpdater(target, handle, priority);
}

void UpdateManager::removeUpdaterFromGroup(int groupId,Ref* target)
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
    for (UpdateGroupMap::iterator iter=_updateGroup.begin(); iter!=_updateGroup.end(); ++iter) {
        removeUpdater(iter->second);
        iter->second->release();
    }
    _updateGroup.clear();
}

NS_CC_YHGE_END
