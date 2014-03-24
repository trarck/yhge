#ifndef YHGE_COCOSEXT_CCREF_H_
#define YHGE_COCOSEXT_CCREF_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

template<typename T>
class RefObjectDeallocater {
public:
    static void deallocate(T *p) { delete p; }
};

template<typename T>
class RefArrayDeallocater {
public:
    static void deallocate(T *p) { delete[] p; }
};

/**
 * 普通指针包装成cocos object
 * 或者给普通指针一个ref count;
 */
template <class T,typename Deallocater= RefObjectDeallocater<T> >
class CCRef : public cocos2d::CCObject
{
public:
	inline CCRef()
    :m_ptr(NULL)
	{
		
	}
	
    inline CCRef(T* ptr)
    :m_ptr(ptr)
    {
        
    }
    
    ~CCRef(){
        if (m_ptr) {
            Deallocater::deallocate(m_ptr);
            m_ptr=NULL;
        }
    }
    
    inline void setPtr(T* ptr){
        m_ptr=ptr;
    }
    
    T* getPtr()
    {
        return m_ptr;
    }
	
	inline static CCRef* create(T* ptr)
	{
		CCRef* pRet=new CCRef(ptr);
		pRet->autorelease();
		return pRet;
	}
    
private:
    
    CCRef(const CCRef& other);
    
    CCRef& operator= (const CCRef& other);
    
	T* m_ptr;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCREF_H_
