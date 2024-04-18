#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "concepts.h"

#include <iostream>

#pragma GCC diagnostic ignored "-Wreturn-type"

#pragma region Constructions
/* ---------------------- Конструкторы ---------------------- */
template <typename T>
List<T>::List(void) : head(nullptr), tail(nullptr) {}

template <typename T>
List<T>::List(const T &value) { this->push_back(value); }

template <typename T>
List<T>::List(size_t size, const T &value) {
    time_t now = time(NULL);
    if (size < 0) throw SizeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    for (size_t i = 0; i < size; ++i)
        this->push_back(value);
}

template <typename T>
List<T>::List(const std::initializer_list<T> &init) {
    for (const auto &value : init)
        this->push_back(value);
}

template <typename T>
template <template<typename> class C>
requires ContainerClass<C<T>>
List<T>::List(const C<T> &container) {
    this->_size = container.size();
    for (const auto &value : container)
        this->push_back(value);
}

template <typename T>
template <typename U, template<typename> class C>
requires ContainerClass<C<U>> && Convertable<T, U>
List<T>::List(const C<U> &container) {
    this->_size = container.size();
    for (const auto &value : container)
        this->push_back(T(value));
}

template <typename T>
List<T>::List(const iterator_t &beg, const iterator_t &end) {
    for (auto it = beg; it != end; ++it)
        this->push_back(*it);
}

template <typename T>
List<T>::List(const iterator_t &beg, const iterator_t &end, size_t count) {
    time_t now = time(NULL);
    if (beg.distance(end) < Iterator<T>::difference_type(count))
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
    
    size_t i = 0;
    for (auto it = beg; i++ < count && it != end; ++it)
        this->push_back(*it);
}

template <typename T>
List<T>::List(const citerator_t &beg, const citerator_t &end) {
    for (auto it = beg; it != end; ++it)
        this->push_back(*it);
}

template <typename T>
List<T>::List(const citerator_t &beg, const citerator_t &end, size_t count) {
    time_t now = time(NULL);
    if (beg.distance(end) < ConstIterator<T>::difference_type(count))
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
    
    size_t i = 0;
    for (auto it = beg; i++ < count && it != end; ++it)
        this->push_back(*it);
}


template <typename T>
List<T>::List(List<T> &&list) : head(list.head), tail(list.tail) {
    this->_size = list._size;
}

template <typename T>
List<T>::List(const List<T> &list) {
    for (const auto &value : list)
        this->push_back(value);
}

template <typename T>
template <typename U>
requires Convertable<T, U>
List<T>::List(const List<U> &list) {
    for (const auto &value : list)
        this->push_back(T(value));
}


#pragma endregion

#pragma region Methods
/* -------------------------------- Методы Списка ------------------------------ */
template<typename T>
Container::size_t List<T>::size(void) const { return _size; }

template<typename T>
bool List<T>::is_empty(void) const { return _size ? true : false; }

// --- Индексация ---
template<typename T>
T& List<T>::operator[](size_t ind) {
    time_t now = time(NULL);
    if (ind >= _size)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    size_t i = 0;
    for (auto &value : *this) {
        if (ind == i)
            return value;
        ++i;
    }
}

template<typename T>
const T& List<T>::operator[](size_t ind) const {
    time_t now = time(NULL);
    if (ind >= _size)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    size_t i = 0;
    for (const auto &value : *this) {
        if (ind == i)
            return value;
        ++i;
    }
}

// --- Пушеры ---
template<typename T>
void List<T>::push_back(const T &value) {
    auto new_node = NodeAlloc(value);

    if (head) {
        tail->set_next(new_node);
        tail = new_node;
    } else {
        head = new_node;
        tail = head;
    }
    ++this->_size;
}

template<typename T>
void List<T>::push_back(const List<T> &list) {
    for (auto &value : list)
        this->push_back(value);
}

template<typename T>
template<typename U>
requires Convertable<T, U>
void List<T>::push_back(const List<U> &list) {
    for (auto &value : list)
        this->push_back(T(value));
}

template<typename T>
void List<T>::push_front(const T &value) {
    auto new_node = NodeAlloc(value);

    if (head) {
        auto tmp_node = head;
        head = new_node;
        head->set_next(tmp_node);
    } else {
        head = new_node;
        tail = head;
    }
    ++this->_size;
}

template<typename T>
void List<T>::push_front(const List<T> &list) {
    List<T> front_list;
    for (auto &value : list)
        front_list.push_back(value);
    front_list.tail->set_next(this->head);
    this->head = front_list.head;
}

template<typename T>
template<typename U>
requires Convertable<T, U>
void List<T>::push_front(const List<U> &list) {
    List<T> front_list;
    for (auto &value : list)
        front_list.push_back(T(value));
    front_list.tail->set_next(this->head);
    this->head = front_list.head;
}

// --- Поперы ---
template<typename T>
T List<T>::pop_back(void) {
    time_t now = time(NULL);
    if (!_size) throw EmptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    T del_val;
    if (_size == 1) {
        del_val = this->head->get_ref();
        this->head = nullptr;
        this->tail = nullptr;
    } else {    
        auto cur = this->head;
        for (; cur->get_next() != tail; cur = cur->get_next());

        del_val = cur->get_next()->get_ref();
        cur->set_next_null();
        tail = cur;
    }

    --this->_size;
    return del_val;
}

template<typename T>
T List<T>::pop_front(void) {
    time_t now = time(NULL);
    if (!_size) throw SizeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    T del_val;
    if (_size == 1) {
        del_val = this->head->get_ref();
        this->head = nullptr;
        this->tail = nullptr;
    } else {
        del_val = this->head->get_ref();
        this->head = this->head->get_next();
    }

    --this->_size;
    return del_val;
}

template<typename T>
T List<T>::pop(size_t index) {
    time_t now = time(NULL);
    if (!_size) throw SizeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    if (index >= this->_size && index < 0)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
    
    T del_val;
    if (!index) {
        del_val = this->pop_front();
    } else if (index + 1 == _size) {
        del_val = this->pop_back();
    } else {
        auto cur = this->head;
        for (size_t i = 0; i < index - 1; ++i, cur = cur->get_next());

        del_val = cur->get_next()->get_ref();
        cur->set_next(cur->get_next()->get_next());
    }

    --this->_size;
    return del_val;
}

// --- Очистка ---
template<typename T>
void List<T>::clear(void) noexcept {
    while (this->_size)
        this->pop_front();
}

// --- Инверсия ---
template<typename T>
void List<T>::reverse(void) noexcept {
    auto current = head;
    auto prev_head = head;
    std::shared_ptr<ListNode<T>> prev = nullptr;

    while (current) {
        auto next = current->get_next();
        current->set_next(prev);
        prev = current;
        current = next;
    }

    head = prev;
    tail = prev_head;
}

template<typename T>
bool List<T>::find(const T &find_value) const noexcept {
    bool is_finded = false;
    for (const auto &val : *this)
        if (val == find_value)
            is_finded = true;

    return is_finded;
}

// --- Вставка ---
template<typename T>
void List<T>::insert(size_t index, const T &value) {
    time_t now = time(NULL);
    if (index > this->_size && index < 0)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    if (!index) {
        this->push_front(value);
    } else if (index == _size) {
        this->push_back(value);
    } else {
        auto cur = this->head;
        for (size_t i = 0; i < index - 1; ++i, cur = cur->get_next());

        std::shared_ptr<ListNode<T>> new_node = NodeAlloc(value);
        new_node->set_next(cur->get_next());
        cur->set_next(new_node);
    }
}

// --- Удаление ---
template<typename T>
requires Comparable<T>
void List<T>::remove(const T &value) {
    bool is_del = false;
    if (this->head) {
    } else if (this->head->get_ref() == value) {
        is_del = true;
        this->pop_front();
    } else {
        auto cur = this->head;
        for (size_t i = 1; !is_del && i < _size; ++i, cur = cur.get_next()) {
            if ((*this)[i] == value) {
                is_del = true;
                cur->set_next(cur->get_next()->get_next());
            }
        }
    }

    time_t now = time(NULL);
    if (!is_del)
        throw NoValueError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
}

// --- Операции ---
template<typename T>
void List<T>::each(std::function<T(const T &value)> func) {
    for (auto &value : *this)
        value = func(value);
}

template<typename T>
List<T> &List<T>::operator=(List<T> &&list) {
    this->clear();
    this->head = list.head;
    this->tail = list.tail;
    this->_size = list._size;
    return *this;
}

template<typename T>
List<T> &List<T>::operator=(const List<T> &list) {
    this->clear();
    for (const auto& item : list)
        this->push_back(item);
    return *this;
}

template<typename T>
requires Multable<T>
List<T> &List<T>::operator*(const T& multer) {
    for (auto &value : *this)
        value *= multer;

    return *this;
}

template<typename T>
requires Multable<T>
List<T> &List<T>::operator*=(const T& multer) { return *this * multer; }

template<typename T>
requires Divable<T> && Comparable<T>
List<T> &List<T>::operator/(const T& diver) {
    time_t now = time(NULL);
    if (diver == T(0)) throw LogicError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
    for (auto &value : *this)
        value /= diver;

    return *this;
}
template<typename T>
requires Divable<T> && Comparable<T> && Neitral<T>
List<T> &List<T>::operator/=(const T& diver) { return *this / diver; }


template<typename T>
List<T> &List<T>::operator+(const List<T> &add_list) {
    this->push_back(add_list);
    return *this;
}

template<typename T>
template<typename U>
requires Convertable<T, U>
List<T> &List<T>::operator+(const List<U> &add_list) {
    this->push_back(add_list);
    return *this;
}


template<typename T>
List<T> &List<T>::operator+=(const List<T> &add_list) { return *this + add_list; }

template<typename T>
template<typename U>
requires Convertable<T, U>
List<T> &List<T>::operator+=(const List<U> &add_list) { return *this + add_list; }

template<typename T>
requires Comparable<T>
template<typename U>
requires Convertable<T, U>
bool List<T>::operator==(const List<U> &add_list) {
    bool is_equal = true;
    if (this->size() != add_list.size())
        is_equal = false;

    for (size_t i = 0; is_equal && i < this->_size; ++i)
        if ((*this)[i] != T(add_list[i]))
            is_equal = false;
    
    return is_equal;
}

template<typename T> 
requires Comparable<T>
template<typename U>
requires Convertable<T, U>
bool List<T>::operator!=(const List<U> &add_list) {
    return !(*this == add_list);
}

// --- Печать ---

template<typename T>
void List<T>::print(void) const noexcept {
    std::cout << "{ ";
    for (size_t i = 0; i < this->size(); ++i)
        std::cout << (!i ? "" : ", ") << (/*const_cast<List<T>&>(*/*this/*)*/)[i];
    std::cout << " }" << std::endl;
}
template<typename T>
void List<T>::debug_print(void) const noexcept {
    std::cout << "Size: " << _size << std::endl;
    std::cout << "{" << std::endl;
    for (size_t i = 0; i < this->size(); ++i){
        std::cout << "  " << "[" << i << "]: " << (/*const_cast<List<T>&>(*/*this/*)*/)[i] << std::endl;

    }
    std::cout << "}" << std::endl;
}

#pragma endregion

#pragma region Iterations
/* ------------------------- Получение Итераторов -------------------------- */

template<typename T>
List<T>::iterator_t List<T>::begin(void) { return Iterator(head, _size); }

template<typename T>
List<T>::iterator_t List<T>::end(void) {
    auto end_ptr = tail->get_next();
    return Iterator(end_ptr, _size, _size); 
}

template<typename T>
List<T>::citerator_t List<T>::cbegin(void) const { return begin(); }

template<typename T>
List<T>::citerator_t List<T>::cend(void) const { return end(); }

#pragma endregion

#pragma region ProtectedMethods

template<typename T>
List<T>::citerator_t List<T>::begin(void) const { return ConstIterator(head, _size); }

template<typename T>
List<T>::citerator_t List<T>::end(void) const {
    auto end_ptr = tail->get_next();
    return ConstIterator(end_ptr, _size, _size); 
}

template<typename T>
std::shared_ptr<ListNode<T>> List<T>::get_head(void) { return head; }
template<typename T>
std::shared_ptr<ListNode<T>> List<T>::get_tail(void) { return tail; }

// Выделение памяти под Узел
template<typename T>
std::shared_ptr<ListNode<T>> List<T>::NodeAlloc(const T &value) {
    std::shared_ptr<ListNode<T>> new_node = nullptr;

    time_t now = time(NULL);
    try {
        new_node = std::make_shared<ListNode<T>>(value);
    } catch (std::bad_alloc &e) {
        throw MemError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
    }

    return new_node;
}

#pragma endregion

#endif // __LIST_HPP__
