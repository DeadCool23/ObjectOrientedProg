#ifndef __CITERATOR_H__
#define __CITERATOR_H__

#include <memory>
#include <iterator>

#include "concepts.h"
#include "base_iterator.h"

template <typename T>
requires Comparable<T> && EmptyConstructable<T> &&
         Divable<T> && Multable<T> && 
         Neitral<T> && Printable<T>
class List;

template <typename T>
class ConstIterator : public BaseIterator {
public:
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using difference_type = size_t;
    using iterator_category = std::forward_iterator_tag;

    using ListNode = List<T>::ListNode;
public:
    ConstIterator(const ConstIterator<T>& iter) = default;
    ConstIterator(const std::shared_ptr<ListNode> &node, size_t size, size_t ind = 0);

    bool operator == (ConstIterator const& other) const;

    pointer operator->() const;
    reference operator*() const;
    
    operator bool() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);

    difference_type distance(const ConstIterator<T>& other) const;
private:
    void next(void);

private:
    std::weak_ptr<ListNode> ptr;
};

#include "citerator.hpp"

#endif // __CITERATOR_H__