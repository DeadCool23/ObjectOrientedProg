#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <ranges>
#include <iostream>
#include "concepts.h"

#pragma GCC diagnostic ignored "-Wreturn-type"

#pragma region Constructions
/* ---------------------- Конструкторы ---------------------- */
template <typename T>
List<T>::List(void) : head(nullptr), tail(nullptr) {}

template <typename T>
List<T>::List(const T &value) { this->clear();push_back(value); }

template <typename T>
List<T>::List(size_type size, const T &value) {
    time_t now = time(NULL);
    if (size < 0) throw SizeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    this->clear();
    for (size_type i = 0; i < size; ++i)
        this->push_back(value);
}

template <typename T>
List<T>::List(const std::initializer_list<T> &init) {
    this->clear();
    for (const auto &value : init)
        this->push_back(value);
}

template <typename T>
template <typename C>
requires ContainerClass<C> && ConvertableTo<typename C::value_type, T>
List<T>::List(const C &container) {
    this->clear();
    for (const auto &value : container)
        this->push_back(T(value));
}

template<typename T>
template<typename Iter>
requires ForwardIterator<Iter>
List<T>::List(const Iter &beg, const Iter &end) {
    this->clear();
    size_type i = 0;
    for (auto it = beg; it != end; ++it)
        this->push_back(*it);
}
template<typename T>
template<typename Iter>
requires ForwardIterator<Iter>
List<T>::List(const Iter &beg, size_type count) {
    this->clear();
    size_type i = 0;
    for (auto it = beg; i++ < count && it; ++it)
        this->push_back(*it);
    
    time_t now = time(NULL);
    if (i < count)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
}

template <typename T>
List<T>::List(List<T> &&list) : head(list.head), tail(list.tail) {
    this->_size = list._size;
}

template <typename T>
template <typename U>
requires ConvertableTo<U, T>
List<T>::List(const List<U> &list) {
    this->clear();
    for (const auto &value : list)
        this->push_back(T(value));
}

template <typename T>
List<T>::List(const List<T> &list) {
    this->clear();
    for (const auto &value : list)
        this->push_back(value);
}


#pragma endregion

#pragma region Methods
/* -------------------------------- Методы Списка ------------------------------ */
template<typename T>
Container::size_type List<T>::size(void) const { return _size; }

template<typename T>
bool List<T>::is_empty(void) const { return _size ? true : false; }

// --- Индексация ---
template<typename T>
T& List<T>::operator[](size_type ind) {
    time_t now = time(NULL);
    if (ind >= _size)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    size_type i = 0;
    for (auto &value : *this) {
        if (ind == i)
            return value;
        ++i;
    }
}

template<typename T>
const T& List<T>::operator[](size_type ind) const {
    time_t now = time(NULL);
    if (ind >= _size)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    size_type i = 0;
    for (auto &value : *this) {
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
template<typename U>
requires ConvertableTo<U, T>
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
template<typename U>
requires ConvertableTo<U, T>
void List<T>::push_front(const List<U> &list) {
    List<T> front_list;
    for (auto &value : list)
        front_list.push_back(T(value));
    front_list.tail->set_next(this->head);
    this->head = front_list.head;
}

// --- Поперы ---
template<typename T>
requires EmptyConstructable<T>
T List<T>::pop_back(void) {
    time_t now = time(NULL);
    if (!_size) throw EmptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    T del_val;
    if (_size == 1) {
        del_val = this->head
            ? this->head->get_ref()
            : T();
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
requires EmptyConstructable<T>
T List<T>::pop_front(void) {
    time_t now = time(NULL);
    if (!_size) throw SizeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    T del_val = this->head
        ? this->head->get_ref()
        : T();
    
    if (_size == 1) {
        this->head = nullptr;
        this->tail = nullptr;
    } else {
        this->head = this->head->get_next();
    }

    --this->_size;
    return del_val;
}

template<typename T>
T List<T>::pop(size_type index) {
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
        for (size_type i = 0; i < index - 1; ++i, cur = cur->get_next());

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
    std::shared_ptr<List<T>::ListNode> prev = nullptr;

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
void List<T>::insert(size_type index, const T &value) {
    time_t now = time(NULL);
    if (index > this->_size && index < 0)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    if (!index) {
        this->push_front(value);
    } else if (index == _size) {
        this->push_back(value);
    } else {
        auto cur = this->head;
        for (size_type i = 0; i < index - 1; ++i, cur = cur->get_next());

        std::shared_ptr<List<T>::ListNode> new_node = NodeAlloc(value);
        new_node->set_next(cur->get_next());
        cur->set_next(new_node);
    }
}

template<typename T>
template<typename U>
requires ConvertableTo<U, T>
void List<T>::insert(size_type index, const List<U> &list) {
    time_t now = time(NULL);
    if (index > this->_size && index < 0)
        throw RangeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    if (!index) {
        this->push_front(list);
    } else if (index == _size) {
        this->push_back(list);
    } else {
        auto cur = this->head;
        for (size_type i = 0; i < index - 1; ++i, cur = cur->get_next());

        List<T> new_tree = List(list);
        new_tree->get_tail()->set_next(cur->get_next());
        cur->set_next(new_tree);
    }
}

// --- Удаление ---
template<typename T>
requires EqualityComparable<T>
void List<T>::remove(const T &value) {
    bool is_del = false;
    if (this->head) {
    } else if (this->head->get_ref() == value) {
        is_del = true;
        this->pop_front();
    } else {
        auto cur = this->head;
        for (size_type i = 1; !is_del && i < _size; ++i, cur = cur.get_next()) {
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
List<T> &List<T>::operator=(List<T> &&list) {
    this->clear();
    this->head = list.head;
    this->tail = list.tail;
    this->_size = list._size;
    return *this;
}

template<typename T>
template<typename U>
requires ConvertableTo<U, T>
List<T> &List<T>::operator=(const List<U> &list) {

    auto tmp = List<T>(list);
    *this = tmp;
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
template<typename U>
requires ConvertableTo<U, T>
List<T> List<T>::operator+(const List<U> &add_list) const {
    List<T> tmp;
    tmp.push_back(*this);  
    tmp.push_back(add_list);  
    return tmp;
}


template<typename T>
template<typename U>
requires ConvertableTo<U, T>
List<T> &List<T>::operator+=(const List<U> &add_list) {
    *this = *this + add_list;
    return *this;
}

template<typename T>
requires EqualityComparable<T>
template<typename U>
requires ConvertableTo<U, T>
bool List<T>::operator==(const List<U> &add_list) {
    bool is_equal = true;
    if (this->size() != add_list.size())
        is_equal = false;

    for (size_type i = 0; is_equal && i < this->_size; ++i)
        if ((*this)[i] != T(add_list[i]))
            is_equal = false;
    
    return is_equal;
}

template<typename T> 
std::strong_ordering List<T>::operator<=>(const List<T>& other) const {
    return _size <=> other._size;
}

// --- Печать ---

template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T> &list) {
    os << "Size: " << list._size << std::endl;
    os << "{" << std::endl;
    for (Container::size_type i = 0; i < list._size; ++i)
        os << "  " << "[" << i << "]: " << list[i] << std::endl;
    os << "}" << std::endl;
}

#pragma endregion

#pragma region Iterations
/* ------------------------- Получение Итераторов -------------------------- */

template<typename T>
List<T>::iterator List<T>::begin(void) { return Iterator<T>(head); }

template<typename T>
List<T>::iterator List<T>::end(void) {
    auto end_ptr = tail->get_next();
    return Iterator<T>(end_ptr, _size); 
}

template<typename T>
List<T>::const_iterator List<T>::cbegin(void) const { return begin(); }

template<typename T>
List<T>::const_iterator List<T>::cend(void) const { return end(); }

template<typename T>
List<T>::const_iterator List<T>::begin(void) const { return ConstIterator<T>(head); }

template<typename T>
List<T>::const_iterator List<T>::end(void) const {
    auto end_ptr = tail->get_next();
    return ConstIterator<T>(end_ptr, _size); 
}

#pragma endregion

#pragma region ProtectedMethods

template<typename T>
std::shared_ptr<typename List<T>::ListNode> List<T>::get_head(void) { return head; }
template<typename T>
std::shared_ptr<typename List<T>::ListNode> List<T>::get_tail(void) { return tail; }

template<typename T>
void List<T>::ListAllocate(size_type size) {
    time_t now = time(NULL);
    if (size < 0) throw SizeError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));

    this->_size = size;
    std::shared_ptr<List<T>::ListNode> cur = nullptr;
    for (size_type i = 0; i < size; ++i, cur = cur->get_next()) {
        cur = NodeAlloc();
        if (!i) this->head = cur;
        this->tail = cur;
    };
}

// Выделение памяти под Узел
template<typename T>
std::shared_ptr<typename List<T>::ListNode> List<T>::NodeAlloc(const T &value) {
    std::shared_ptr<List<T>::ListNode> new_node = nullptr;

    time_t now = time(NULL);
    try {
        new_node = std::make_shared<List<T>::ListNode>(value);
    } catch (std::bad_alloc &e) {
        throw MemError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
    }

    return new_node;
}

#pragma endregion

#endif // __LIST_HPP__
