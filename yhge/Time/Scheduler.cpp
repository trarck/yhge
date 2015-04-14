#include "Scheduler.h"
#include <yhge/Base/Log.h>

NS_CC_YHGE_BEGIN


Scheduler::Scheduler()
:m_updating(false)
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

    for (iter=m_pUpdatesNegList.begin(); iter!=m_pUpdatesNegList.end(); ++iter) {
        delete *iter;
    }
    
    for (iter=m_pUpdatesZeroList.begin(); iter!=m_pUpdatesZeroList.end(); ++iter) {
        delete *iter;
    }
    
    for (iter=m_pUpdatesPosList.begin(); iter!=m_pUpdatesPosList.end(); ++iter) {
        delete *iter;
    }
    
    m_pUpdatesNegList.clear();
    m_pUpdatesPosList.clear();
    m_pUpdatesZeroList.clear();
}

void Scheduler::update(float delta)
{
    m_updating=true;
    
    TaskList::iterator iter;
    SchedulerTask* task=NULL;

    for (iter=m_pUpdatesNegList.begin(); iter!=m_pUpdatesNegList.end(); ++iter) {
        task=*iter;
        if (!task->isMarkedForDeletion()) {
            (*iter)->update(delta);
        }
    }
    
    for (iter=m_pUpdatesZeroList.begin(); iter!=m_pUpdatesZeroList.end(); ++iter) {
        task=*iter;
        if (!task->isMarkedForDeletion()) {
            (*iter)->update(delta);
        }
    }
    
    for (iter=m_pUpdatesPosList.begin(); iter!=m_pUpdatesPosList.end(); ++iter) {
        task=*iter;
        if (!task->isMarkedForDeletion()) {
            (*iter)->update(delta);
        }
    }
    
    m_updating=false;
    
    //remove marked for delete
    removeMarkedList(m_pUpdatesNegList);
    removeMarkedList(m_pUpdatesZeroList);
    removeMarkedList(m_pUpdatesPosList);
    
}

void Scheduler::registerUpdate(Ref* target,SEL_SCHEDULE handle,int priority)
{
    CCAssert(target!=NULL, "[Scheduler::scheduleUpdate] target must not be null");
    
    //check target is registered
    if (m_registerMap.find(target->m_uID)!=m_registerMap.end()) {
        //is registered do nothing
        return;
    }
    
    SchedulerTask* task=new SchedulerTask(target,handle,priority);
    
    if (priority==0) {
        //append to zero list
        
        m_pUpdatesZeroList.push_back(task);
        
    }else if (priority>0){
        //insert to pos list
        insertToList(m_pUpdatesPosList,task);
    }else{
        //insert to neg list
        insertToList(m_pUpdatesNegList, task);
    }
    
    //record register priority
    m_registerMap[target->m_uID]=priority;
}

//void Scheduler::unregisterUpdate(Ref* target,int priority)
//{
//    if (priority==0) {
//        //remove from zero list
//        removeFromList(m_pUpdatesZeroList, target);
//    }else if (priority>0){
//        //remove from pos list
//        removeFromList(m_pUpdatesPosList, target);
//    }else{
//        //remove from neg list
//        removeFromList(m_pUpdatesNegList, target);
//    }
//}

//void Scheduler::unregisterUpdate(Ref* target,SEL_SCHEDULE handle,int priority)
//{
//    if (priority==0) {
//        //remove from zero list
//        removeFromList(m_pUpdatesZeroList, target, handle);
//    }else if (priority>0){
//        //remove from pos list
//        removeFromList(m_pUpdatesPosList, target, handle);
//    }else{
//        //remove from neg list
//        removeFromList(m_pUpdatesNegList, target, handle);
//    }
//}

//void Scheduler::unregisterUpdate(Ref* target,SEL_SCHEDULE handle)
//{
//    std::map<int, int>::iterator registerIter=m_registerMap.find(target->m_uID);
//    if (registerIter==m_registerMap.end()) {
//        //not register do nothing
//        return;
//    }
//    
//    int priority=(*registerIter).second;
//    
//    if (priority==0) {
//        //remove from zero list
//        removeFromList(m_pUpdatesZeroList, target, handle);
//    }else if (priority>0){
//        //remove from pos list
//        removeFromList(m_pUpdatesPosList, target, handle);
//    }else{
//        //remove from neg list
//        removeFromList(m_pUpdatesNegList, target, handle);
//    }
//}

void Scheduler::unregisterUpdate(Ref* target)
{
    std::map<int, int>::iterator registerIter=m_registerMap.find(target->m_uID);
    if (registerIter==m_registerMap.end()) {
        //not register do nothing
        return;
    }
    
    int priority=(*registerIter).second;
    
    if (priority==0) {
        //remove from zero list
        removeFromList(m_pUpdatesZeroList, target);
    }else if (priority>0){
        //remove from pos list
        removeFromList(m_pUpdatesPosList, target);
    }else{
        //remove from neg list
        removeFromList(m_pUpdatesNegList, target);
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
    if (m_updating){
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
    for (TaskList::iterator iter=m_pUpdatesNegList.begin(); iter!=m_pUpdatesNegList.end(); ++iter) {
        if ((*iter)->isMarkedForDeletion()) {
            iter=list.erase(iter)-1;
        }
    }
}

NS_CC_YHGE_END
