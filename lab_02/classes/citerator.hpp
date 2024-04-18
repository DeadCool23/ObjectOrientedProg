#ifndef __CITERATOR_HPP__
#define __CITERATOR_HPP__

template<typename T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<ListNode<T>> &node, size_t size, size_t ind) {
    ptr = node;
    this->size = size;
    this->index = ind;
}

template<typename T>
bool ConstIterator<T>::operator == (ConstIterator const& other) const {
    return this->ptr.lock() == other.ptr.lock();
}

template<typename T>
ConstIterator<T>::pointer ConstIterator<T>::operator->() const {
    return &this->ptr.lock()->get_ref();
}

template<typename T>
ConstIterator<T>::reference ConstIterator<T>::operator*() const {
    return this->ptr.lock()->get_ref();
}

template<typename T>
ConstIterator<T>::operator bool() const {
    return this->ptr.lock() == nullptr;
}

template<typename T>
void ConstIterator<T>::next(void) {
    this->ptr = this->ptr.lock()->get_next();
    ++this->index;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator++() {
    this->next();
    return *this;
}


template<typename T>
ConstIterator<T> ConstIterator<T>::operator++(int) {
    auto ret_ptr = *this;
    this->next();
    return ret_ptr;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator+(size_t index) {
    time_t now = time(NULL);
    if (index >= this->size)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    for (size_t i = 0; i < index; ++i)
        this->next();
    return *this;
}

template<typename T>
ConstIterator<T>& ConstIterator<T>::operator+=(size_t index) {
    time_t now = time(NULL);
    if (index >= this->size)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    for (size_t i = 0; i < index; ++i)
        this->next();
    return *this;
}

template<typename T>
ConstIterator<T>::difference_type ConstIterator<T>::distance(const ConstIterator<T>& other) const {
    return difference_type(this->index) - difference_type(other.index);
}

#endif // __CITERATOR_HPP__