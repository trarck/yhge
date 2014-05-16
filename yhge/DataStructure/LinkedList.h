#ifndef YH_DATASTRUCTURE_LINKEDLIST_H_
#define YH_DATASTRUCTURE_LINKEDLIST_H_

#include "DataStructureMacros.h"
#include "Iterator.h"

NS_CC_YHGE_DATASTRUCTURE_BEGIN

/*************************************************
    Declaration of Class LinkedList
*************************************************/
template <typename Type>
class LinkedList
{
    protected:
        // Nested Element Class(es)
        class Node;

        // Nested Iterator Seek Strategy Class(es)
        template <typename PointerType> class ForwardSeek;
        template <typename PointerType> class ReverseSeek;

        // Nested Functor Class(es)
        class IsLessThan;
        class IsEqual;
        class IsEqualTo;

    public:
        // Type Definition(s)
        typedef Type        value_type;
        typedef const Type  const_value_type;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;

        typedef BaseIterator<Type, Node, ForwardSeek<Node> > Iterator;
        typedef BaseIterator<Type, Node, ReverseSeek<Node> > ReverseIterator;
        typedef BaseIterator<const Type, const Node, ForwardSeek<const Node> > ConstIterator;
        typedef BaseIterator<const Type, const Node, ReverseSeek<const Node> > ConstReverseIterator;

        // Constructor(s) & Destructor(s)
        LinkedList(void);
        LinkedList(const LinkedList &list);
        LinkedList(size_type number, const Type &value = Type());

        template <typename InputIterator>
        LinkedList(InputIterator first, InputIterator last);

        ~LinkedList(void);

        // Iterator Method(s)
        Iterator                begin(void);
        ConstIterator           begin(void)     const;
        Iterator                end(void);
        ConstIterator           end(void)       const;
        ReverseIterator         rbegin(void);
        ConstReverseIterator    rbegin(void)    const;
        ReverseIterator         rend(void);
        ConstReverseIterator    rend(void)      const;

        // Element Access Method(s)
        Type            &front(void);
        const Type      &front(void)    const;
        Type            &back(void);
        const Type      &back(void)     const;

        // Modifier Method(s)
        void            push_front(const Type &value);
        void            push_back(const Type &value);
        void            pop_front(void);
        void            pop_back(void);

        template <typename InputIterator>
        void            insert(Iterator position, InputIterator first, InputIterator last);
        Iterator        insert(Iterator position, const Type &value);
        void            insert(Iterator position, size_type number, const Type &value);
        Iterator        erase(Iterator position);
        Iterator        erase(Iterator first, Iterator last);

        template <typename InputIterator>
        void            assign(InputIterator first, InputIterator last);
        void            assign(size_type number, const Type &value);
        void            swap(LinkedList &list);
        void            clear(void);

        // Operation Method(s)
        void            splice(Iterator position, LinkedList &list);
        void            splice(Iterator position, LinkedList &list, Iterator iter);
        void            splice(Iterator position, LinkedList &list, Iterator first, Iterator last);

        template <typename Predicate>
        void            merge(LinkedList &list, Predicate predicate);
        void            merge(LinkedList &list);

        template <typename Predicate>
        void            remove_if(Predicate predicate);
        void            remove(const Type &value);

        template <typename Predicate>
        void            unique(Predicate predicate);
        void            unique(void);

        template <typename Predicate>
        void            sort(Predicate predicate);
        void            sort(void);
        void            reverse(void);

        // Capacity Method(s)
        bool            empty(void)     const;
        size_type       size(void)      const;
        size_type       max_size(void)  const;
        void            resize(size_type number, const Type &value = Type());

        // Assignment Operator(s)
        LinkedList            &operator=(const LinkedList &list);

        // Relational Operator(s)
        bool            operator==(const LinkedList &list) const;
        bool            operator!=(const LinkedList &list) const;
        bool            operator< (const LinkedList &list) const;
        bool            operator> (const LinkedList &list) const;
        bool            operator<=(const LinkedList &list) const;
        bool            operator>=(const LinkedList &list) const;

    protected:
        // Data Member(s)
        Node            _sentinel;
};

/*************************************************
    Declaration of Class Node
*************************************************/
template <typename Type>
class LinkedList<Type>::Node
{
    public:
        // Constructor(s) & Destructor(s)
        Node(void);
        Node(const Type &value);
        Node(Node *const previous, Node *const next);
        Node(const Type &value, Node *const previous, Node *const next);
        //~Node(void);

        // Set Function(s) & Get Function(s)
        Type            &value(void);
        const Type      &value(void)    const;
        Node            *&next(void);
        const Node      *next(void)     const;
        Node            *&previous(void);
        const Node      *previous(void) const;

        // Operation Method(s)
        void            reverse(void);

    private:
        // Data Member(s)
        Type            _value;
        Node            *_previous, *_next;
};

/*************************************************
    Declaration of Class ForwardSeek
*************************************************/
template <typename Type>
template <typename PointerType>
class LinkedList<Type>::ForwardSeek
{
    public:
        // Seek Method(s)
        inline static void next(PointerType *&pointer);
        inline static void previous(PointerType *&pointer);
};

/*************************************************
    Declaration of Class ReverseSeek
*************************************************/
template <typename Type>
template <typename PointerType>
class LinkedList<Type>::ReverseSeek
{
    public:
        // Seek Method(s)
        inline static void next(PointerType *&pointer);
        inline static void previous(PointerType *&pointer);
};

/*************************************************
    Declaration of Class IsLessThan
*************************************************/
template <typename Type>
class LinkedList<Type>::IsLessThan
{
    public:
        // Function Call Operator(s)
        inline bool operator()(const Type &value1, const Type &value2);
};

/*************************************************
    Declaration of Class IsEqual
*************************************************/
template <typename Type>
class LinkedList<Type>::IsEqual
{
    public:
        // Function Call Operator(s)
        inline bool operator()(const Type &value1, const Type &value2);
};

/*************************************************
    Declaration of Class IsEqualTo
*************************************************/
template <typename Type>
class LinkedList<Type>::IsEqualTo
{
    public:
        // Constructor(s)
        IsEqualTo(const Type &value);

        // Function Call Operator(s)
        inline bool operator()(const Type &value);

    private:
        // Data Member(s)
        const Type _value;
};

NS_CC_YHGE_DATASTRUCTURE_END

#include "LinkedList-implement.h"

#endif // YH_DATASTRUCTURE_LINKEDLIST_H_
