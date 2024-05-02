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

using namespace IterConcepts;

template <typename T>
requires EqualityComparable<T> && EmptyConstructable<T>
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

    template<typename Iter>
    requires ForwardIterator<Iter> && ConvertableTo<typename Iter::value_type, T>
    List(const Iter &begin, const Iter &end);
    template<typename Iter>
    requires ForwardIterator<Iter> && ConvertableTo<typename Iter::value_type, T>
    List(const Iter &begin, size_type count);

    template <typename C>
    requires ContainerClass<C> && ConvertableTo<typename C::value_type, T>
    explicit List(const C &container);


    List(List<T> &&list);
    template <typename U>
    requires ConvertableTo<U, T>
    List(const List<U> &list);
    List(const List<T> &list);

    List<T> &operator=(List<T> &&list);
    template<typename U>
    requires ConvertableTo<U, T>
    List<T> &operator=(const List<U> &list);
    List<T> &operator=(const List<T> &list);

    bool is_empty() const override;
    size_type size(void) const override;

    void push_back(const T &value);
    template<typename U>
    requires ConvertableTo<U, T>
    void push_back(const List<U> &list);

    void push_front(const T &value);
    template<typename U>
    requires ConvertableTo<U, T>
    void push_front(const List<U> &list);
    
    T pop_back(void);
    T pop_front(void);
    T pop(size_type index = 0);

    void clear(void) noexcept;
    void reverse(void) noexcept;
    bool find(const T &find_value) const noexcept;

    void insert(size_type index, const T &value);
    template<typename U>
    requires ConvertableTo<U, T>
    void insert(size_type index, const List<U> &list);

    void remove(const T &value);

    T& operator[](size_type ind);
    const T& operator[](size_type ind) const;

    template<typename U>
    requires ConvertableTo<U, T>
    List<T> operator+(const List<U> &add_list) const;
    
    template<typename U>
    requires ConvertableTo<U, T>
    List<T> &operator+=(const List<U> &add_list);

    template<typename U>
    requires ConvertableTo<U, T>
    bool operator==(const List<U> &add_list);

    std::strong_ordering operator<=>(const List<T>& other) const;

    iterator begin(void);
    iterator end(void);

    const_iterator begin(void) const;
    const_iterator end(void) const;

    const_iterator cbegin(void) const;
    const_iterator cend(void) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const List<U> &list);

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
        bool operator == (const std::shared_ptr<ListNode> &node) const;

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