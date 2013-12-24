#ifndef YHGE_COCOSEXT_CCSCOPEPTR_H_
#define YHGE_COCOSEXT_CCSCOPEPTR_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

/**
 * 对指针进行封装，可以用于CCArray,CCDictionay中等。
 * 类似 boost的auto
 */
template <class T>
class CCScopePtr : public cocos2d::CCObject
{
public:
	inline CCScopePtr()
    :m_ptr(NULL)
	{
		
	}
	
    inline CCScopePtr(T* ptr)
    :m_ptr(ptr)
    {
        
    }
    
    ~CCScopePtr(){
        CCLOG("ccscope destry");
        CC_SAFE_DELETE(m_ptr);
        m_ptr=NULL;
    }
    
    inline void setPtr(T* ptr){
        m_ptr=ptr;
    }
    
    T* getPtr()
    {
        return m_ptr;
    }
	
	inline static CCScopePtr* create(T* ptr)
	{
		CCScopePtr* pRet=new CCScopePtr(ptr);
		pRet->autorelease();
		return pRet;
	}
    
private:
    
    CCScopePtr(const CCScopePtr& other){};
    
    CCScopePtr& operator= (const CCScopePtr& other){return *this;};
    
	T* m_ptr;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_CCSCOPEPTR_H_
