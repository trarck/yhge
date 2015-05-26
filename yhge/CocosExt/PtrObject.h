#ifndef YHGE_COCOSEXT_PTROBJECT_H_
#define YHGE_COCOSEXT_PTROBJECT_H_

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
class PtrObject : public cocos2d::Ref
{
public:
	inline PtrObject()
    :_ptr(NULL)
	{
		
	}
	
    inline PtrObject(T* ptr)
    :_ptr(ptr)
    {
        
    }
    
    ~PtrObject(){
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
	
	inline static PtrObject* create(T* ptr)
	{
		PtrObject* pRet=new PtrObject(ptr);
		pRet->autorelease();
		return pRet;
	}
    
private:
    
    PtrObject(const PtrObject& other);
    
    PtrObject& operator= (const PtrObject& other);
    
	T* _ptr;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_PTROBJECT_H_
