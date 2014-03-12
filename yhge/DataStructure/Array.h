#ifndef YHGE_DATASTRUCTURE_ARRAY_H_
#define YHGE_DATASTRUCTURE_ARRAY_H_

#include <stddef.h>
#include "DataStructureMacros.h"

NS_CC_YHGE_DATASTRUCTURE_BEGIN

template<typename T>
class StdRefCount {
public:
    static void release(T *p) {  }
    static void retain(T *p) { }
};

template<typename T>
class Cocos2dRefCount {
public:
    static void release(T *p) { p->release(); }
    static void retain(T *p) { p->retain();}
};

template <class T,typename RefCountMgr=Cocos2dRefCount<T> >
class Array
{
public:
	
    Array(int num)
    :m_num(num)
    {
        m_data=new T*[num];
        
        init();
    }
    
    ~Array()
    {
        cleanup();
        delete[] m_data;
    }
    
    void set(int index,T* value)
    {
        CCAssert(index>=0 && index<m_num,"out index");
        if(m_data[index])
            RefCountMgr::release(m_data[index]);
        
        m_data[index]=value;
        
        if (value) {
            RefCountMgr::retain(value);
        }
    }
    
    T* get(int index)
    {
        CCAssert(index>=0 && index<m_num,"out index");
        
        return m_data[index];
    }
    
    void init()
    {
        for (int i=0; i<m_num; ++i) {
            m_data[i]=NULL;
        }
    }
    
    void cleanup()
    {
        for (int i=0; i<m_num; ++i) {
            if(m_data[i])
                RefCountMgr::release(m_data[i]);
        }
    }
    
    inline void setNum(int num)
    {
        m_num = num;
    }
    
    inline int getNum()
    {
        return m_num;
    }
    
protected:
    
    T* * m_data;
    
    int m_num;
//    int m_max;
};

template <class T,typename RefCountMgr=Cocos2dRefCount<T> >
class TwoDimArray:public Array<T,RefCountMgr>
{
public:
    typedef Array<T,RefCountMgr> ParentClass;
   
    
    TwoDimArray(int col,int row)
    :m_col(col)
    ,m_row(row)
    ,ParentClass(col*row)
    {
        
    }
    
    void set(int col,int row,T* value)
    {
        CCAssert(col>=0 && col<m_col,"col out index");
        CCAssert(row>=0 && row<m_row,"row out index");
        
        int index=row*m_col+col;
        
        ParentClass::set(index,value);
    }
    
    T* get(int col,int row)
    {
        CCAssert(col>=0 && col<m_col,"col out index");
        CCAssert(row>=0 && row<m_row,"row out index");
        
        int index=row*m_col+col;
        return ParentClass::get(index);
    }
    
    inline void setRow(int row)
    {
        m_row = row;
    }
    
    inline int getRow()
    {
        return m_row;
    }
    
    inline void setCol(int col)
    {
        m_col = col;
    }
    
    inline int getCol()
    {
        return m_col;
    }
protected:
    
    int m_row;
    
    int m_col;

};

NS_CC_YHGE_DATASTRUCTURE_END

#endif // YHGE_DATASTRUCTURE_ARRAY_H_
