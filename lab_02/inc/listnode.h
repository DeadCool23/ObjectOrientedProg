#ifndef __LISTNODE_H__
#define __LISTNODE_H__

#include <memory>
#include "concepts.h"

template <typename T>
requires Empty<T> && Comparable<T>
class ListNode {
public:
    ListNode(void);
    ListNode(const T &val);
    ListNode(ListNode<T> &node);
    ListNode(ListNode<T> &&node);
    ListNode(std::shared_ptr<ListNode<T>> &node);

    void set_value(const T &val);
    void set_next(ListNode<T> &node);
    void set_next(const std::shared_ptr<ListNode<T>> &node);

    void set_next_null(void);

    T& get_ref(void);
    const T& get_value(void) const;

    std::shared_ptr<ListNode<T>> get_next(void) const;

    bool operator == (const ListNode<T> &node) const;
    bool operator != (const ListNode<T> &node) const;

    bool operator == (const std::shared_ptr<ListNode<T>> &node) const;
    bool operator != (const std::shared_ptr<ListNode<T>> &node) const;

    ~ListNode() = default;

private:
    T value;
    std::shared_ptr<ListNode<T>> next;
};

#include "listnode.hpp"

#endif // __LISTNODE_H__