#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

template<typename T>
Iterator<T>::Iterator(const std::shared_ptr<typename List<T>::ListNode> &node, size_t size, size_t ind) {
    this->ptr = node;
    this->size = size;
    this->index = ind;
}

template<typename T>
bool Iterator<T>::operator == (const Iterator<T> &other) const {
    return this->ptr.lock() == other.ptr.lock();
}

template<typename T>
Iterator<T>::pointer Iterator<T>::operator->() {
    return &this->ptr.lock()->get_ref();
}

template<typename T>
const Iterator<T>::pointer Iterator<T>::operator->() const {
    return &this->ptr.lock()->get_value();
}

template<typename T>
Iterator<T>::reference Iterator<T>::operator*() {
    return this->ptr.lock()->get_ref();
}

template<typename T>
const Iterator<T>::reference Iterator<T>::operator*() const {
    return this->ptr.lock()->get_value();
}


template<typename T>
Iterator<T>::operator bool() const {
    return this->ptr.lock() != nullptr;
}

template<typename T>
void Iterator<T>::next(void) {
    time_t now = time(NULL);
    if (index >= size || !this->ptr.lock())
        throw IteratorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
    this->ptr = this->ptr.lock()->get_next();
    ++this->index;
}

template<typename T>
Iterator<T>& Iterator<T>::operator++() {
    this->next();
    return *this;
}


template<typename T>
Iterator<T> Iterator<T>::operator++(int) {
    auto ret_ptr = *this;
    this->next();
    return ret_ptr;
}

template<typename T>
Iterator<T>::difference_type Iterator<T>::distance(const Iterator<T>& other) const {
    return difference_type(this->index) - difference_type(other.index);
}

#endif // __ITERATOR_HPP__
