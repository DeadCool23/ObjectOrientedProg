#ifndef __LIST_H__
#define __LIST_H__

#include "errors.h"

#include "concepts.h"

#include "listnode.h"
#include "container.h"

#include "iterator.h"
#include "citerator.h"

#include <functional>
#include <initializer_list>

template <typename T>
requires Comparable<T> && 
         Divable<T> && Multable<T> && 
         Neitral<T> && Printable<T>
class List final : public Container {
public:
    using value_t = T;
    using iterator_t = Iterator<T>;
    using citerator_t = ConstIterator<T>;

public:
    List(void);
    explicit List(const T &value);
    List(size_t size, const T &value);
    List(const std::initializer_list<T> &init);

    List(const iterator_t &beg, const iterator_t &end);
    List(const iterator_t &beg, const iterator_t &end, size_t count);
    
    List(const citerator_t &beg, const citerator_t &end);
    List(const citerator_t &beg, const citerator_t &end, size_t count);

    template <template<typename> class C>
    requires ContainerClass<C<T>>
    List(const C<T> &container);

    template <typename U, template<typename> class C>
    requires ContainerClass<C<U>> && Convertable<T, U>
    List(const C<U> &container);


    List(List &&list);
    explicit List(const List &list);

    bool is_empty() const override;
    size_t size(void) const override;

    void push_back(const T &value);
    void push_back(const List<T> &list);
    template<typename U>
    requires Convertable<T, U>
    void push_back(const List<U> &list);

    void push_front(const T &value);
    void push_front(const List<T> &list);
    template<typename U>
    requires Convertable<T, U>
    void push_front(const List<U> &list);
    
    T pop_back(void);
    T pop_front(void);
    T pop(size_t index = 0);

    void clear(void) noexcept;
    void reverse(void) noexcept;
    bool find(const T &find_value) const noexcept;

    void insert(size_t index, const T &value);

    void remove(const T &value);
    void remove(ListNode<T> &node);
    void remove(std::shared_ptr<ListNode<T>> &node);

    void each(std::function<T(const T &value)> func);

    T& operator[](size_t ind);
    const T& operator[](size_t ind) const;

    List<T> &operator=(List<T> &&list);
    List<T> &operator=(const List<T> &list);

    List<T> &operator*(const T& multer);
    List<T> &operator*=(const T& multer);

    List<T> &operator/(const T& diver);
    List<T> &operator/=(const T& diver);

    List<T> &operator+(const List<T> &add_list);
    template<typename U>
    requires Convertable<T, U>
    List<T> &operator+(const List<U> &add_list);
    
    List<T> &operator+=(const List<T> &add_list);
    template<typename U>
    requires Convertable<T, U>
    List<T> &operator+=(const List<U> &add_list);

    void print(void) const noexcept;
    void debug_print(void) const noexcept;

    iterator_t begin(void);
    iterator_t end(void);

    citerator_t cbegin(void) const;
    citerator_t cend(void) const;

    ~List() = default;

protected:
    citerator_t begin(void) const;
    citerator_t end(void) const;

    std::shared_ptr<ListNode<T>> get_head(void);
    std::shared_ptr<ListNode<T>> get_tail(void);

    std::shared_ptr<ListNode<T>> NodeAlloc(const T &value);

private:
    std::shared_ptr<ListNode<T>> head;
    std::shared_ptr<ListNode<T>> tail;
};

#include "list.hpp"

#endif // __LIST_H__