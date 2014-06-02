#ifndef YHGE_COCOSEXT_SUPPORT_LIST_H_
#define YHGE_COCOSEXT_SUPPORT_LIST_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/DataStructure/LinkedList.h>

NS_CC_YHGE_BEGIN

template<class T>
class List
{
protected:
    typedef ds::LinkedList<T> ObjectList;
public:
    typedef typename ds::LinkedList<T>::Iterator iterator;
    typedef size_t      size_type;
    
    
    iterator begin(){return m_data.begin();}
    iterator end(){return m_data.end();}
    
    iterator rbegin(){return m_data.rbegin();}
    iterator rend(){return m_data.rend();}
    
    List<T>()
    :m_data()
    {
        
    }
    
    ~List<T>()
    {
        
    }
    
    List<T>(const List<T>& other)
    {
        m_data=other.m_data;
        addRefForAllObjects();
    }
    
    List<T>& operator=(const List<T>& other)
    {
        if (this != &other) {
            clear();
            m_data = other.m_data;
            addRefForAllObjects();
        }
        return *this;
    }
    
    bool empty() const
    {
        return m_data.empty();
    }
    
    size_type size() const
    {
        return m_data.size();
    }
    
    size_type maxSize() const
    {
        return m_data.max_size();
    }
    
    iterator find(T value)
    {
        iterator iter = m_data.begin();
        while (iter != m_data.end())
        {
            iterator position = iter++;
            if ((*position)==value)
            {
                return iter;
            }
        }
        return m_data.end();
    }
    
    T front() const
    {
        return m_data.front();
    }
    
    T back() const
    {
        return m_data.back();
    }
    
    void pushBack(T value)
    {
        CCASSERT(value != NULL, "The object should not be NULL");
        m_data.push_back(value);
        value->retain();
    }
    
    void pushBack(const ds::LinkedList<T>& other)
    {
        for(iterator iter=other.begin();iter!=other.end;++iter) {
            m_data.push_back((*iter));
            (*iter)->retain();
        }
    }
    
    void popFront()
    {
        iterator front=m_data.front();
        m_data.pop_front();
        front->release();
    }
    
    void popBack()
    {
        iterator last=m_data.back();
        m_data.pop_back();
        last->release();
    }
    
    
    void insert(iterator position,T value)
    {
        m_data.insert(position,value);
        value->retain();
    }
    
    void insert(iterator position, size_type number, T value)
    {
        m_data.insert(position,number,value);
        for (int i=0; i<number; ++i) {
            value->retain();
        }
    }
    
    iterator erase(iterator position)
    {
        (*position)->release();
        return m_data.erase(position);
    }
    
    iterator erase(iterator first,iterator last)
    {
        for (iterator iter = first; iter != last; ++iter)
        {
            (*iter)->release();
        }
        
        return m_data.erase(first, last);
    }
    
    void remove(T value, bool toRelease = true)
    {
        CCASSERT(value != NULL, "The object should not be NULL");
        m_data.remove(value);
        if(toRelease)
            value->release();
    }
    
    void clear()
    {
        for( iterator it = m_data.begin(); it != m_data.end(); ++it ) {
            (*it)->release();
        }
        m_data.clear();
    }
    
    void reverse()
    {
        m_data.reverse();
    }
    
    ObjectList getData()
    {
        return m_data;
    }

protected:
    
    void addRefForAllObjects()
    {
        for(iterator iter=m_data.begin();iter!=m_data.end();++iter) {
            (*iter)->retain();
        }
    }
    
    ObjectList m_data;
    
};

NS_CC_YHGE_END


#endif /* defined(YHGE_COCOSEXT_SUPPORT_LIST_H_) */
