#ifndef __LISTNODE_HPP__
#define __LISTNODE_HPP__

template<typename T>
requires Empty<T>
ListNode<T>::ListNode(void) : value(T()), next(nullptr) {}

template<typename T>
ListNode<T>::ListNode(const T &val) : value(val), next(nullptr) {}

template<typename T>
ListNode<T>::ListNode(ListNode<T> &node) :value(node), next(node.next) {}

template<typename T>
ListNode<T>::ListNode(ListNode<T> &&node) : value(node.next), next(node.next) {}

template<typename T>
ListNode<T>::ListNode(std::shared_ptr<ListNode<T>> &node) {
    this->value = node->value;
    this->next = node->next;
}

template<typename T>
void ListNode<T>::set_value(const T &val) { this->value = val; }

template<typename T>
void ListNode<T>::set_next(ListNode<T> &node) {
    this->next = std::shared_ptr<ListNode<T>>(node);
}

template<typename T>
void ListNode<T>::set_next(const std::shared_ptr<ListNode<T>> &node) {
    this->next = node;
}

template<typename T>
void ListNode<T>::set_next_null(void) { this->next = nullptr; }

template<typename T>
T& ListNode<T>::get_ref(void) { return value; }

template<typename T>
const T& ListNode<T>::get_value(void) const { return value; };

template<typename T>
std::shared_ptr<ListNode<T>> ListNode<T>::get_next(void) const {
    return this->next;
};

template<typename T>
requires Comparable<T>
bool ListNode<T>::operator==(const ListNode<T> &node) const {
    return this->next == node.next && this->get_ref() == node.get_ref();
}
template<typename T>
bool ListNode<T>::operator!=(const ListNode<T> &node) const {
    return !(*this == node);
}


template<typename T>
bool ListNode<T>::operator==(const std::shared_ptr<ListNode<T>> &node) const {
    return this == node;
}

template<typename T>
bool ListNode<T>::operator!=(const std::shared_ptr<ListNode<T>> &node) const {
    return !(this == node);
}

#endif // __LISTNODE_HPP__