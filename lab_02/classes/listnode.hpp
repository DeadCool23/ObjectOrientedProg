#ifndef __LISTNODE_HPP__
#define __LISTNODE_HPP__

template<typename T>
requires EmptyConstructable<T>
List<T>::ListNode::ListNode(void) : value(T()), next(nullptr) {}

template<typename T>
List<T>::ListNode::ListNode(const T &val) : value(val), next(nullptr) {}

template<typename T>
List<T>::ListNode::ListNode(List<T>::ListNode &&node) : value(node.next), next(node.next) {}

template<typename T>
List<T>::ListNode::ListNode(const List<T>::ListNode &node) :value(node), next(node.next) {}

template<typename T>
List<T>::ListNode::ListNode(const std::shared_ptr<List<T>::ListNode> &node) {
    this->value = node->value;
    this->next = node->next;
}

template<typename T>
void List<T>::ListNode::set_value(const T &val) { this->value = val; }

template<typename T>
void List<T>::ListNode::set_next(const List<T>::ListNode &node) {
    this->next = std::shared_ptr<List<T>::ListNode>(node);
}

template<typename T>
void List<T>::ListNode::set_next(const std::shared_ptr<List<T>::ListNode> &node) {
    this->next = node;
}

template<typename T>
void List<T>::ListNode::set_next_null(void) { this->next = nullptr; }

template<typename T>
T& List<T>::ListNode::get_ref(void) { return value; }

template<typename T>
const T& List<T>::ListNode::get_value(void) const { return value; };

template<typename T>
std::shared_ptr<typename List<T>::ListNode> List<T>::ListNode::get_next(void) const {
    return this->next;
};

template<typename T>
requires Comparable<T>
bool List<T>::ListNode::operator==(const List<T>::ListNode &node) const {
    return this->next == node.next && this->get_ref() == node.get_ref();
}
template<typename T>
bool List<T>::ListNode::operator!=(const List<T>::ListNode &node) const {
    return !(*this == node);
}


template<typename T>
bool List<T>::ListNode::operator==(const std::shared_ptr<typename List<T>::ListNode> &node) const {
    return this == node;
}

template<typename T>
bool List<T>::ListNode::operator!=(const std::shared_ptr<typename List<T>::ListNode> &node) const {
    return !(this == node);
}

#endif // __LISTNODE_HPP__