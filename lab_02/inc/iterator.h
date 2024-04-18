#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <memory>
#include <iterator>

#include "concepts.h"
#include "listnode.h"
#include "base_iterator.h"

extern "C" {
    #include <stdint.h>
}

template <typename T>
class Iterator : public BaseIterator {
public:
    using pointer = T*;
    using reference = T&;
    using value_type = T;
    using difference_type = int32_t;
    using iterator_category = std::forward_iterator_tag;

public:
    Iterator(const Iterator& iter) = default;
    Iterator(const std::shared_ptr<ListNode<T>> &node, size_t size, size_t ind = 0);
    
    bool operator == (Iterator const& other) const;

    pointer operator->();
    reference operator*();
    
    operator bool() const;
    Iterator& operator++();
    Iterator operator++(int);

    Iterator& operator+(size_t index);
    Iterator& operator+=(size_t index);

    difference_type distance(const Iterator<T>& other) const;
private:
    void next(void);

private:
    std::weak_ptr<ListNode<T>> ptr;
};

#include "iterator.hpp"

#endif // __ITERATOR_H__