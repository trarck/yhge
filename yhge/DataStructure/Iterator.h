#ifndef YH_DATASTRUCTURE_ITERATOR_H_
#define YH_DATASTRUCTURE_ITERATOR_H_

#include "DataStructureMacros.h"

NS_CC_YHGE_DATASTRUCTURE_BEGIN

/*************************************************
    Declaration of Class BaseIterator
*************************************************/
template <typename ElementType, typename PointerType, typename SeekStrategy>
class BaseIterator
{
    public:
        // Type Definition(s)
        typedef ElementType value_type;
        typedef PointerType pointer_type;
        typedef ptrdiff_t   difference_type;

        // Constructor(s) & Destructor(s)
        BaseIterator(pointer_type *pointer = NULL);
        //~BaseIterator(void);

        // Get Function(s)
        pointer_type    *location(void) const;

        // Coversion Operator(s)
        operator pointer_type *(void) const;

        // Arithmetic Operator(s)
        BaseIterator    operator+(difference_type n) const;
        BaseIterator    operator-(difference_type n) const;
        BaseIterator    &operator++(void);
        BaseIterator    &operator--(void);
        BaseIterator    operator++(int);
        BaseIterator    operator--(int);
        BaseIterator    &operator+=(difference_type n);
        BaseIterator    &operator-=(difference_type n);

        // Member Access Operator(s)
        value_type      &operator*(void) const;
        value_type      *operator->(void) const;

        // Relational Operator(s)
        bool            operator==(const BaseIterator &iter) const;
        bool            operator!=(const BaseIterator &iter) const;

    protected:
        // Data Member(s)
        pointer_type    *_pointer;
};

NS_CC_YHGE_DATASTRUCTURE_END

#include "Iterator-implement.h"

#endif // YH_DATASTRUCTURE_ITERATOR_H_
