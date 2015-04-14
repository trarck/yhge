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
class CCRef : public cocos2d::Ref
{
public:
	inline CCRef()
    :_ptr(NULL)
	{
		
	}
	
    inline CCRef(T* ptr)
    :_ptr(ptr)
    {
        
    }
    
    ~CCRef(){
        if (_ptr) {
            Deallocater::deallocate(_ptr);
            _ptr=NULL;
        }
    }
    
    inline void setPtr(T* ptr){
        _ptr=ptr;
    }
    
    T* getPtr()
    {
        return _ptr;
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
    
	T* _ptr;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCREF_H_
