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
requires Comparable<T> && EmptyConstructable<T>
class List : public Container {
public:
    using value_type = T;
    using iterator = Iterator<T>;
    using const_iterator = ConstIterator<T>;

    friend class Iterator<T>;
    friend class ConstIterator<T>;
public:
    List(void);
    explicit List(const T &value);
    List(size_type size, const T &value);
    List(const std::initializer_list<T> &init);

    List(const iterator &beg, const iterator &end);
    List(const iterator &beg, size_type count);
    
    List(const const_iterator &beg, const const_iterator &end);
    List(const const_iterator &beg, size_type count);

    template<typename Iter>
    requires IteratorCheck<Iter, T>
    List(const Iter &begin, const Iter &end);
    template<typename Iter>
    requires IteratorCheck<Iter, T>
    List(const Iter &begin, size_type count);

    template <typename U, template<typename> class C>
    requires ContainerClass<C<U>> && Convertable<T, U>
    explicit List(const C<U> &container);


    List(List<T> &&list);
    template <typename U>
    requires Convertable<T, U>
    List(const List<U> &list);
    List(const List<T> &list);

    bool is_empty() const override;
    size_type size(void) const override;

    void push_back(const T &value);
    template<typename U>
    requires Convertable<T, U>
    void push_back(const List<U> &list);

    void push_front(const T &value);
    template<typename U>
    requires Convertable<T, U>
    void push_front(const List<U> &list);
    
    T pop_back(void);
    T pop_front(void);
    T pop(size_type index = 0);

    void clear(void) noexcept;
    void reverse(void) noexcept;
    bool find(const T &find_value) const noexcept;

    void insert(size_type index, const T &value);
    template<typename U>
    requires Convertable<T, U>
    void insert(size_type index, const List<U> &list);

    void remove(const T &value);

    T& operator[](size_type ind);
    const T& operator[](size_type ind) const;

    List<T> &operator=(List<T> &&list);
    template<typename U>
    requires Convertable<T, U>
    List<T> &operator=(const List<U> &list);
    List<T> &operator=(const List<T> &list);

    template<typename U>
    requires Convertable<T, U>
    List<T> operator+(const List<U> &add_list) const;
    
    template<typename U>
    requires Convertable<T, U>
    List<T> &operator+=(const List<U> &add_list);

    template<typename U>
    requires Convertable<T, U>
    bool operator==(const List<U> &add_list);

    template<typename U>
    requires Convertable<T, U>
    bool operator!=(const List<U> &add_list);

    auto operator<=>(const List<T>& other) const;

    void print(void) const noexcept;
    void debug_print(void) const noexcept;

    iterator begin(void);
    iterator end(void);

    const_iterator begin(void) const;
    const_iterator end(void) const;

    const_iterator cbegin(void) const;
    const_iterator cend(void) const;

    ~List() = default;

protected:
    class ListNode {
        friend class Iterator<T>;
        friend class ConstIterator<T>;
    public:
        ListNode(void);
        ListNode(const T &val);
        ListNode(ListNode &&node);
        ListNode(const ListNode &node);
        ListNode(const std::shared_ptr<ListNode> &node);

        void set_value(const T &val);
        void set_next(const ListNode &node);
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

    void ListAllocate(size_type size);
    std::shared_ptr<ListNode> NodeAlloc(const T &value = T());

private:
    std::shared_ptr<ListNode> head;
    std::shared_ptr<ListNode> tail;
};

#include "list.hpp"
#include "listnode.hpp"

#endif // __LIST_H__