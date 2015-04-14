#include "Scheduler.h"
#include <yhge/Base/Log.h>

NS_CC_YHGE_BEGIN


Scheduler::Scheduler()
:_updating(false)
{
    YHDEBUG("Scheduler create");
}

Scheduler::~Scheduler()
{
    YHDEBUG("Scheduler destroy");
    clear();
}

bool Scheduler::init(void)
{
    YHDEBUG("Scheduler init");
    return true;
}


/**
 * 消除更新列表
 */
void Scheduler::clear()
{
    //remove node
    TaskList::iterator iter;

    for (iter=_pUpdatesNegList.begin(); iter!=_pUpdatesNegList.end(); ++iter) {
        delete *iter;
    }
    
    for (iter=_pUpdatesZeroList.begin(); iter!=_pUpdatesZeroList.end(); ++iter) {
        delete *iter;
    }
    
    for (iter=_pUpdatesPosList.begin(); iter!=_pUpdatesPosList.end(); ++iter) {
        delete *iter;
    }
    
    _pUpdatesNegList.clear();
    _pUpdatesPosList.clear();
    _pUpdatesZeroList.clear();
}

void Scheduler::update(float delta)
{
    _updating=true;
    
    TaskList::iterator iter;
    SchedulerTask* task=NULL;

    for (iter=_pUpdatesNegList.begin(); iter!=_pUpdatesNegList.end(); ++iter) {
        task=*iter;
        if (!task->isMarkedForDeletion()) {
            (*iter)->update(delta);
        }
    }
    
    for (iter=_pUpdatesZeroList.begin(); iter!=_pUpdatesZeroList.end(); ++iter) {
        task=*iter;
        if (!task->isMarkedForDeletion()) {
            (*iter)->update(delta);
        }
    }
    
    for (iter=_pUpdatesPosList.begin(); iter!=_pUpdatesPosList.end(); ++iter) {
        task=*iter;
        if (!task->isMarkedForDeletion()) {
            (*iter)->update(delta);
        }
    }
    
    _updating=false;
    
    //remove marked for delete
    removeMarkedList(_pUpdatesNegList);
    removeMarkedList(_pUpdatesZeroList);
    removeMarkedList(_pUpdatesPosList);
    
}

void Scheduler::registerUpdate(Ref* target,SEL_SCHEDULE handle,int priority)
{
    CCAssert(target!=NULL, "[Scheduler::scheduleUpdate] target must not be null");
    
    //check target is registered
    if (_registerMap.find(target->_uID)!=_registerMap.end()) {
        //is registered do nothing
        return;
    }
    
    SchedulerTask* task=new SchedulerTask(target,handle,priority);
    
    if (priority==0) {
        //append to zero list
        
        _pUpdatesZeroList.push_back(task);
        
    }else if (priority>0){
        //insert to pos list
        insertToList(_pUpdatesPosList,task);
    }else{
        //insert to neg list
        insertToList(_pUpdatesNegList, task);
    }
    
    //record register priority
    _registerMap[target->_uID]=priority;
}

//void Scheduler::unregisterUpdate(Ref* target,int priority)
//{
//    if (priority==0) {
//        //remove from zero list
//        removeFromList(_pUpdatesZeroList, target);
//    }else if (priority>0){
//        //remove from pos list
//        removeFromList(_pUpdatesPosList, target);
//    }else{
//        //remove from neg list
//        removeFromList(_pUpdatesNegList, target);
//    }
//}

//void Scheduler::unregisterUpdate(Ref* target,SEL_SCHEDULE handle,int priority)
//{
//    if (priority==0) {
//        //remove from zero list
//        removeFromList(_pUpdatesZeroList, target, handle);
//    }else if (priority>0){
//        //remove from pos list
//        removeFromList(_pUpdatesPosList, target, handle);
//    }else{
//        //remove from neg list
//        removeFromList(_pUpdatesNegList, target, handle);
//    }
//}

//void Scheduler::unregisterUpdate(Ref* target,SEL_SCHEDULE handle)
//{
//    std::map<int, int>::iterator registerIter=_registerMap.find(target->_uID);
//    if (registerIter==_registerMap.end()) {
//        //not register do nothing
//        return;
//    }
//    
//    int priority=(*registerIter).second;
//    
//    if (priority==0) {
//        //remove from zero list
//        removeFromList(_pUpdatesZeroList, target, handle);
//    }else if (priority>0){
//        //remove from pos list
//        removeFromList(_pUpdatesPosList, target, handle);
//    }else{
//        //remove from neg list
//        removeFromList(_pUpdatesNegList, target, handle);
//    }
//}

void Scheduler::unregisterUpdate(Ref* target)
{
    std::map<int, int>::iterator registerIter=_registerMap.find(target->_uID);
    if (registerIter==_registerMap.end()) {
        //not register do nothing
        return;
    }
    
    int priority=(*registerIter).second;
    
    if (priority==0) {
        //remove from zero list
        removeFromList(_pUpdatesZeroList, target);
    }else if (priority>0){
        //remove from pos list
        removeFromList(_pUpdatesPosList, target);
    }else{
        //remove from neg list
        removeFromList(_pUpdatesNegList, target);
    }
}

void Scheduler::insertToList(TaskList& list,SchedulerTask* task)
{
    CCAssert(task!=NULL, "[Scheduler::insertToList] task must not be null");
    
    int taskPriority=task->getPriority();
    
    for (TaskList::iterator iter=list.begin(); iter!=list.end(); ++iter) {
        if (taskPriority<(*iter)->getPriority()) {
            
            //insert here
            
            list.insert(iter, task);
            
            return;
        }
    }
    
    list.push_back(task);
    
}

//void Scheduler::removeFromList(TaskList& list,Ref* target,SEL_SCHEDULE handle)
//{
//    CCAssert(target!=NULL, "[Scheduler::insertToList] target must not be null");
//    
//    
//    for (TaskList::Iterator iter=list.begin(); iter!=list.end(); ++iter) {
//        
//        if (target==(*iter)->getTarget() && handle==(*iter)->getHandle()) {
//            //remove here
//            
//            list.erase(iter);
//            
//            return;
//        }
//    }
//}

void Scheduler::removeFromList(TaskList& list,Ref* target)
{
    if (_updating){
        markRemoveFromList(list, target);
    }else{
        directRemoveFromList(list, target);
    }
}

void Scheduler::directRemoveFromList(TaskList& list,Ref* target)
{
    CCAssert(target!=NULL, "[Scheduler::insertToList] target must not be null");
    for (TaskList::iterator iter=list.begin(); iter!=list.end(); ++iter) {
        
        if (target==(*iter)->getTarget()) {
            //remove here
            
            //delete Task Object
            delete *iter;
            list.erase(iter);
            //because return ,not use iter any more
//            iter=list.erase(iter);
//            --iter;
            return;
        }
    }
}

void Scheduler::markRemoveFromList(TaskList& list,Ref* target)
{
    CCAssert(target!=NULL, "[Scheduler::insertToList] target must not be null");
    for (TaskList::iterator iter=list.begin(); iter!=list.end(); ++iter) {
        
        if (target==(*iter)->getTarget()) {
            //mark delete
            
            //delete Task Object
            (*iter)->setMarkedForDeletion(true);
            return;
        }
    }
}

void Scheduler::removeMarkedList(TaskList& list)
{
    for (TaskList::iterator iter=_pUpdatesNegList.begin(); iter!=_pUpdatesNegList.end(); ++iter) {
        if ((*iter)->isMarkedForDeletion()) {
            iter=list.erase(iter)-1;
        }
    }
}

NS_CC_YHGE_END
