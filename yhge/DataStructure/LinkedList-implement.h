#ifndef YH_DATASTRUCTURE_LINKEDLIST_IMPLEMENT_H_
#define YH_DATASTRUCTURE_LINKEDLIST_IMPLEMENT_H_

#include "LinkedList.h"

NS_CC_YHGE_DATASTRUCTURE_BEGIN

/*************************************************
    Implement of Class LinkedList
*************************************************/
template <typename Type>
LinkedList<Type>::LinkedList(void)
    : _sentinel(&_sentinel, &_sentinel)
{
    // do nothing
}

template <typename Type>
LinkedList<Type>::LinkedList(const LinkedList &list)
    : _sentinel(&_sentinel, &_sentinel)
{
    insert(begin(), list.begin(), list.end());
}

template <typename Type>
LinkedList<Type>::LinkedList(size_type number, const Type &value)
    : _sentinel(&_sentinel, &_sentinel)
{
    insert(begin(), number, value);
}

template <typename Type>
template <typename InputIterator>
LinkedList<Type>::LinkedList(InputIterator first, InputIterator last)
    : _sentinel(&_sentinel, &_sentinel)
{
    insert(begin(), first, last);
}

template <typename Type>
LinkedList<Type>::~LinkedList(void)
{
    clear();
}

template <typename Type>
typename LinkedList<Type>::iterator LinkedList<Type>::begin(void)
{
    // return an iterator to the beginning
    return iterator(_sentinel.next());
}

template <typename Type>
typename LinkedList<Type>::const_iterator LinkedList<Type>::begin(void) const
{
    // return an constant iterator to the beginning
    return const_iterator(_sentinel.next());
}

template <typename Type>
typename LinkedList<Type>::iterator LinkedList<Type>::end(void)
{
    // return an iterator just past the end
    return iterator(&_sentinel);
}

template <typename Type>
typename LinkedList<Type>::const_iterator LinkedList<Type>::end(void) const
{
    // return an constant iterator just past the end
    return const_iterator(&_sentinel);
}

template <typename Type>
typename LinkedList<Type>::reverse_iterator LinkedList<Type>::rbegin(void)
{
    // return a reverse iterator to the end
    return reverse_iterator(_sentinel.previous());
}

template <typename Type>
typename LinkedList<Type>::const_reverse_iterator LinkedList<Type>::rbegin(void) const
{
    // return a constant reverse iterator to the end
    return const_reverse_iterator(_sentinel.previous());
}

template <typename Type>
typename LinkedList<Type>::reverse_iterator LinkedList<Type>::rend(void)
{
    // return a reverse iterator just past the beginning
    return reverse_iterator(&_sentinel);
}

template <typename Type>
typename LinkedList<Type>::const_reverse_iterator LinkedList<Type>::rend(void) const
{
    // return a constant reverse iterator just past the beginning
    return const_reverse_iterator(&_sentinel);
}

template <typename Type>
Type &LinkedList<Type>::front(void)
{
    // return a reference to the first element
    return *begin();
}

template <typename Type>
const Type &LinkedList<Type>::front(void) const
{
    // return a reference to the first element
    return *begin();
}

template <typename Type>
Type &LinkedList<Type>::back(void)
{
    // return a reference to the last element
    return *rbegin();
}

template <typename Type>
const Type &LinkedList<Type>::back(void) const
{
    // return a reference to the last element
    return *rbegin();
}

template <typename Type>
void LinkedList<Type>::push_front(const Type &value)
{
    // add an element to the beginning of list
    insert(begin(), value);
}

template <typename Type>
void LinkedList<Type>::push_back(const Type &value)
{
    // add an element to the end of list
    insert(end(), value);
}

template <typename Type>
void LinkedList<Type>::pop_front(void)
{
    // remove the first element
    erase(begin());
}

template <typename Type>
void LinkedList<Type>::pop_back(void)
{
    // remove the last element
    erase(--end());
}

template <typename Type>
template <typename InputIterator>
void LinkedList<Type>::insert(iterator position, InputIterator first, InputIterator last)
{
    Node *location, *now;
    location = position.location();
    now = location->previous();

    // insert elements from [first] to [last] at [position]
    for (InputIterator iter = first; iter != last; ++iter, now = now->next())
    {
        now->next() = new Node(*iter, now, NULL);
    }

    now->next() = location;
    location->previous() = now;
}

template <typename Type>
typename LinkedList<Type>::iterator LinkedList<Type>::insert(iterator position, const Type &value)
{
    // insert the element [value] before [position]
    insert(position, size_type(1), value);

    // return iterator that point to the newly inserted element
    return --position;
}

template <typename Type>
void LinkedList<Type>::insert(iterator position, size_type number, const Type &value)
{
    Node *location, *now;
    location = position.location();
    now = location->previous();

    // insert [number] times of copies of element [value] at [position]
    for (size_type count = 0; count != number; ++count, now = now->next())
    {
        now->next() = new Node(value, now, NULL);
    }

    now->next() = location;
    location->previous() = now;
}

template <typename Type>
typename LinkedList<Type>::iterator LinkedList<Type>::erase(iterator position)
{
    // remove the element at [position]
    return erase(position, position + 1);
}

template <typename Type>
typename LinkedList<Type>::iterator LinkedList<Type>::erase(iterator first, iterator last)
{
    if (first == last) { return last; }

    // remove the element from [first] to [last]
    Node *previous = first.location()->previous();
    for (iterator iter = first; iter != last; )
    {
        delete (iter++).location();
    }

    previous->next() = last.location();
    previous->next()->previous() = previous;

    return last;
}

template <typename Type>
template <typename InputIterator>
void LinkedList<Type>::assign(InputIterator first, InputIterator last)
{
    // copy all elements from [first] to [last]
    LinkedList copy(first, last);
    swap(copy);
}

template <typename Type>
void LinkedList<Type>::assign(size_type number, const Type &value)
{
    // remove all elements before assign
    clear();

    // assign [number] times of copies of element [value] to the list
    insert(begin(), number, value);
}

template <typename Type>
void LinkedList<Type>::swap(LinkedList &list)
{
    LinkedList copy;

    // exchang the elements of this list with [list]
    splice(copy.begin(), list);
    splice(list.begin(), *this);
    splice(begin(), copy);
}

template <typename Type>
void LinkedList<Type>::clear(void)
{
    // remove all elements
    erase(begin(), end());
}

template <typename Type>
void LinkedList<Type>::splice(iterator position, LinkedList &list)
{
    // move elements from [list] before location [position]
    splice(position, list, list.begin(), list.end());
}

template <typename Type>
void LinkedList<Type>::splice(iterator position, LinkedList &list, iterator iter)
{
    // move element at [iter] before location [position]
    splice(position, list, iter, iter + 1);
}

template <typename Type>
void LinkedList<Type>::splice(iterator position, LinkedList &list, iterator first, iterator last)
{
    if (first == last) { return; }

    Node *posNode, *firstNode, *lastNode;
    posNode     = position.location();
    firstNode   = first.location();
    lastNode    = last.location();

    posNode->previous()->next()     = firstNode;
    firstNode->previous()->next()   = lastNode;
    lastNode->previous()->next()    = posNode;

    Node *previous          = posNode->previous();
    posNode->previous()     = lastNode->previous();
    lastNode->previous()    = firstNode->previous();
    firstNode->previous()   = previous;
}

template <typename Type>
template <typename Predicate>
void LinkedList<Type>::merge(LinkedList &list, Predicate predicate)
{
    iterator iter1 = begin();
    iterator iter2 = list.begin();

    iterator last1 = end();
    iterator last2 = list.end();

    while (iter1 != last1 && iter2 != last2)
    {
        // check whether [predicate] is true
        if (predicate(*iter1, *iter2))
        {
            ++iter1;
        }
        else
        {
            // move element at location [iter2] to this list before [iter1]
            iterator position = iter2++;
            splice(iter1, list, position, iter2);
        }
    }

    splice(last1, list, iter2, last2);
}

template <typename Type>
void LinkedList<Type>::merge(LinkedList &list)
{
    // merge this list with [list] from lower to higher
    merge(list, IsLessThan());
}

template <typename Type>
template <typename Predicate>
void LinkedList<Type>::remove_if(Predicate predicate)
{
    // remove elements for which [predicate] is true
    iterator iter = begin();
    while (iter != end())
    {
        iterator position = iter++;
        if (predicate(*position))
        {
            erase(position);
        }
    }
}

template <typename Type>
void LinkedList<Type>::remove(const Type &value)
{
    // remove elements that are equal to [value]
    remove_if(IsEqualTo(value));
}

template <typename Type>
template <typename Predicate>
void LinkedList<Type>::unique(Predicate predicate)
{
    // remove elements if [predicate] is true
    iterator iter = ++begin();
    while (iter != end())
    {
        iterator position = iter++;
        if (predicate(*(position - 1), *position))
        {
            erase(position);
        }
    }
}

template <typename Type>
void LinkedList<Type>::unique(void)
{
    // remove elements that equal to the element immediately preceding
    unique(IsEqual());
}

template <typename Type>
template <typename Predicate>
void LinkedList<Type>::sort(Predicate predicate)
{
    LinkedList copy;
    while (!empty())
    {
        // find the smallest element of this list
        iterator smallest = begin();
        for (iterator iter = ++begin(); iter != end(); ++iter)
        {
            if (predicate(*iter, *smallest))
            {
                smallest = iter;
            }
        }

        // move the smallest element to the end of [copy]
        copy.splice(copy.end(), *this, smallest, smallest + 1);
    }

    // swap the content between [copy] and this list
    swap(copy);
}

template <typename Type>
void LinkedList<Type>::sort(void)
{
    // sort all elements from lower to higher
    sort(IsLessThan());
}

template <typename Type>
void LinkedList<Type>::reverse(void)
{
    // reverse the list
    iterator iter;
    for (iter = begin(); iter != end(); --iter)
    {
        // reverse all nodes
        iter.location()->reverse();
    }

    // reverse sentinel node
    iter.location()->reverse();
}

template <typename Type>
bool LinkedList<Type>::empty(void) const
{
    // check whether the list is empty
    return (begin() == end());
}

template <typename Type>
typename LinkedList<Type>::size_type LinkedList<Type>::size(void) const
{
    // count the size of this list
    size_type number = 0;
    for (const_iterator iter = begin(); iter != end(); ++iter)
    {
        ++number;
    }

    return number;
}

template <typename Type>
typename LinkedList<Type>::size_type LinkedList<Type>::max_size(void) const
{
    // return the maximum size of the list
    return size_type(-1);
}

template <typename Type>
void LinkedList<Type>::resize(size_type number, const Type &value)
{
    iterator iter = begin();
    for (size_type count = 0; count < number; ++count, ++iter)
    {
        // Check whether [number] is greater than the current size
        if (iter == end())
        {
            // expend this list by inserting elements [value]
            insert(end(), number - count, value);
            return;
        }
    }

    // drop the rest of elements
    erase(iter, end());
}

template <typename Type>
LinkedList<Type> &LinkedList<Type>::operator=(const LinkedList &list)
{
    // avoid self-assignment
    if (&list != this) { return *this; }

    // copy all elements from [list]
    assign(list.begin(), list.end());

    return *this;
}

template <typename Type>
bool LinkedList<Type>::operator==(const LinkedList &list) const
{
    const_iterator iter1 = begin();
    const_iterator iter2 = list.begin();

    const_iterator last1 = end();
    const_iterator last2 = list.end();

    while (iter1 != last1 && iter2 != last2 && *iter1 == *iter2)
    {
        ++iter1;
        ++iter2;
    }

    return iter1 == last1 && iter2 == iter2;
}

template <typename Type>
bool LinkedList<Type>::operator!=(const LinkedList &list) const
{
    return !(*this == list);
}

template <typename Type>
bool LinkedList<Type>::operator<(const LinkedList &list) const
{
    const_iterator iter1 = begin();
    const_iterator iter2 = list.begin();

    const_iterator last1 = end();
    const_iterator last2 = list.end();

    while (iter1 != last1 && iter2 != last2)
    {
        if (*iter1 < *iter2) { return true; }
        if (*iter1 > *iter2) { return false; }

        ++iter1;
        ++iter2;
    }

    return iter1 == last1 && iter2 != last2;
}

template <typename Type>
bool LinkedList<Type>::operator>(const LinkedList &list) const
{
    return list < *this;
}

template <typename Type>
bool LinkedList<Type>::operator<=(const LinkedList &list) const
{
    return !(*this > list);
}

template <typename Type>
bool LinkedList<Type>::operator>=(const LinkedList &list) const
{
    return !(*this < list);
}

/*************************************************
    Implement of Class Node
*************************************************/
template <typename Type>
LinkedList<Type>::Node::Node(void)
    : _value(), _previous(NULL), _next(NULL)
{
    // do nothing
}

template <typename Type>
LinkedList<Type>::Node::Node(const Type &value)
    : _value(value), _previous(NULL), _next(NULL)
{
    // do nothing
}

template <typename Type>
LinkedList<Type>::Node::Node(Node *const previous, Node *const next)
    : _value(), _previous(previous), _next(next)
{
    // do nothing
}

template <typename Type>
LinkedList<Type>::Node::Node(const Type &value, Node *const previous, Node *const next)
    : _value(value), _previous(previous), _next(next)
{
    // do nothing
}
/*
template <typename Type>
LinkedList<Type>::Node::~Node(void)
{
    // do nothing
}
*/
template <typename Type>
Type &LinkedList<Type>::Node::value(void)
{
    return _value;
}

template <typename Type>
const Type &LinkedList<Type>::Node::value(void) const
{
    return _value;
}

template <typename Type>
typename LinkedList<Type>::Node *&LinkedList<Type>::Node::next(void)
{
    return _next;
}

template <typename Type>
const typename LinkedList<Type>::Node *LinkedList<Type>::Node::next(void) const
{
    return _next;
}

template <typename Type>
typename LinkedList<Type>::Node *&LinkedList<Type>::Node::previous(void)
{
    return _previous;
}

template <typename Type>
const typename LinkedList<Type>::Node *LinkedList<Type>::Node::previous(void) const
{
    return _previous;
}

template <typename Type>
void LinkedList<Type>::Node::reverse(void)
{
    // swap pointers [_next] and [_previous]
    Node *temp = _next;
    _next = _previous;
    _previous = temp;
}

/*************************************************
    Implement of Class ForwardSeek
*************************************************/
template <typename Type>
template <typename PointerType>
void LinkedList<Type>::ForwardSeek<PointerType>::next(PointerType *&pointer)
{
    pointer = pointer->next();
}

template <typename Type>
template <typename PointerType>
void LinkedList<Type>::ForwardSeek<PointerType>::previous(PointerType *&pointer)
{
    pointer = pointer->previous();
}

/*************************************************
    Implement of Class ReverseSeek
*************************************************/
template <typename Type>
template <typename PointerType>
void LinkedList<Type>::ReverseSeek<PointerType>::next(PointerType *&pointer)
{
    pointer = pointer->previous();
}

template <typename Type>
template <typename PointerType>
void LinkedList<Type>::ReverseSeek<PointerType>::previous(PointerType *&pointer)
{
    pointer = pointer->next();
}

/*************************************************
    Implement of Class IsLessThan
*************************************************/
template <typename Type>
bool LinkedList<Type>::IsLessThan::operator()(const Type &value1, const Type &value2)
{
    return value1 < value2;
}

/*************************************************
    Implement of Class IsEqual
*************************************************/
template <typename Type>
bool LinkedList<Type>::IsEqual::operator()(const Type &value1, const Type &value2)
{
    return value1 == value2;
}

/*************************************************
    Implement of Class IsEqualTo
*************************************************/
template <typename Type>
LinkedList<Type>::IsEqualTo::IsEqualTo(const Type &value)
    : _value(value)
{
    // do nothing
}

template <typename Type>
bool LinkedList<Type>::IsEqualTo::operator()(const Type &value)
{
    return value == _value;
}

NS_CC_YHGE_DATASTRUCTURE_END

#endif // YH_DATASTRUCTURE_LINKEDLIST_IMPLEMENT_H_
