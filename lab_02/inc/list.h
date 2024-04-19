#ifndef __LIST_H__
#define __LIST_H__

#include "errors.h"

#include "concepts.h"

#include "container.h"

#include "iterator.h"
#include "citerator.h"

#include <memory>
#include <functional>
#include <initializer_list>

template <typename T>
requires Comparable<T> && EmptyConstructable<T> &&
         Divable<T> && Multable<T> && 
         Neitral<T> && Printable<T>
class List : public Container {
public:
    using value_type = T;
    using iterator_type = Iterator<T>;
    using const_iterator_type = ConstIterator<T>;

    friend class Iterator<T>;
    friend class ConstIterator<T>;
public:
    List(void);
    explicit List(const T &value);
    List(size_t size, const T &value);
    List(const std::initializer_list<T> &init);

    List(const iterator_type &beg, const iterator_type &end);
    List(const iterator_type &beg, size_t count);
    
    List(const const_iterator_type &beg, const const_iterator_type &end);
    List(const const_iterator_type &beg, size_t count);

    template<typename Iter>
    requires IteratorCheck<Iter, T>
    List(const Iter &begin, const Iter &end);
    template<typename Iter>
    requires IteratorCheck<Iter, T>
    List(const Iter &begin, size_t count);

    template <template<typename> class C>
    requires ContainerClass<C<T>>
    explicit List(const C<T> &container);

    template <typename U, template<typename> class C>
    requires ContainerClass<C<U>> && Convertable<T, U>
    explicit List(const C<U> &container);


    List(List<T> &&list);
    List(const List<T> &list);
    template <typename U>
    requires Convertable<T, U>
    List(const List<U> &list);

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
    void insert(size_t index, const List<T> &list);
    template<typename U>
    requires Convertable<T, U>
    void insert(size_t index, const List<U> &list);

    void remove(const T &value);

    void each(const std::function<T(const T &value)> &func);

    T& operator[](size_t ind);
    const T& operator[](size_t ind) const;

    List<T> &operator=(List<T> &&list);
    List<T> &operator=(const List<T> &list);
    template<typename U>
    requires Convertable<T, U>
    List<T> &operator=(const List<U> &list);

    List<T> operator*(const T& multer);
    List<T> &operator*=(const T& multer);

    List<T> operator/(const T& diver);
    List<T> &operator/=(const T& diver);

    List<T> operator+(const List<T> &add_list);
    template<typename U>
    requires Convertable<T, U>
    List<T> operator+(const List<U> &add_list);
    
    List<T> &operator+=(const List<T> &add_list);
    template<typename U>
    requires Convertable<T, U>
    List<T> &operator+=(const List<U> &add_list);

    template<typename U>
    requires Convertable<T, U>
    bool operator==(const List<U> &add_list);

    template<typename U>
    requires Convertable<T, U>
    bool operator!=(const List<U> &add_list);

    void print(void) const noexcept;
    void debug_print(void) const noexcept;

    iterator_type begin(void);
    iterator_type end(void);

    const_iterator_type begin(void) const;
    const_iterator_type end(void) const;

    const_iterator_type cbegin(void) const;
    const_iterator_type cend(void) const;

    ~List() = default;

protected:
    class ListNode {
        friend class Iterator<T>;
        friend class ConstIterator<T>;
    public:
        ListNode(void);
        ListNode(const T &val);
        ListNode(ListNode &node);
        ListNode(ListNode &&node);
        ListNode(std::shared_ptr<ListNode> &node);

        void set_value(const T &val);
        void set_next(ListNode &node);
        void set_next(const std::shared_ptr<ListNode> &node);

        void set_next_null(void);

        T& get_ref(void);
        const T& get_value(void) const;

        std::shared_ptr<ListNode> get_next(void) const;

        bool operator == (const ListNode &node) const;
        bool operator != (const ListNode &node) const;

        bool operator == (const std::shared_ptr<ListNode> &node) const;
        bool operator != (const std::shared_ptr<ListNode> &node) const;

        ~ListNode() = default;

    private:
        T value;
        std::shared_ptr<ListNode> next;
    };

protected:
    std::shared_ptr<ListNode> get_head(void);
    std::shared_ptr<ListNode> get_tail(void);

    List<T> ListAllocate(size_t size);
    std::shared_ptr<ListNode> NodeAlloc(const T &value = T());

private:
    std::shared_ptr<ListNode> head;
    std::shared_ptr<ListNode> tail;
};

#include "list.hpp"
#include "listnode.hpp"

#endif // __LIST_H__