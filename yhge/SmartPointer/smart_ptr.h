#ifndef YHGE_SMARTPOINTER_SMART_PTR_H_
#define YHGE_SMARTPOINTER_SMART_PTR_H_

#include <yhge/YHGEMacros.h>
#include <cstdlib>

NS_CC_YHGE_BEGIN

namespace smart_ptr {

class RefCount
{
public:
    RefCount() : m_count(1)
    {
        
    }

    RefCount(int count)
    :m_count(count)
    {
        
    }
    
    ~RefCount()
    {
    }

    // increment use count
    int increase()
    {
        return ++m_count;
    }

    // decrement use count
    int decrease()
    {
        return m_count>0?--m_count:0;
    }

    // return use count
    int getCount() const
    {
        return m_count;
    }

    // return true if _Uses == 0
    bool expired() const
    {
        return getCount() == 0;
    }

private:
    int m_count;
};

//#if defined(WIN32) || defined(_WIN32)
//template <class T> class _NoAddRefReleaseOnComPtr : public T {
//private:
//    virtual unsigned long __stdcall AddRef(void) = 0;
//    virtual unsigned long __stdcall Release(void) = 0;
//};
//#endif  // defined(WIN32) || defined(_WIN32)

// base class for shared_ptr and weak_ptr
template<class T, bool is_strong , typename MemMgr>
class BasePtr
{
public:
    explicit BasePtr(T *p=0) : m_counter(NULL), m_ptr(p)
    {
        if (m_ptr) {
            m_counter = new RefCount(is_strong?1:0);
        }
    }

    BasePtr(const BasePtr& rhs) : m_counter(NULL), m_ptr(NULL)
    {
        acquire(rhs);
    }

    template<class Q, bool b,typename MemMgr2>
    BasePtr(const BasePtr<Q, b, MemMgr2> &rhs) : m_counter(NULL), m_ptr(NULL)
    {
        acquire(rhs);
    }

    virtual ~BasePtr()
    {
        release();
    }

    operator T*()   const    { return m_ptr; }
    T& operator*()  const    { return *m_ptr; }
//#if defined(WIN32) || defined(_WIN32)
//    _NoAddRefReleaseOnComPtr<T>* operator->() const  { return (_NoAddRefReleaseOnComPtr<T>*)m_ptr; }
//#else
    T* operator->() const    { return m_ptr; }
//#endif  // defined(WIN32) || defined(_WIN32)
    T* get()        const    { return m_ptr; }

    bool unique() const 
    { return (m_counter ? (1 == m_counter->getCount()) : true); }

    void reset(T *p=0)
    {
        BasePtr<T,is_strong, MemMgr> ptr(p);
        reset(ptr);
    }

    template <class Q, bool b, typename MemMgr2>
    void reset(const BasePtr<Q,b,MemMgr2> &rhs)
    {
        if ((void *)this != (void *)&rhs) {
            release();
            acquire(rhs);
        }
    }

    int useCount(void) const
    {
        return m_counter?m_counter->getCount():0;
    }

    // swap pointers
    template <class Q, bool b, typename MemMgr2>
    void swap(BasePtr<Q, b,MemMgr2> & rhs)
    {
        privateSwap(m_counter, rhs.m_counter);
        privateSwap(m_ptr, rhs.m_ptr);
    }

    BasePtr& operator=(const BasePtr &rhs)
    {
        reset(rhs);
        return *this;
    }

    template <class Q,bool b, typename MemMgr2>
    BasePtr& operator=(const BasePtr<Q,b,MemMgr2> &rhs)
    {
        reset(rhs);
        return *this;
    }

protected:

    template <typename TP1, typename TP2>
    static void privateSwap(TP1 &obj1, TP2 &obj2)
    {
        TP1 tmp = obj1;
        obj1 = static_cast<TP1>(obj2);
        obj2 = static_cast<TP2>(tmp);
    }

    template <class Q, bool b, typename MemMgr2>
    void acquire(const BasePtr<Q, b,MemMgr2> & rhs)
    {
        if (rhs.m_counter && rhs.m_counter->getCount()) {
            m_counter = rhs.m_counter;
            m_counter->increase();
            m_ptr = static_cast<T*>(rhs.m_ptr);
        }
    }

    // decrement the count, delete if it is 0
    void release(void)
    {
        if (m_counter) {
            if (0 == m_counter->decrease()) {
                MemMgr::deallocate(m_ptr);
                m_ptr = NULL;
            }

            if (0==m_counter->getCount()) {
                delete m_counter;
            }
            m_counter = NULL;
        }
        
        if (m_ptr) {
            m_ptr = NULL;
        }
    }

    template<class Q, bool b,typename MemMgr2> friend class BasePtr;
    
protected:
    RefCount *m_counter;
    T * m_ptr;
};

//////////////////////////////////////////////////////////////////////////
//
//   operator
//
template<class T,  bool bx, class Q, bool by, typename MemMgr1, typename MemMgr2>
bool operator<(const BasePtr<T, bx,MemMgr1> &lhs, const BasePtr<Q, by,MemMgr2> &rhs)
{
    // test if left pointer < right pointer
    return lhs.get() < rhs.get();
}

template <class T, typename MemMgr> class weak_ptr;

template<typename T>
class StdMemMgr {
public:
    static void deallocate(T *p) { delete p; }
    static T * allocate(void) { return new T(); }
    template<typename A1> static T * allocate(A1 const &a1) { return new T(a1); }
    template<typename A1, typename A2> static T * allocate(A1 const &a1, A2 const &a2) { return new T(a1, a2); }
    template<typename A1, typename A2, typename A3> static T * allocate(A1 const &a1, A2 const &a2, A3 const &a3) { return new T(a1, a2, a3); }
    template<typename A1, typename A2, typename A3, typename A4> static T * allocate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4) { return new T(a1, a2, a3, a4); }
    template<typename A1, typename A2, typename A3, typename A4, typename A5> static T * allocate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4, A5 const &a5) { return new T(a1, a2, a3, a4, a5); }
    template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6> static T * allocate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4, A5 const &a5, A6 const &a6) { return new T(a1, a2, a3, a4, a5, a6); }
};

template <class T, typename MemMgr=StdMemMgr<T> >
class shared_ptr : public BasePtr<T,true, MemMgr>
{
    typedef BasePtr<T, true,MemMgr> BaseClass;
public:
    explicit shared_ptr(T* p = 0) : BaseClass(p)
    {
    }

    shared_ptr(const shared_ptr& rhs) : BaseClass(rhs)
    {
    }

    template<class Q, typename MemMgr2> 
    shared_ptr(const shared_ptr<Q, MemMgr2> &rhs) : BaseClass(rhs)
    {
    }

    // construct shared_ptr object that owns resource *rhs
    template<class Q, typename MemMgr2> 
    explicit shared_ptr(const weak_ptr<Q, MemMgr2> &rhs) : BaseClass(rhs)
    {
    }

    ~shared_ptr()
    {
    }

    shared_ptr& operator=(const shared_ptr &rhs)
    {
        BaseClass::operator = (rhs);
        return *this;
    }

    template <class Q, typename MemMgr2> 
    shared_ptr& operator=(const shared_ptr<Q, MemMgr2> &rhs)
    {
        BaseClass::operator = (rhs);
        return *this;
    }

    template <class Q, typename MemMgr2>
    shared_ptr& operator=(const weak_ptr<Q, MemMgr2> &rhs)
    {
        BaseClass::operator = (rhs);
        return *this;
    }
};


template <class T, typename MemMgr=StdMemMgr<T> >
class weak_ptr : public BasePtr<T, false,MemMgr>
{
    typedef BasePtr<T, false,MemMgr> BaseClass;
public:
    // construct empty weak_ptr object
    weak_ptr()
    {

    }

    // construct weak_ptr object for resource owned by rhs
    template<class Q, typename MemMgr2>
    weak_ptr(const shared_ptr<Q, MemMgr2> &rhs) : BaseClass(rhs)
    {
    }

    // construct weak_ptr object for resource pointed to by rhs
    weak_ptr(const weak_ptr &rhs) : BaseClass(rhs)
    {
    }

    // construct weak_ptr object for resource pointed to by rhs
    template<class Q, typename MemMgr2>
    weak_ptr(const weak_ptr<Q, MemMgr2> &rhs) : BaseClass(rhs)
    {
    }

    ~weak_ptr()
    {
    }

    weak_ptr& operator=(const weak_ptr &rhs)
    {
        BaseClass::operator =(rhs);
        return *this;
    }

    template <class Q, typename MemMgr2>
    weak_ptr& operator=(const weak_ptr<Q, MemMgr2> &rhs)
    {
        BaseClass::operator = (rhs);
        return *this;
    }

    template <class Q, typename MemMgr2>
    weak_ptr& operator=(const shared_ptr<Q, MemMgr2> &rhs)
    {
        BaseClass::operator = (rhs);
        return *this;
    }

    // return true if resource no longer exists
    bool expired() const
    {
        return BaseClass::m_counter ? BaseClass::m_counter->expired() : true;
    }

    // convert to shared_ptr
    shared_ptr<T, MemMgr> lock() const
    {
        return shared_ptr<T, MemMgr>(*this);
    }
    
protected:
    
    void release(void)
    {
        if (BaseClass::m_counter) {
            BaseClass::m_counter->decrease();
        }
        
        if (BaseClass::m_ptr) {
            BaseClass::m_ptr = NULL;
        }
    }
    
private:
    operator T*()   const ;
    T& operator*()  const ;
    T* operator->() const ;
    T* get()        const ;
};


//////////////////////////////////////////////////////////////////////////
//
//   function MakeSharedPtr group
//

template <typename T, typename MemMgr=StdMemMgr<T> >
class MakeSharedPtr
{
public:
    typedef shared_ptr<T, MemMgr> pointer_type;

    static pointer_type generate(void)
    {
        return pointer_type ( MemMgr::allocate() );
    }

    template <typename A1>
    static pointer_type generate(A1 const &a1)
    {
        return pointer_type ( MemMgr::allocate(a1) );
    }

    template <typename A1, typename A2>
    static pointer_type generate(A1 const &a1, A2 const &a2)
    {
        return pointer_type ( MemMgr::allocate(a1, a2) );
    }

    template <typename A1, typename A2, typename A3>
    static pointer_type generate(A1 const &a1, A2 const &a2, A3 const &a3)
    {
        return pointer_type ( MemMgr::allocate(a1, a2, a3) );
    }

    template <typename A1, typename A2, typename A3, typename A4>
    static pointer_type generate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4)
    {
        return pointer_type ( MemMgr::allocate(a1, a2, a3, a4) );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5>
    static pointer_type generate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4, A5 const &a5)
    {
        return pointer_type ( MemMgr::allocate(a1, a2, a3, a4, a5) );
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static pointer_type generate(A1 const &a1, A2 const &a2, A3 const &a3, A4 const &a4, A5 const &a5, A6 const &a6)
    {
        return pointer_type ( MemMgr::allocate(a1, a2, a3, a4, a5, a6) );
    }
};

//////////////////////////////////////////////////////////////////////////
// COM pointer support
//

template<typename T>
class ComMemMgr {
public:
    static void deallocate(T *p) { p->Release(); }
    static T * allocate(T *p) { p->AddRef(); return p; }  // we must hold the AddRef-ed pointer
};

template <typename T>
shared_ptr<T, ComMemMgr<T> > make_com_shared_ptr(const T *rawPtr) {
    return MakeSharedPtr<T, ComMemMgr<T> >::template generate<T*>(const_cast<T * &>(rawPtr));
}


//////////////////////////////////////////////////////////////////////////
// auto-released array support
//

template<typename T>
class ArrayMemMgr {
public:
    static void deallocate(T *p) { delete []p; }
    static T * allocate(int n) { return new T[n]; }
};

template <class T, typename MemMgr=ArrayMemMgr<T> >
class shared_array : public BasePtr<T, true,MemMgr>
{
    typedef BasePtr<T, true,MemMgr> BaseClass;
public:
    explicit shared_array(T* p = 0) : BaseClass(p)
    {
    }

    shared_array(const shared_array& rhs) : BaseClass(rhs)
    {
    }

    template<class Q>
    shared_array(const shared_array<Q, MemMgr> &rhs) : BaseClass(rhs)
    {
    }

    ~shared_array()
    {
    }

    const T & operator[](int i) const
    {
        return BaseClass::get()[i];
    }

    T & operator[](int i)
    {
        return BaseClass::get()[i];
    }

    shared_array& operator=(const shared_array &rhs)
    {
        BaseClass::operator = (rhs);
        return *this;
    }

    template <class Q>
    shared_array& operator=(const shared_array<Q, MemMgr> &rhs)
    {
        BaseClass::operator = (rhs);
        return *this;
    }
private:
    T& operator*()  const ;
    T* operator->() const ;
};

//////////////////////////////////////////////////////////////////////////
// cocos2dx pointer support
//

template<typename T>
class Cocos2dxMemMgr {
public:
    static void deallocate(T *p) { p->release(); }
    static T * allocate(T *p) { p->retain(); return p; }  // we must hold the AddRef-ed pointer
};

template <typename T>
shared_ptr<T, Cocos2dxMemMgr<T> > make_cocos2dx_shared_ptr(const T *rawPtr) {
    return MakeSharedPtr<T, Cocos2dxMemMgr<T> >::template generate<T*>(const_cast<T * &>(rawPtr));
}

//////////////////////////////////////////////////////////////////////////
// define macros

// defining COM smart pointer type
#ifndef DEFINE_COM_SHARED_PTR
#define DEFINE_COM_SHARED_PTR(NAME_SPACE_T, TYPE) \
    typedef smart_ptr::shared_ptr<NAME_SPACE_T::TYPE, smart_ptr::ComMemMgr<NAME_SPACE_T::TYPE> > TYPE##ComPtr;
#endif  // DEFINE_COM_STRONG_PTR

// defining standard smart pointer type
#ifndef DEFINE_STD_SHARED_PTR
#define DEFINE_STD_SHARED_PTR(NAME_SPACE_T, TYPE) \
    typedef smart_ptr::shared_ptr<NAME_SPACE_T::TYPE, smart_ptr::StdMemMgr<NAME_SPACE_T::TYPE> > TYPE##StdPtr;
#endif  // DEFINE_STD_STRONG_PTR

// defining array style smart pointer type
#ifndef DEFINE_ARR_SHARED_PTR
#define DEFINE_ARR_SHARED_PTR(NAME_SPACE_T, TYPE) \
    typedef smart_ptr::shared_ptr<NAME_SPACE_T::TYPE, smart_ptr::ArrayMemMgr<NAME_SPACE_T::TYPE> > TYPE##ArrPtr;
#endif  // DEFINE_ARR_STRONG_PTR
    
// defining cocos2dx style smart pointer type
#ifndef DEFINE_COCOS2DX_SHARED_PTR
#define DEFINE_COCOS2DX_SHARED_PTR(NAME_SPACE_T, TYPE) \
typedef smart_ptr::shared_ptr<NAME_SPACE_T::TYPE, smart_ptr::Cocos2dxMemMgr<NAME_SPACE_T::TYPE> > TYPE##Cocos2dxPtr;
#endif  // DEFINE_ARR_STRONG_PTR


}; // namespace smart_ptr
NS_CC_YHGE_END

#endif // YHGE_SMARTPOINTER_SMART_PTR_H_
