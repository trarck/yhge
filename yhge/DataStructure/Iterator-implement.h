#ifndef YH_DATASTRUCTURE_ITERATOR_IMPLEMENT_H_
#define YH_DATASTRUCTURE_ITERATOR_IMPLEMENT_H_

#include "Iterator.h"

NS_CC_YHGE_DATASTRUCTURE_BEGIN

/*************************************************
    Implement of Class BaseIterator
*************************************************/
template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>::BaseIterator(pointer_type *pointer)
    : _pointer(pointer)
{
    // do nothing
}
/*
template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>::~BaseIterator(void)
{
    // do nothing
}
*/
template <typename ElementType, typename PointerType, typename SeekStrategy>
PointerType *BaseIterator<ElementType, PointerType, SeekStrategy>::location(void) const
{
    return _pointer;
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>::operator PointerType *(void) const
{
    return _pointer;
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>::operator+(difference_type n) const
{
    BaseIterator iter(*this);
    if (n > 0)  { for (difference_type t = 0; t < n; ++t) { ++iter; } }
    else        { for (difference_type t = 0; t > n; --t) { --iter; } }

    return iter;
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>::operator-(difference_type n) const
{
    BaseIterator iter(*this);
    if (n > 0)  { for (difference_type t = 0; t < n; ++t) { --iter; } }
    else        { for (difference_type t = 0; t > n; --t) { ++iter; } }

    return iter;
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy> &
BaseIterator<ElementType, PointerType, SeekStrategy>::operator++(void)
{
    SeekStrategy::next(_pointer);

    return *this;
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy> &
BaseIterator<ElementType, PointerType, SeekStrategy>::operator--(void)
{
    SeekStrategy::previous(_pointer);

    return *this;
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>::operator++(int)
{
    BaseIterator iter(*this);
    ++(*this);

    return iter;
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy>::operator--(int)
{
    BaseIterator iter(*this);
    --(*this);

    return iter;
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy> &
BaseIterator<ElementType, PointerType, SeekStrategy>::operator+=(difference_type n)
{
    return (*this = *this + n);
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
BaseIterator<ElementType, PointerType, SeekStrategy> &
BaseIterator<ElementType, PointerType, SeekStrategy>::operator-=(difference_type n)
{
    return (*this = *this - n);
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
ElementType &BaseIterator<ElementType, PointerType, SeekStrategy>::operator*(void) const
{
    return _pointer->value();
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
ElementType *BaseIterator<ElementType, PointerType, SeekStrategy>::operator->(void) const
{
    return &(_pointer->value());
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
bool BaseIterator<ElementType, PointerType, SeekStrategy>::operator==(const BaseIterator &iter) const
{
    return _pointer == iter._pointer;
}

template <typename ElementType, typename PointerType, typename SeekStrategy>
bool BaseIterator<ElementType, PointerType, SeekStrategy>::operator!=(const BaseIterator &iter) const
{
    return _pointer != iter._pointer;
}

NS_CC_YHGE_DATASTRUCTURE_END

#endif // YH_DATASTRUCTURE_ITERATOR_IMPLEMENT_H_
